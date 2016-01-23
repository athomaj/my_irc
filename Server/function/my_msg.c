/*
** function_part2.c for  in /home/athoma_j/rendu/PSU_2014_myirc
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Sun Apr 12 14:05:26 2015 julien athomas
** Last update Thu Apr 16 13:10:44 2015 julien athomas
*/

#include "../../server.h"

char		*my_msg_first_check(t_parser *parser, t_client *client,
				   char **cur, char **next)
{
  char		*tmp;

  if (parser->params)
    tmp = strdup(parser->params);
  if (!parser->params || !(*cur = strtok(tmp, " ")))
    {
      write(client->fd, ERR_NORECIPIENT, strlen(ERR_NORECIPIENT));
      write(client->fd, "\r\n", 2);
      return (NULL);
    }
  if (!(*next = strtok(NULL, " ")))
    {
      write(client->fd, ERR_NOTEXTTOSEND, strlen(ERR_NOTEXTTOSEND));
      write(client->fd, "\r\n", 2);
      return (NULL);
    }
  return (tmp);
}

int		my_msg_next(t_parser *parser, t_client *client, t_client *tmpc,
			    char *cur)
{
  int		ret;

  tmpc = client->channel->client;
  ret = -1;
  while (tmpc && (ret))
    {
      if (tmpc->user && tmpc->user->nick &&
	  ((ret = strcmp(tmpc->user->nick, cur)) == 0))
	{
	  write(tmpc->fd, parser->line, strlen(parser->line));
	  write(tmpc->fd, "\r\n", 2);
	}
      tmpc = tmpc->next;
    }
  if (ret)
    {
      write(client->fd, ERR_NOSUCHNICK, strlen(ERR_NOSUCHNICK));
      write(client->fd, "\r\n", 2);
      return (-1);
    }
  return (0);
}

int		my_msg_check(t_client *client)
{
  if (!client->channel)
    {
      write(client->fd, ERR_CANNOTSENDTOCHAN, strlen(ERR_CANNOTSENDTOCHAN));
      write(client->fd, "\r\n", 2);
      return (-1);
    }
  return (0);
}

int		my_msg(t_parser *parser, UNUSED t_all *all, t_client *client)
{
  char		*cur;
  char		*next;
  char		*tmp;
  t_client	*tmpc;

  if ((tmp = my_msg_first_check(parser, client, &cur, &next)) == NULL)
    return (-1);
  while (next)
    {
      cur = next;
      next = strtok(NULL, " ");
    }
  parser->line = cur;
  tmp = strdup(parser->params);
  cur = strtok(tmp, " ");
  tmpc = NULL;
  while (cur && strcmp(cur, parser->line))
    {
      if (my_msg_check(client) == -1 ||
	  my_msg_next(parser, client, tmpc, cur) == -1)
	return (-1);
      cur = strtok(NULL, " ");
    }
  return (0);
}
