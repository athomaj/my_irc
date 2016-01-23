/*
** irc_gen.c for  in /home/maillo_a/rendu/PSU_2014_myirc
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Sun Apr 12 18:44:52 2015 Flavien Maillot
** Last update Sun Apr 12 23:07:35 2015 Flavien Maillot
*/

#include "server.h"

void			dump_channels(t_channel *tmp)
{
  while (tmp)
    {
      printf("%s\n", tmp->name);
      tmp = tmp->next;
    }
}

void			my_write(t_all *all, t_client *client)
{
  t_client		*tmp;

  tmp = all->actual;
  while (tmp)
    {
      if (tmp != client && tmp == client)
	{
	  write(tmp->fd, &(all->buf.buf[all->buf.init_idx]),
		all->buf.actual_size);
	  write(tmp->fd, "\n", 1);
	}
      tmp = tmp->next;
    }
}

t_user*			add_user()
{
  t_user		*user;

  if ((user = malloc(sizeof(t_user))) == NULL)
    return (NULL);
  user->nick = NULL;
  user->channel = NULL;
  user->user = NULL;
  user->pass = NULL;
  user->prefix = NULL;
  return (user);
}

int			add_fd(t_all *all, int type, int fd,
			       void (*fptr)(t_all *, t_client *))
{
  t_client		*node;

  if ((node = malloc(sizeof(t_client))) == NULL)
    return (-1);
  node->type = type;
  node->fd = fd;
  node->next = all->actual;
  node->fptr = fptr;
  node->idx = all->actual == NULL ? 0 : (all->actual)->idx;
  node->write_fptr = &my_write;
  node->len = all->actual == NULL ? 0 : (all->actual)->len;
  node->channel = NULL;
  node->user = add_user();
  all->actual = node;
  return (0);
}
