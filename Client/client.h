/*
** client.h for  in /home/maillo_a/rendu/PSU_2014_myirc/client
** 
** Made by Flavien Maillot
** Login   <maillo_a@epitech.net>
** 
** Started on  Sun Apr 12 21:38:01 2015 Flavien Maillot
** Last update Sun Apr 12 22:11:07 2015 Flavien Maillot
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

/* init_client.c */
void		init_servco(int *, char *, int);
void		init_fds(fd_set *, int);
void		init_fptr(void (*fptr[7])(char buf[515], int *), char *tab[7]);
int		init_connection();

/* client_fptr.c */
void		my_server(char buf[515], int *);
void		my_nick(char buf[515], int *);
void		my_list(char buf[515], int *);
void		my_join(char buf[515], int *);
void		my_part(char buf[515], int *);

/* client_fptr_next.c */
void		my_users(char buf[515], int *);
void		my_msg(char buf[515], int *);

/* client.c*/
void		check_fptr(void (*fptr[7])(char buf[515], int *),
			   char *tab[7], char buf[515], int *fd);
int		read_stdin(int *fd, void (*fptr[7])(char buf[515], int *),
			   char *tab[7]);
int		read_socket(int *);
int		check_fds(fd_set *, int *, void (*fptr[7])
			  (char buf[515], int *), char *tab[7]);

#endif /* !CLIENT_H_ */
