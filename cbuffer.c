/*
** main.c for  in /home/athoma_j/tmp
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Thu Apr  9 10:13:50 2015 julien athomas
** Last update Fri Apr 10 23:55:25 2015 julien athomas
*/

#include "cbuffer.h"

void	buf_push(struct s_cbuffer *buf, char *add)
{
  int	i;

  buf->actual_size = 0;
  i = buf->idx;
  buf->init_idx = i;
  while (*add)
    {
      buf->buf[i] = *add;
      i = (i + 1) % buf->max_size;
      ++add;
      ++buf->actual_size;
    }
  buf->idx = i;
}

void	init_buffer(t_cbuffer *buf)
{
  buf->max_size = BUF_SIZE;
  buf->actual_size = 0;
  buf->idx = 0;
  buf->push = &buf_push;
  memset(buf, 0, BUF_SIZE);
}
