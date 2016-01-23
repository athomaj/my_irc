/*
** func.c for  in /home/athoma_j/rendu/PSU_2014_myirc
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Wed Apr  8 12:58:52 2015 julien athomas
** Last update Thu Apr 16 13:23:06 2015 julien athomas
*/

#include "../server.h"

void	init_com(__attribute__((unused))int (*fptr[NB_COM])
		 (t_parser *, t_all *, t_client *))
{
  fptr[0] = my_nick;
  fptr[1] = my_list;
  fptr[2] = my_join;
  fptr[3] = my_part;
  fptr[4] = my_users;
  fptr[5] = my_msg;
  fptr[6] = my_quit;
  fptr[7] = my_user;
}

void	init_ptr(char *tab[NB_COM], int (*fptr[NB_COM])
		 (t_parser *, t_all *, t_client *))
{
  tab[0] = "NICK";
  tab[1] = "LIST";
  tab[2] = "JOIN";
  tab[3] = "PART";
  tab[4] = "NAMES";
  tab[5] = "PRIVMSG";
  tab[6] = "QUIT";
  tab[7] = "USER";
  init_com(fptr);
}

void		write_msg(t_parser *parser, t_all *all, t_client *client)
{
  t_channel	*channel;
  t_client	*tmp;

  channel = all->channel;
  if (!client->channel)
    {
      write(client->fd, "You are not in a channel\r\n",
	    sizeof("You are not in a channel\r\n"));
      return ;
    }
  while (channel && channel != client->channel)
    channel = channel->next;
  if (channel)
    {
      tmp = channel->client;
      while (tmp)
	{
	  if (tmp != client && parser->line)
	    {
	      write(tmp->fd, parser->line, strlen(parser->line));
	      write(tmp->fd, "\r\n", 2);
	    }
	  tmp = tmp->next;
	}
    }
}

int	check_quit(t_all *all, t_parser *parser, t_client *client)
{
  char	*tmp;

  tmp = strndup(&all->buf.buf[all->buf.init_idx], all->buf.actual_size);
  if (tmp && strstr(tmp, "QUIT"))
    {
      my_quit(parser, all, client);
      return (1);
    }
  return (0);
}

bool	treatment(t_parser *parser, t_all *all, t_client *client)
{
  char	*tab[NB_COM];
  int	(*fptr[NB_COM])(t_parser *, t_all *, t_client *);
  int	i;

  if (DEBUG == true)
    printf("treatment\n");
  if (check_quit(all, parser, client))
    return (false);
  init_ptr(tab, fptr);
  i = -1;
  while (++i < NB_COM)
    if (parser->command && strncmp(parser->command, tab[i],
				   strlen(tab[i])) == 0)
      {
	if (i && (!client->user || !client->user->nick) && i != 6)
	  {
	    write(client->fd, ERR_NOTREGISTERED, strlen(ERR_NOTREGISTERED));
	    write(client->fd, "\r\n", 2);
	  }
	else
	  fptr[i](parser, all, client);
	return (true);
      }
  write_msg(parser, all, client);
  return (true);
}
