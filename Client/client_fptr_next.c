/*
** client_fptr_next.c for  in /home/maillo_a/rendu/PSU_2014_myirc/client
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Sun Apr 12 21:50:59 2015 Flavien Maillot
** Last update Sun Apr 12 21:51:44 2015 Flavien Maillot
*/

#include "client.h"

void		my_users(char buf[515], int *fd)
{
  char		tmp[520];

  memset(tmp, 0, 520);
  memcpy(tmp, "NAMES", 5);
  strcat(tmp, &buf[6]);
  strcat(tmp, "\r\n\0");
  write(*fd, tmp, strlen(tmp));
}

void		my_msg(char buf[515], int *fd)
{
  char		tmp[520];

  memset(tmp, 0, 520);
  memcpy(tmp, "PRIVMSG", 7);
  strcat(tmp, &buf[4]);
  strcat(tmp, "\r\n\0");
  write(*fd, tmp, strlen(tmp));
}
