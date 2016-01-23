/*
** init_client.c for  in /home/maillo_a/rendu/PSU_2014_myirc/client
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Sun Apr 12 21:47:03 2015 Flavien Maillot
** Last update Sun Apr 12 22:08:18 2015 Flavien Maillot
*/

#include "client.h"

void			init_servco(int *fd, char *ip, int port)
{
  struct protoent	*pe;
  struct sockaddr_in	s_in;

  if ((pe = getprotobyname("TCP")) == NULL)
    return ;
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = inet_addr(ip);
  if ((*fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      *fd = -1;
      printf("socket failed\n");
      return ;
    }
  if (connect(*fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      *fd = -1;
      printf("connect failed\n");
      return ;
    }
}

void		init_fds(fd_set *fd_read, int fd)
{
  FD_ZERO(fd_read);
  FD_SET(0, fd_read);
  if (fd != -1)
    FD_SET(fd, fd_read);
}

void		init_fptr(void (*fptr[7])(char buf[515], int *), char *tab[7])
{
  tab[0] = "/server";
  tab[1] = "/nick";
  tab[2] = "/list";
  tab[3] = "/join";
  tab[4] = "/part";
  tab[5] = "/users";
  tab[6] = "/msg";
  fptr[0] = &my_server;
  fptr[1] = &my_nick;
  fptr[2] = &my_list;
  fptr[3] = &my_join;
  fptr[4] = &my_part;
  fptr[5] = &my_users;
  fptr[6] = &my_msg;
}

int		init_connection()
{
  fd_set	fd_read;
  void		(*fptr[7])(char buf[515], int *);
  char		*tab[7];
  int		fd;

  fd = -1;
  init_fptr(fptr, tab);
  while (1)
    {
      init_fds(&fd_read, fd);
      if ((select(fd == -1 ? 1 : fd + 1, &fd_read, NULL, NULL, NULL)) == -1)
	return (-1);
      if (check_fds(&fd_read, &fd, fptr, tab) == -1)
	return (-1);
    }
  return (0);
}
