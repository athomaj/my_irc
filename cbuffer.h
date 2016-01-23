/*
** main.h for  in /home/athoma_j/tmp
** 
** Made by julien athomas
** Login   <athoma_j@epitech.net>
** 
** Started on  Thu Apr  9 10:17:33 2015 julien athomas
** Last update Sat Apr 11 01:10:19 2015 julien athomas
*/

#ifndef TEST
# define TEST

#include <string.h>

# define BUF_SIZE 512

typedef struct	s_cbuffer
{
  char		buf[BUF_SIZE];
  int		max_size;
  int		actual_size;
  int		idx;
  int		init_idx;
  void		(*push)(struct s_cbuffer *, char *);
}		t_cbuffer;

void	buf_push(struct s_cbuffer *, char *);
void	init_buffer(t_cbuffer *);

#endif
