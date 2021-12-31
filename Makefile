# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malmeida <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 11:29:20 by malmeida          #+#    #+#              #
#    Updated: 2021/12/27 11:54:49 by malmeida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	+=	--quiet

			# Library Name #
NAME		=
BBSHELL		=	bbshell

			# Mandatory Variables #
SRC_BBSHELL	=	./srcs/*.c

			# Libft Variables #
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

			# Compiling Variables #
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INC			= -I./includes -lreadline -I$(LIBFT_DIR)
RM			= rm -f
FSANITIZE	= -g -fsanitize=address
RDFLAG		= -L/Users/$(shell whoami)/.brew/opt/readline/lib -lreadline
RDFLAGER	= -I/Users/$(shell whoami)/.brew/opt/readline/include

			# Color Variables #
GREEN		= \e[0;32m
RED			= \e[0;31m
YELLOW		= \e[0;33m
RESET		= \e[0m

all: $(BBSHELL)

$(NAME): all

$(BBSHELL): $(LIBFT) $(SRC_BBSHELL)
	@ $(CC) $(CFLAG) $(SRC_BBSHELL) $(LIBFT) $(INC) -o $(BBSHELL) $(RDFLAG) $(RDFLAGER)
	@printf "[$(GREEN)SUCCESS$(RESET)] bbshell compiled.\n"

$(LIBFT):
	@ $(MAKE) -C ./libft

clean:
	@ $(RM) $(BBSHELL)
	@printf "[$(YELLOW)SUCCESS$(RESET)] Executable removed.\n"

fclean:
	@ $(RM) $(BBSHELL)
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@printf "[$(YELLOW)SUCCESS$(RESET)] Executable removed.\n"
	@printf "[$(YELLOW)SUCCESS$(RESET)] Libft removed.\n"

re: fclean all

mandatory:	$(PHILO)

m:	mandatory