# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 18:15:11 by fvargas           #+#    #+#              #
#    Updated: 2024/10/23 17:48:14 by janaebyrne       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread -lreadline

DEBUG_FLAGS = -g

SRC = main.c util.c command.c ft_split.c ft_echo.c execution.c
# parsing.c 

INC = minishell.h

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

debug: $(SRC)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re