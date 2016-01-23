/*
** server.h for  in /Users/julien/rendu/PSU_2014_myirc
** 
** Made by julien athomas
** Login   <julien@epitech.net>
** 
** Started on  Mon Apr  6 11:05:00 2015 julien athomas
** Last update Thu Apr 16 13:06:24 2015 julien athomas
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>
# include "Server/parser/parser.h"

# define SERVER_ID 1
# define CLIENT_ID 2

# define UNUSED __attribute__((unused))
# define NB_COM 8

# include "cbuffer.h"

/*
** error code
*/
# define ERR_NOSUCHNICK "401 ERR_NOSUCHNICK"
# define ERR_NOSUCHSERVER "402 ERR_NOSUCHSERVER"
# define ERR_NOSUCHCHANNEL "403 ERR_NOSUCHCHANNEL"
# define ERR_CANNOTSENDTOCHAN "404 ERR_CANNOTSENDTOCHAN"
# define ERR_TOOMANYCHANNELS "405 ERR_TOOMANYCHANNELS"
# define ERR_WASNOSUCHNICK "406 ERR_WASNOSUCHNICK"
# define ERR_TOOMANYTARGETS "407 ERR_TOOMANYTARGETS"
# define ERR_NOORIGIN "409 ERR_NOORIGIN"
# define ERR_NORECIPIENT "411 ERR_NORECIPIENT"
# define ERR_NOTEXTTOSEND "412 ERR_NOTEXTTOSEND"
# define ERR_NOTOPLEVEL "413 ERR_NOTOPLEVEL"
# define ERR_WILDTOPLEVEL "414 ERR_WILDTOPLEVEL"
# define ERR_UNKNOWNCOMMAND "421 ERR_UNKNOWNCOMMAND"
# define ERR_NOMOTD "422 ERR_NOMOTD"
# define ERR_NOADMININFO "423 ERR_NOADMININFO"
# define ERR_FILEERROR "424 ERR_FILEERROR"
# define ERR_NONICKNAMEGIVEN "431 ERR_NONICKNAMEGIVEN"
# define ERR_ERRONEUSNICKNAME "432 ERR_ERRONEUSNICKNAME"
# define ERR_NICKNAMEINUSE "433 ERR_NICKNAMEINUSE"
# define ERR_NICKCOLLISION "436 ERR_NICKCOLLISION"
# define ERR_USERNOTINCHANNEL "441 ERR_USERNOTINCHANNEL"
# define ERR_NOTONCHANNEL "442 ERR_NOTONCHANNEL"
# define ERR_USERONCHANNEL "443 ERR_USERONCHANNEL"
# define ERR_NOLOGIN "444 ERR_NOLOGIN"
# define ERR_SUMMONDISABLED "445 ERR_SUMMONDISABLED"
# define ERR_USERSDISABLED "446 ERR_USERSDISABLED"
# define ERR_NOTREGISTERED "451 ERR_NOTREGISTERED"
# define ERR_NEEDMOREPARAMS "461 ERR_NEEDMOREPARAMS"
# define ERR_ALREADYREGISTRED "462 ERR_ALREADYREGISTRED"
# define ERR_NOPERMFORHOST "463 ERR_NOPERMFORHOST"
# define ERR_PASSWDMISMATCH "464 ERR_PASSWDMISMATCH"
# define ERR_YOUREBANNEDCREEP "465 ERR_YOUREBANNEDCREEP"
# define ERR_KEYSET "467 ERR_KEYSET"
# define ERR_CHANNELISFULL "471 ERR_CHANNELISFULL"
# define ERR_UNKNOWNMODE "472 ERR_UNKNOWNMODE"
# define ERR_INVITEONLYCHAN "473 ERR_INVITEONLYCHAN"
# define ERR_BANNEDFROMCHAN "474 ERR_BANNEDFROMCHAN"
# define ERR_BADCHANNELKEY "475 ERR_BADCHANNELKEY"
# define ERR_NOPRIVILEGES "481 ERR_NOPRIVILEGES"
# define ERR_CHANOPRIVSNEEDED "482 ERR_CHANOPRIVSNEEDED"
# define ERR_CANTKILLSERVER "483 ERR_CANTKILLSERVER"
# define ERR_NOOPERHOST "491 ERR_NOOPERHOST"
# define ERR_UMODEUNKNOWNFLAG "501 ERR_UMODEUNKNOWNFLAG"
# define ERR_USERSDONTMATCH "502 ERR_USERSDONTMATCH"

