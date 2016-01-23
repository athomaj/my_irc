/*
** main.c for  in /Users/julien/rendu/PSU_2014_myirc
** 
** Made by julien athomas
** Login   <julien@epitech.net>
** 
** Started on  Mon Apr  6 10:13:43 2015 julien athomas
** Last update Sun Apr 12 21:19:47 2015 julien athomas
*/

#include "server.h"

int	init_proto(struct protoent **pe, struct sockaddr_in *s_in, int port)
{
  if ((*pe = getprotobyname("TCP")) == NULL)
    return (-1);
  s_in->sin_family = AF_INET;
  s_in->sin_port = htons(port);
  s_in->sin_addr.s_addr = INADDR_ANY;
  return (0);
}

int	init_socket(struct protoent *pe, struct sockaddr_in *s_in)
{
  int	fd;

  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  if (bind(fd, (const struct sockaddr *)s_in, sizeof(*s_in)) == -1)
    {
      fprintf(stderr, "bind failed\n");
      if (close(fd) == -1)
	return (-1);
      return (-1);
    }
  if (listen(fd, 42) == -1)
    {
      if (close(fd) == -1)
	return (-1);
      return (-1);
    }
  return (fd);
}

int		set_fds_channel(t_all *all, fd_set *fd_read, t_client *tmp,
				int max_fd)
{
  t_channel	*tmp_chan;

  tmp_chan = all->channel;
  while (tmp_chan)
    {
      tmp = tmp_chan->client;
      while (tmp)
	{
	  FD_SET(tmp->fd, fd_read);
	  max_fd = tmp->fd > max_fd ? tmp->fd : max_fd;
	  tmp = tmp->next;
	}
      tmp_chan = tmp_chan->next;
    }
  return (max_fd);
}

int			set_fds(t_all *all, fd_set *fd_read)
{
  int			max_fd;
  t_client		*tmp;

  max_fd = 0;
  FD_ZERO(fd_read);
  tmp = all->actual;
  while (tmp)
    {
      FD_SET(tmp->fd, fd_read);
      max_fd = tmp->fd > max_fd ? tmp->fd : max_fd;
      tmp = tmp->next;
    }
  return (set_fds_channel(all, fd_read, tmp, max_fd));
}

int			main(int argc, char **argv)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;
  int			fd;

  if (argc != 2)
    {
      fprintf(stderr, "Usage: ./server port\n");
      return (-1);
    }
  init_proto(&pe, &s_in, atoi(argv[1]));
  if ((fd = init_socket(pe, &s_in)) == -1)
    return (-1);
  receive_clients(fd);
  if (close(fd) == -1)
    return (-1);
  return (0);
}
