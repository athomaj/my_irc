/*
** general.c for  in /home/maillo_a/rendu/PSU_2014_myirc/server/parser
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Fri Apr 10 16:40:53 2015 Flavien Maillot
** Last update Sun Apr 12 20:20:46 2015 Flavien Maillot
*/

#include "parser.h"

bool		dspb(char *str, bool value)
{
  if (DEBUG == true)
    printf("%s %s\n", str, (value == true) ? ("true") : ("false"));
  return (value);
}

bool		check_special(char c)
{
  if ((c >= '[' && c <= '`') || (c >= '{' && c <= '}'))
    return (true);
  return (false);
}

bool		check_letter(char c)
{
  if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
    return (false);
  return (true);
}

bool		check_digit(char c)
{
  if (c < '0' || c > '9')
    return (false);
  return (true);
}

bool		check_letterdigit(t_parser *parser, char *string, char end)
{
  int		i;

  if (DEBUG == true)
    printf("check_letterdigit : %s\n", &(string[parser->pos]));
  i = 0;
  if (check_letter(string[parser->pos]) == false &&
      check_digit(string[parser->pos]) == false)
    return (false);
  while (string[++(parser->pos)] != end && string[parser->pos] != 0)
    {
      ++i;
      if (check_letter(string[parser->pos]) == false &&
	  check_digit(string[parser->pos]) == false)
	{
	  parser->pos -= i;
	  return (dspb("letter", false));
	}
    }
  if (string[parser->pos] != end)
    {
      parser->pos -= i;
      return (dspb("letter", false));
    }
  ++(parser->pos);
  return (dspb("letter", true));
}
