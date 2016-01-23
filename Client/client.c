/*
** client.c for  in /home/athoma_j/rendu/PSU_2014_myirc/client
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Sun Apr 12 12:03:52 2015 julien athomas
** Last update Sun Apr 12 23:15:02 2015 julien athomas
*/

#include "client.h"

void		check_fptr(void (*fptr[7])(char buf[515], int *),
			   char *tab[7], char buf[515], int *fd)
{
  int		i;
  char		*tmp;

  tmp = strtok(strdup(buf), " ");
  if (!tmp)
    {
      printf("invalid command\n");
      return ;
    }
  i = -1;
  while (++i < 7)
    if (strcmp(tab[i], tmp) == 0)
      {
	fptr[i](buf, fd);
	return ;
      }
  strcat(buf, "\r\n");
  write(*fd, buf, strlen(buf));
}

int		read_stdin(int *fd, void (*fptr[7])(char buf[515], int *),
			   char *tab[7])
{
  char		buf[515];
  int		ret;

  if ((ret = read(0, buf, 512)) <= 0)
    return (-1);
  buf[ret - 1] = 0;
  check_fptr(fptr, tab, buf, fd);
  return (0);
}

int		read_socket(int *fd)
{
  char		buf[515];
  int		ret;

  if ((ret = read(*fd, buf, 512)) <= 0)
    {
      printf("connection closed\n");
      return (-1);
    }
  buf[ret] = 0;
  write(1, buf, ret);
  return (0);
}

int		check_fds(fd_set *fd_read, int *fd,
			  void (*fptr[7])(char buf[515], int *), char *tab[7])
{
  if (FD_ISSET(0, fd_read))
    if (read_stdin(fd, fptr, tab) == -1)
      return (-1);
  if (*fd != -1 && FD_ISSET(*fd, fd_read))
    if (read_socket(fd) == -1)
      return (-1);
  return (0);
}

int	main()
{
  init_connection();
  return (0);
}
