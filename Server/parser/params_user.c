/*
** params_user.c for  in /home/maillo_a/rendu/PSU_2014_myirc/server/parser
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Fri Apr 10 16:42:33 2015 Flavien Maillot
** Last update Sun Apr 12 17:59:34 2015 Flavien Maillot
*/

#include "parser.h"

bool		check_user(t_parser *parser, char *user)
{
  int		i;

  if (DEBUG == true)
    printf("check_user\n");
  i = 0;
  while (user[parser->pos] != 0 &&
	 user[parser->pos] != '\r' &&
	 user[parser->pos] != '\n' &&
	 user[parser->pos] != ' ' &&
	 user[parser->pos] != '@')
    {
      ++(parser->pos);
      ++i;
    }
  if (i >= 1)
    return (dspb("user", true));
  return (dspb("user", false));
}

bool		check_user_and_host(t_parser *parser, char *nickname)
{
  if (nickname[parser->pos] == '!')
    {
      ++(parser->pos);
      if (check_user(parser, nickname) == false)
	return (false);
    }
  if (nickname[parser->pos] == '@')
    {
      ++(parser->pos);
      if (check_host(parser, nickname) == false)
	return (false);
    }
  return (true);
}

bool		check_nickname(t_parser *parser, char *nickname)
{
  int		i;

  if (DEBUG == true)
    printf("check_nickname : %s\n", nickname);
  i = 0;
  while (nickname[parser->pos] != '!' &&
	 nickname[parser->pos] != '@' &&
	 nickname[parser->pos] != 0)
    {
      ++i;
      if (check_letter(nickname[parser->pos]) == false &&
	  check_digit(nickname[parser->pos]) == false &&
	  check_special(nickname[parser->pos]) == false)
	{
	  parser->pos -= i;
	  return (false);
	}
      ++(parser->pos);
    }
  if (check_user_and_host(parser, nickname) == false)
    return (false);
  return (true);
}

bool		check_middle(t_parser *parser, char *middle)
{
  int		i;

  if (DEBUG == true)
    printf("check_middle\n");
  i = 0;
  while (middle[parser->pos] != 0 && middle[parser->pos] != '\r' &&
	 middle[parser->pos] != '\n' &&
         middle[parser->pos] != ' ')
    {
      ++i;
      ++(parser->pos);
    }
  if (middle[parser->pos] == ' ')
    {
      check_params(parser, middle);
      return (dspb("middle", true));
    }
  parser->pos -= i;
  return (dspb("middle", false));
}

bool		check_trailing(t_parser *parser, char *trailing)
{
  int		i;

  if (DEBUG == true)
    printf("check_trailing\n");
  i = 0;
  while (trailing[parser->pos] != 0 &&
	 trailing[parser->pos] != '\r' &&
	 trailing[parser->pos] != '\n')
    {
      ++i;
      ++(parser->pos);
    }
  if (i == 0)
    return (dspb("trailing", false));
  return (dspb("trailing", true));
}
