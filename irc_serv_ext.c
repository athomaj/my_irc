/*
** irc_serv_ext.c for  in /home/maillo_a/rendu/PSU_2014_myirc
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Sun Apr 12 18:49:03 2015 Flavien Maillot
** Last update Sun Apr 12 19:02:04 2015 Flavien Maillot
*/

#include "server.h"

void			serv_ptr(t_all *all, UNUSED t_client *client)
{
  struct sockaddr_in	s_in_c;
  socklen_t		s_size;
  int			fd_c;

  if ((fd_c = accept(all->fds->fd_s, (struct sockaddr *)(&s_in_c),
		     &(s_size))) == -1)
    {
      fprintf(stderr, "Accept failed\n");
      close(all->fds->fd_s);
      return ;
    }
  printf("New Client\n");
  add_fd(all, CLIENT_ID, fd_c, &client_ptr);
}

void		check_fd_channel(t_all *all, t_client *tmp)
{
  t_channel	*tmp_chan;

  tmp_chan = all->channel;
  while (tmp_chan)
    {
      tmp = tmp_chan->client;
      while (tmp)
	{
	  if (FD_ISSET(tmp->fd, &(all->fds->fd_read)))
	    {
	      tmp->fptr(all, tmp);
	      return ;
	    }
	  if (FD_ISSET(tmp->fd, &(all->fds->fd_write)))
	    tmp->write_fptr(all, tmp);
	  tmp = tmp->next;
	}
      tmp_chan = tmp_chan->next;
    }
}

void			check_fd(t_all *all)
{
  t_client		*tmp;

  tmp = all->actual;
  while (tmp)
    {
      if (FD_ISSET(tmp->fd, &(all->fds->fd_read)))
	{
	  tmp->fptr(all, tmp);
	  return ;
	}
      if (FD_ISSET(tmp->fd, &(all->fds->fd_write)))
	tmp->write_fptr(all, tmp);
      tmp = tmp->next;
    }
  check_fd_channel(all, tmp);
}
