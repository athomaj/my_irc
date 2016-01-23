/*
** channel.c for  in /home/athoma_j/rendu/PSU_2014_myirc
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Sun Apr 12 09:15:23 2015 julien athomas
** Last update Sun Apr 12 17:20:02 2015 Flavien Maillot
*/

#include "../../server.h"

int			new_channel(t_all *all, char *name)
{
  t_channel		*chan;

  if ((chan = malloc(sizeof(t_channel))) == NULL)
    return (-1);
  chan->name = strdup(name);
  chan->client = NULL;
  chan->topic = strdup("New useless channel");
  chan->next = all->channel;
  all->channel = chan;
  if (DEBUG == true)
    printf("new Channel\n");
  return (0);
}

void		add_client_to_channel(t_all *all, t_channel *channel,
				      t_client *client)
{
  t_client	*tmp;
  t_client	*tmp2;

  if (client->channel)
    remove_client_from_channel(&client->channel, client);
  tmp = all->actual;
  tmp2 = NULL;
  while (tmp && tmp != client)
    {
      tmp2 = tmp;
      tmp = tmp->next;
    }
  if (tmp)
    {
      if (tmp2 == NULL)
	all->actual = all->actual->next;
      else
	tmp2->next = tmp->next;
    }
  client->next = channel->client;
  channel->client = client;
  client->channel = channel;
  if (DEBUG == true)
    printf("Client added\n");
}

void		remove_client_from_channel(t_channel **channel,
					   t_client *client)
{
  t_client	*tmp;
  t_client	*tmp2;

  tmp = NULL;
  tmp2 = (*channel)->client;
  while (tmp2 && tmp2 != client)
    {
      tmp = tmp2;
      tmp2 = tmp2->next;
    }
  if (tmp2)
    {
      if (tmp)
	tmp->next = tmp2->next;
      else
	(*channel)->client = (*channel)->client->next;
      client->channel = NULL;
    }
  else
    printf("does not exist\n");
}
