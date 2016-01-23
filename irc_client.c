/*
** irc_client.c for  in /home/maillo_a/rendu/PSU_2014_myirc
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Sun Apr 12 18:36:44 2015 Flavien Maillot
** Last update Sun Apr 12 21:23:02 2015 julien athomas
*/

#include "server.h"

void			remove_client(t_all *all, t_client *client)
{
  t_client		*tmp;
  t_client		*tmp2;

  tmp = all->actual;
  tmp = NULL;
  close(client->fd);
  if (client->channel)
    remove_client_from_channel(&(client->channel), client);
  tmp2 = all->actual;
  while (tmp2 && tmp2 != client)
    {
      tmp = tmp2;
      tmp2 = tmp2->next;
    }
  if (tmp2)
    {
      if (tmp != NULL)
	tmp->next = tmp2->next;
      else
	all->actual = all->actual->next;
    }
}

void			client_ptr(t_all *all, t_client *client)
{
  char			buff[512];
  int			len;
  t_client		*tmp;

  if ((len = read(client->fd, buff, 511)) <= 0)
    {
      remove_client(all, client);
      return ;
    }
  buff[len] = 0;
  tmp = all->actual;
  while (tmp)
    {
      tmp->len = len;
      tmp = tmp->next;
    }
  FD_SET(client->fd, &(all->fds->fd_write));
  all->buf.push(&(all->buf), buff);
  split_buffer(all, client);
}

int			receive_clients(int fd)
{
  t_fd			fds;
  int			ret;
  t_all			all;

  init_buffer(&(all.buf));
  all.fds = &fds;
  all.channel = NULL;
  all.fds->fd_s = fd;
  all.actual = NULL;
  new_channel(&all, "toto");
  new_channel(&all, "titi");
  if ((add_fd(&all, SERVER_ID, fd, &serv_ptr)) == -1)
    return (-1);
  while (1)
    {
      all.fds->max_fd = set_fds(&all, &(all.fds->fd_read));
      FD_ZERO(&(all.fds->fd_write));
      if ((ret = select(all.fds->max_fd + 1, &(all.fds->fd_read),
			&(all.fds->fd_write),
			NULL, NULL)) == -1)
	return (1);
      check_fd(&all);
    }
  return (0);
}
