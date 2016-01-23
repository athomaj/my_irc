/*
** parser.h for  in /home/maillo_a/rendu/PSU_2014_myirc/server/parser
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Wed Apr  8 21:00:37 2015 Flavien Maillot
** Last update Thu Apr 16 13:06:47 2015 julien athomas
*/

#ifndef PARSER_H_
# define PARSER_H_

# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "../../server.h"

# define DEBUG true

typedef struct s_all	t_all;
typedef struct s_client	t_client;

typedef struct	s_parser
{
  char		*prefix;
  char		*command;
  char		*params;
  char		*line;
  int		start;
  int		end;
  int		pos;
}		t_parser;

/* first_check.c */
bool	check_crlf(t_parser *, char *);
bool	check_params(t_parser *, char *);
bool	check_command(t_parser *, char *);
bool	check_prefixe(t_parser *, char *);

/* parser.c */
bool	parse_message(t_parser *, char *);
bool	save_line(t_parser *, char *);
bool	split_buffer(t_all *, t_client *);
char	*get_substring(char *, int);

/* treatment.c */
bool	treatment(t_parser *, t_all *, t_client *);

/* check general.c */
bool	dspb(char *, bool);
bool	check_special(char);
bool	check_letter(char);
bool	check_digit(char);
bool	check_letterdigit(t_parser *, char *, char);

/* check server_host.c */
bool	check_shortname(t_parser *, char *, char);
bool	check_hostname(t_parser *, char *);
bool	check_servername(t_parser *, char *);

/* check host_ip.c */
bool	check_ip6addr(t_parser *, char *);
bool	check_ip4addr(t_parser *, char *);
bool	check_hostaddr(t_parser *, char *);
bool	check_host(t_parser *, char *);

/* check params_user.c */
bool	check_user(t_parser *, char *);
bool	check_nickname(t_parser *, char *);
bool	check_trailing(t_parser *, char *);
bool	check_middle(t_parser *, char *);

/* Function action */
int	my_nick_channel(t_parser *, t_all *, t_client *);
int	my_nick(t_parser *, t_all *, t_client *);
int	my_join(t_parser *, t_all *, t_client *);
int	my_users(t_parser *, t_all *, t_client *);

/* Function action suite */
int	my_list(t_parser *, t_all *, t_client *);
void	write_msg(t_parser *, t_all *, t_client *);
int	my_msg(t_parser *, t_all *, t_client*);
int	my_part(t_parser *, t_all *, t_client *);
int	my_quit(t_parser *, t_all *, t_client *);
int	my_user(t_parser *, t_all *, t_client *);

#endif /* !PARSER_H_ */
