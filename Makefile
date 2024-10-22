# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 18:15:11 by fvargas           #+#    #+#              #
#    Updated: 2024/10/22 18:22:58 by fvargas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread -lreadline

DEBUG_FLAGS = -g

SRC = main.c util.c 
# parsing.c execution.c

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