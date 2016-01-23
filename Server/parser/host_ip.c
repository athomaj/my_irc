/*
** host_ip.c for  in /home/maillo_a/rendu/PSU_2014_myirc/server/parser
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Fri Apr 10 16:41:35 2015 Flavien Maillot
** Last update Sun Apr 12 16:50:54 2015 Flavien Maillot
*/

#include "parser.h"

bool		check_ip4addr(t_parser *parser, char *ip)
{
  int		dot;
  int		digit;
  int		end;

  dot = 0;
  digit = 0;
  end = 0;
  while (end == 0 && ip[parser->pos] != 0)
    {
      while (check_digit(ip[parser->pos]) == true && ++digit > 0 &&
	     ++(parser->pos));
      if (dot == 3)
	end = 1;
      if (dot != 3 && (ip[parser->pos] != '.' || ++dot < 0 ||
		       ++(parser->pos) < 0))
	{
	  parser->pos -= (dot + digit);
	  return (false);
	}
    }
  if (dot == 3)
    return (dspb("ip4", true));
  parser->pos -= (dot + digit);
  return (false);
}

bool		check_ip6addr(__attribute__((unused))t_parser *parser,
			      __attribute__((unused))char *ip)
{
  if (DEBUG == true)
    printf("check_ip6\n");
  return (false);
}

bool		check_hostaddr(t_parser *parser, char *hostaddr)
{
  if (DEBUG == true)
    printf("check_hostaddr\n");
  if (check_ip4addr(parser, hostaddr) == false &&
      check_ip6addr(parser, hostaddr) == false)
    return (dspb("hostaddr", false));
  return (dspb("hostaddr", true));
}

bool		check_host(t_parser *parser, char *host)
{
  if (check_hostaddr(parser, host) == false)
    return (false);
  return (true);
}
