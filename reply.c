/*
** reply.c for  in /home/athoma_j/rendu/PSU_2014_myirc
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Wed Apr  8 23:12:42 2015 julien athomas
** Last update Sun Apr 12 23:11:33 2015 Flavien Maillot
*/

#include "server.h"

void	com_reply(t_client *client, char *code, char *msg, char *arg)
{
  char	*res;

  if ((res = malloc(strlen(msg) + strlen(arg) + strlen(code)))
      == NULL)
    return ;
  sprintf(res, msg, code, arg);
  write(client->fd, res, strlen(res) - 1);
}