/*
** reply code
*/
# define RPL_NONE "300 RPL_NONE"
# define RPL_USERHOST "302 RPL_USERHOST"
# define RPL_ISON "303 RPL_ISON"
# define RPL_AWAY "301 RPL_AWAY"
# define RPL_UNAWAY "305 RPL_UNAWAY"
# define RPL_NOWAWAY "306 RPL_NOWAWAY"
# define RPL_WHOISUSER "311 RPL_WHOISUSER"
# define RPL_WHOISSERVER "312 RPL_WHOISSERVER"
# define RPL_WHOISOPERATOR "313 RPL_WHOISOPERATOR"
# define RPL_WHOISIDLE "317 RPL_WHOISIDLE"
# define RPL_ENDOFWHOIS "318 RPL_ENDOFWHOIS"
# define RPL_WHOISCHANNELS "319 RPL_WHOISCHANNELS"
# define RPL_WHOWASUSER "314 RPL_WHOWASUSER"
# define RPL_ENDOFWHOWAS "369 RPL_ENDOFWHOWAS"
# define RPL_LISTSTART "321 RPL_LISTSTART"
# define RPL_LIST "322 RPL_LIST"
# define RPL_LISTEND "323 RPL_LISTEND"
# define RPL_CHANNELMODEIS "324 RPL_CHANNELMODEIS"
# define RPL_NOTOPIC "331 RPL_NOTOPIC"
# define RPL_TOPIC "332 RPL_TOPIC"
# define RPL_INVITING "341 RPL_INVITING"
# define RPL_SUMMONING "342 RPL_SUMMONING"
# define RPL_VERSION "351 RPL_VERSION"
# define RPL_WHOREPLY "352 RPL_WHOREPLY"
# define RPL_ENDOFWHO "315 RPL_ENDOFWHO"
# define RPL_NAMREPLY "353 RPL_NAMREPLY"
# define RPL_ENDOFNAMES "366 RPL_ENDOFNAMES"
# define RPL_LINKS "364 RPL_LINKS"
# define RPL_ENDOFLINKS "365 RPL_ENDOFLINKS"
# define RPL_BANLIST "367 RPL_BANLIST"
# define RPL_ENDOFBANLIST "368 RPL_ENDOFBANLIST"
# define RPL_INFO "371 RPL_INFO"
# define RPL_ENDOFINFO "374 RPL_ENDOFINFO"
# define RPL_MOTDSTART "375 RPL_MOTDSTART"
# define RPL_MOTD "372 RPL_MOTD"
# define RPL_ENDOFMOTD "376 RPL_ENDOFMOTD"
# define RPL_YOUREOPER "381 RPL_YOUREOPER"
# define RPL_REHASHING "382 RPL_REHASHING"
# define RPL_TIME "391 RPL_TIME"
# define RPL_USERSSTART "392 RPL_USERSSTART"
# define RPL_USERS "393 RPL_USERS"
# define RPL_ENDOFUSERS "394 RPL_ENDOFUSERS"
# define RPL_NOUSERS "395 RPL_NOUSERS"

