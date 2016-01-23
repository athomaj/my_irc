/*
** first_check.c for  in /home/maillo_a/rendu/PSU_2014_myirc/server/parser
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Sun Apr 12 16:15:16 2015 Flavien Maillot
** Last update Sun Apr 12 21:36:00 2015 Flavien Maillot
*/

#include "parser.h"

bool		check_prefixe(t_parser *parser, char *prefixe)
{
  int		size;

  if (DEBUG == true)
    printf("check_prefixe [%s]\n", prefixe);
  parser->start = parser->pos;
  if (prefixe[0] == ':')
    {
      ++(parser->pos);
      if ((check_servername(parser, prefixe) == false &&
           check_nickname(parser, prefixe) == false))
	return (false);
      if (prefixe[parser->pos] != ' ')
	return (false);
      ++(parser->pos);
    }
  parser->end = parser->pos;
  size = parser->end - parser->start;
  if (size > 0)
    parser->prefix = get_substring(&(prefixe[parser->start]), size);
  else
    parser->prefix = NULL;
  return (true);
}

bool		check_command(t_parser *parser, char *command)
{
  int		i;
  int		size;

  parser->start = parser->pos;
  i = 0;
  if (check_letter(command[parser->pos]) == true)
    while (check_letter(command[++(parser->pos)]) == true);
  else if (check_digit(command[parser->pos]) == true)
    {
      ++i;
      while (++i && check_digit(command[++(parser->pos)]) == true);
      if (i != 4)
	return (false);
    }
  else
    return (false);
  parser->end = parser->pos;
  size = parser->end - parser->start;
  if (size > 0)
    parser->command = get_substring(&(command[parser->start]), size);
  else
    parser->command = NULL;
  parser->start = parser->pos;
  return (true);
}

bool		check_params(t_parser *parser, char *param)
{
  int		size;

  if (DEBUG == true)
    printf("\n\ncheck_params : >%s\n", &(param[parser->pos]));
  if (param[parser->pos] == ' ')
    {
      if (param[++(parser->pos)] == ':')
	++(parser->pos);
      if (check_middle(parser, param) == false)
	{
	  if (check_trailing(parser, param) == false)
	    return (false);
	}
      else
	return (true);
    }
  (param[parser->start + 1] == ':') ? (parser->start += 2) :
    (parser->start += 1);
  parser->end = parser->pos;
  size = parser->end - parser->start;
  if (size > 0)
    parser->params = get_substring(&(param[parser->start]), size);
  else
    parser->params = NULL;
  return (true);
}

bool		check_crlf(t_parser *parser, char *buffer)
{
  if (DEBUG == true)
    printf("check_crlf\n");
  if (buffer[parser->pos] == '\r' && ++(parser->pos) &&
      buffer[parser->pos] == '\n')
    {
      if (save_line(parser, buffer) == false)
	return (false);
      return (dspb("crlf", true));
    }
  else
    return (dspb("crlf", false));
}
