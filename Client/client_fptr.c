/*
** client_fptr.c for  in /home/maillo_a/rendu/PSU_2014_myirc/client
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Sun Apr 12 21:47:19 2015 Flavien Maillot
** Last update Thu Apr 16 13:35:09 2015 julien athomas
*/

#include "client.h"

void		my_server(char buf[515], int *fd)
{
  char		*tmp;
  char		*ip;
  char		*port;

  tmp = strtok(buf, " ");
  tmp = strtok(NULL, " ");
  if (tmp == NULL)
    {
      printf("wrong arguments\n");
      return ;
    }
  ip = strtok(tmp, ":");
  port = strtok(NULL, ":");
  if (ip == NULL || port == NULL)
    {
      printf("wrong arguments\n");
      return ;
    }
  init_servco(fd, ip, atoi(port));
}

void		my_nick(char buf[515], int *fd)
{
  char		tmp[520];

  memset(tmp, 0, 520);
  memcpy(tmp, "NICK", 4);
  strcat(tmp, &buf[5]);
  strcat(tmp, "\r\n\0");
  write(*fd, tmp, strlen(tmp));
}

void		my_list(char buf[515], int *fd)
{
  char		tmp[520];

  memset(tmp, 0, 520);
  memcpy(tmp, "LIST", 4);
  strcat(tmp, &buf[5]);
  strcat(tmp, "\r\n\0");
  write(*fd, tmp, strlen(tmp));
}

void		my_join(char buf[515], int *fd)
{
  char		tmp[520];

  memset(tmp, 0, 520);
  memcpy(tmp, "JOIN", 4);
  strcat(tmp, &buf[5]);
  strcat(tmp, "\r\n\0");
  write(*fd, tmp, strlen(tmp));
}

void		my_part(char buf[515], int *fd)
{
  char		tmp[520];

  memset(tmp, 0, 520);
  memcpy(tmp, "PART", 4);
  strcat(tmp, &buf[5]);
  strcat(tmp, "\r\n\0");
  write(*fd, tmp, strlen(tmp));
}