/*
** trace code
*/
# define RPL_TRACELINK "200 RPL_TRACELINK"
# define RPL_TRACECONNECTING "201 RPL_TRACECONNECTING"
# define RPL_TRACEHANDSHAKE "202 RPL_TRACEHANDSHAKE"
# define RPL_TRACEUNKNOWN "203 RPL_TRACEUNKNOWN"
# define RPL_TRACEOPERATOR "204 RPL_TRACEOPERATOR"
# define RPL_TRACEUSER "205 RPL_TRACEUSER"
# define RPL_TRACESERVER "206 RPL_TRACESERVER"
# define RPL_TRACENEWTYPE "208 RPL_TRACENEWTYPE"
# define RPL_TRACELOG "261 RPL_TRACELOG"
# define RPL_STATSLINKINFO "211 RPL_STATSLINKINFO"
# define RPL_STATSCOMMANDS "212 RPL_STATSCOMMANDS"
# define RPL_STATSCLINE "213 RPL_STATSCLINE"
# define RPL_STATSNLINE "214 RPL_STATSNLINE"
# define RPL_STATSILINE "215 RPL_STATSILINE"
# define RPL_STATSKLINE "216 RPL_STATSKLINE"
# define RPL_STATSYLINE "218 RPL_STATSYLINE"
# define RPL_ENDOFSTATS "219 RPL_ENDOFSTATS"
# define RPL_STATSLLINE "241 RPL_STATSLLINE"
# define RPL_STATSUPTIME "242 RPL_STATSUPTIME"
# define RPL_STATSOLINE "243 RPL_STATSOLINE"
# define RPL_STATSHLINE "244 RPL_STATSHLINE"
# define RPL_UMODEIS "221 RPL_UMODEIS"
# define RPL_LUSERCLIENT "251 RPL_LUSERCLIENT"
# define RPL_LUSEROP "252 RPL_LUSEROP"
# define RPL_LUSERUNKNOWN "253 RPL_LUSERUNKNOWN"
# define RPL_LUSERCHANNELS "254 RPL_LUSERCHANNELS"
# define RPL_LUSERME "255 RPL_LUSERME"
# define RPL_ADMINME "256 RPL_ADMINME"
# define RPL_ADMINLOC1 "257 RPL_ADMINLOC1"
# define RPL_ADMINLOC2 "258 RPL_ADMINLOC2"
# define RPL_ADMINEMAIL "259 RPL_ADMINEMAIL"

typedef struct s_client		t_client;
typedef struct s_channel	t_channel;
typedef struct s_all		t_all;

typedef struct	s_user
{
  char		*nick;
  char		*channel;
  char		*user;
  char		*pass;
  char		*prefix;
}		t_user;

struct			s_client
{
  struct sockaddr_in	s_in_c;
  socklen_t		s_size;
  t_user		*user;
  int			fd;
  int			type;
  int			idx;
  int			len;
  t_client		*next;
  void			(*fptr)(t_all *, t_client *);
  void			(*write_fptr)(t_all *, t_client *);
  char			*server;
  t_channel		*channel;
};

struct		s_channel
{
  char		*name;
  char		*topic;
  t_client	*client;
  t_channel	*next;
};

typedef struct	s_fd
{
  fd_set	fd_read;
  fd_set	fd_write;
  int		fd_s;
  int		max_fd;
}		t_fd;

struct		s_all
{
  t_fd		*fds;
  t_channel	*channel;
  t_client	*actual;
  t_cbuffer	buf;
};

bool	split_buffer(t_all *, t_client *);
int	new_channel(t_all *all, char *name);
void	add_client_to_channel(t_all *, t_channel *channel, t_client *client);
void	remove_client_from_channel(t_channel **channel, t_client *client);

/* irc_serv_ext.c */
void	serv_ptr(t_all *all, UNUSED t_client *client);
void	check_fd(t_all *all);

/* irc_gen.c */
t_user*	add_user();
void	dump_channels(t_channel *tmp);
void	my_write(t_all *all, t_client *client);
int	add_fd(t_all *all, int type, int fd, void (*fptr)(t_all *, t_client *));

/* irc_client.c */
void	remove_client(t_all *all, t_client *client);
void	client_ptr(t_all *all, t_client *client);
int	receive_clients(int fd);

/* main.c */
int	init_proto(struct protoent **pe, struct sockaddr_in *s_in, int port);
int	init_socket(struct protoent *pe, struct sockaddr_in *s_in);
int	set_fds(t_all *all, fd_set *fd_read);

#endif /* !SERVER_H_ */
