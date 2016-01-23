/*
** function_part1.c for  in /home/maillo_a/rendu/PSU_2014_myirc/server/function
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Fri Apr 10 22:59:01 2015 Flavien Maillot
** Last update Sun Apr 12 23:18:50 2015 julien athomas
*/

#include "../../server.h"

int		my_nick_channel(t_parser *parser, t_all *all, t_client *client)
{
  t_client	*tmp;
  t_channel	*channel;

  channel = all->channel;
  while (channel)
    {
      tmp = channel->client;
      while (tmp)
	{
	  if (tmp->user->nick && strcmp(tmp->user->nick, parser->params) == 0)
	    {
	      write(client->fd, ERR_NICKNAMEINUSE, strlen(ERR_NICKNAMEINUSE));
	      write(client->fd, "\r\n", 2);
	      return (-1);
	    }
	  tmp = tmp->next;
	}
      channel = channel->next;
    }
  return (0);
}

int		my_nick(t_parser *parser, t_all *all, t_client *client)
{
  t_client	*tmp;

  if (!parser->params)
    {
      write(client->fd, ERR_NONICKNAMEGIVEN, strlen(ERR_NONICKNAMEGIVEN));
      write(client->fd, "\r\n", 2);
      return (-1);
    }
  tmp = all->actual;
  while (tmp)
    {
      if (tmp->user->nick && strcmp(tmp->user->nick, parser->params) == 0)
	{
	  write(client->fd, ERR_NICKNAMEINUSE, strlen(ERR_NICKNAMEINUSE));
	  write(client->fd, "\r\n", 2);
	  return (-1);
	}
      tmp = tmp->next;
    }
  if (my_nick_channel(parser, all, client) != 0)
    return (-1);
  client->user->nick = strdup(parser->params);
  return (0);
}

void		my_join_channel(t_parser *parser, t_all *all, t_client *client,
				t_channel *channel)
{
  if (!channel)
    {
      new_channel(all, parser->params);
      add_client_to_channel(all, all->channel, client);
    }
}

int		my_join(t_parser *parser, t_all *all, t_client *client)
{
  t_channel	*channel;

  channel = all->channel;
  if (parser->params != NULL)
    {
      while (channel)
	{
	  if (strcmp(channel->name, parser->params) == 0)
	    {
	      if (client->channel)
		remove_client_from_channel(&client->channel, client);
	      add_client_to_channel(all, channel, client);
	      return (0);
	    }
	  channel = channel->next;
	}
      my_join_channel(parser, all, client, channel);
    }
  else
    {
      write(client->fd, ERR_NEEDMOREPARAMS, strlen(ERR_NEEDMOREPARAMS));
      write(client->fd, "\r\n", 2);
    }
  return (0);
}

int		my_users(UNUSED t_parser *parser, UNUSED t_all *all,
			 t_client *client)
{
  t_client	*clients;

  write(client->fd, RPL_USERSSTART, strlen(RPL_USERSSTART));
  write(client->fd, "\r\n", 2);
  clients = NULL;
  if (client->channel)
    clients = client->channel->client;
  while (clients)
    {
      if (clients->user != NULL && clients->user->nick != NULL)
	{
	  write(client->fd, RPL_USERS, strlen(RPL_USERS));
	  write(client->fd, " ", 1);
	  write(client->fd, clients->user->nick, strlen(clients->user->nick));
	  write(client->fd, "\r\n", 2);
	}
      clients = clients->next;
    }
  write(client->fd, RPL_ENDOFUSERS, strlen(RPL_ENDOFUSERS));
  write(client->fd, "\r\n", 2);
  return (0);
}
