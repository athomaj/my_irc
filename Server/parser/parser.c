/*
** parser.c for  in /home/maillo_a/rendu/PSU_2014_myirc/server/parser
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Wed Apr  8 20:57:28 2015 Flavien Maillot
** Last update Sun Apr 12 21:16:29 2015 julien athomas
*/

#include "parser.h"

char		*get_substring(char *string, int length)
{
  char		*new_string;

  if ((new_string = malloc(sizeof(char) * (length + 1))) == NULL)
    return (NULL);
  bzero(new_string, length + 1);
  strncpy(new_string, string, length);
  return (new_string);
}

bool		save_line(t_parser *parser, char *buffer)
{
  if (parser->line != NULL)
    free(parser->line);
  if ((parser->line = malloc(sizeof(char) * (parser->pos + 2))) == NULL)
    return (false);
  bzero(parser->line, parser->pos + 2);
  strncpy(parser->line, buffer, parser->pos - 1);
  return (true);
}

bool		parse_message(t_parser *parser, char *message)
{
  if (message == NULL)
    return (false);
  if (check_prefixe(parser, message) == true &&
      check_command(parser, message) == true &&
      check_params(parser, message) == true &&
      check_crlf(parser, message) == true)
    return (true);
  return (false);
}

bool		split_buffer(t_all *all, t_client *client)
{
  t_parser	parser;

  printf("Analyse : %s\n", all->buf.buf);
  parser.line = NULL;
  parser.pos = 0;
  if (parse_message(&parser, &(all->buf.buf[all->buf.init_idx])) == true)
    {
      if (DEBUG == true)
	{
	  printf("\nresultat :\n");
	  if (parser.prefix != NULL)
	    printf("préfixe :%s\n", parser.prefix);
	  if (parser.command != NULL)
	    printf("command :%s\n", parser.command);
	  if (parser.params != NULL)
	    printf("param :%s\n", parser.params);
	}
      treatment(&parser, all, client);
    }
  else
    {
      write_msg(&parser, all, client);
      printf("failed\n");
    }
  return (true);
}
