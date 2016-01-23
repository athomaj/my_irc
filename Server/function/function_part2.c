/*
** function_part2.c for  in /home/athoma_j/rendu/PSU_2014_myirc
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Sun Apr 12 14:05:26 2015 julien athomas
** Last update Thu Apr 16 13:08:22 2015 julien athomas
*/

#include "../../server.h"

int		my_list(UNUSED t_parser *parser, t_all *all, t_client *client)
{
  t_channel	*tmp;

  tmp = all->channel;
  write(client->fd, RPL_LISTSTART, strlen(RPL_LISTSTART));
  write(client->fd, "\r\n", 2);
  while (tmp)
    {
      if (!parser->params || strpbrk(tmp->name, parser->params))
	{
	  write(client->fd, RPL_LIST, strlen(RPL_LIST));
	  write(client->fd, " ", 1);
	  write(client->fd, tmp->name, strlen(tmp->name));
	  write(client->fd, "\r\n", 2);
	}
      tmp = tmp->next;
    }
  write(client->fd, RPL_LISTEND, strlen(RPL_LISTEND));
  write(client->fd, "\r\n", 2);
  return (0);
}

int		my_part_channel(t_all *all, t_client *client,
				t_channel *channel)
{
  if (client->channel != channel)
    {
      write(client->fd, ERR_NOTONCHANNEL, strlen(ERR_NOTONCHANNEL));
      write(client->fd, "\r\n", 2);
      return (-1);
    }
  remove_client_from_channel(&client->channel, client);
  client->next = all->actual;
  all->actual = client;
  return (0);
}

int		my_part(t_parser *parser, t_all *all, t_client *client)
{
  t_channel	*channel;

  if (!parser->params)
    {
      write(client->fd, ERR_NEEDMOREPARAMS, strlen(ERR_NEEDMOREPARAMS));
      write(client->fd, "\r\n", 2);
      return (-1);
    }
  channel = all->channel;
  while (channel && strcmp(channel->name, parser->params) != 0)
    channel = channel->next;
  if (channel)
    {
      if (my_part_channel(all, client, channel) != 0)
	return (-1);
    }
  else
    {
      write(client->fd, ERR_NOSUCHCHANNEL, strlen(ERR_NOSUCHCHANNEL));
      write(client->fd, "\r\n", 2);
    }
  return (0);
}

int		my_user(UNUSED t_parser *parser, UNUSED t_all *all,
			UNUSED t_client *client)
{
  write(client->fd, "You are now connected\r\n",
	sizeof("You are now connected\r\n"));
  return (0);
}

int		my_quit(UNUSED t_parser *parser, t_all *all, t_client *client)
{
  remove_client(all, client);
  return (0);
}
