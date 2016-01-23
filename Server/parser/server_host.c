/*
** server_host.c for  in /home/maillo_a/rendu/PSU_2014_myirc/server/parser
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Fri Apr 10 16:41:22 2015 Flavien Maillot
** Last update Sun Apr 12 15:58:57 2015 Flavien Maillot
*/

#include "parser.h"

bool		check_shortname(t_parser *parser, char *shortname, char c)
{
  if (DEBUG == true)
    printf("\ncheck_shortname : %s\n", &(shortname[parser->pos]));
  while (check_letterdigit(parser, shortname, '-') == true);
  if (check_letterdigit(parser, shortname, c) == true)
    {
      --(parser->pos);
      return (dspb("shortname2", true));
    }
  return (dspb("shortname", false));
}

bool		check_hostname(t_parser *parser, char *hostname)
{
  if (DEBUG == true)
    printf("check_hostname\n");
  while (check_shortname(parser, hostname, '.') == true)
    if (hostname[parser->pos] == '.')
      ++(parser->pos);
  if (check_shortname(parser, hostname, ' ') == true)
    return (dspb("hostname", true));
  return (dspb("hostname", false));
}

bool		check_servername(t_parser *parser, char *servername)
{
  if (DEBUG == true)
    printf("check_servername\n");
  if (check_hostname(parser, servername) == true)
    return (dspb("servername", true));
  return (dspb("servername", false));
}
