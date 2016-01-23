##
## Makefile for  in /Users/julien/rendu/PSU_2014_myirc
##
## Made by julien athomas
## Login   <julien@epitech.net>
##
## Started on  Mon Apr  6 10:24:46 2015 julien athomas
## Last update Sun Apr 12 22:49:54 2015 julien athomas
##

SRC=		main.c					\
		cbuffer.c				\
		irc_client.c				\
		irc_gen.c				\
		irc_serv_ext.c				\
		Server/parser/parser.c			\
		Server/parser/first_check.c		\
		Server/parser/general.c			\
		Server/parser/host_ip.c			\
		Server/parser/params_user.c		\
		Server/parser/server_host.c		\
		Server/treatment.c			\
		Server/function/function_part1.c	\
		Server/function/function_part2.c	\
		Server/function/channel.c		\
		Server/function/my_msg.c		\

SRC2=		Client/client.c				\
		Client/client_fptr.c			\
		Client/client_fptr_next.c		\
		Client/init_client.c			\

OBJ=		$(SRC:.c=.o)

OBJ2=		$(SRC2:.c=.o)

NAME=		bin/server

NAME2=		bin/client

CFLAGS=		-W -Wall -Wextra -Werror


all:		$(NAME) $(NAME2)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ)

$(NAME2):	$(OBJ2)
		gcc -o $(NAME2) $(OBJ2)

clean:
		rm -f $(OBJ)
		rm -f $(OBJ2)

fclean:		clean
		rm -f $(NAME)
		rm -f $(NAME2)

re:		fclean all

.PHONY:		all re fclean clean
