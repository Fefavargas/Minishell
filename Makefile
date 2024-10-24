# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 18:15:11 by fvargas           #+#    #+#              #
#    Updated: 2024/10/24 20:58:23 by janaebyrne       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread -lreadline -Iinc

DEBUG_FLAGS = -g

SRC_DIR = srcs
EXECUTION_DIR = $(SRC_DIR)/execution
PARSING_DIR = $(SRC_DIR)/parsing
UTILS_DIR = $(SRC_DIR)/utils

SRC = $(SRC_DIR)/main.c $(UTILS_DIR)/util.c $(UTILS_DIR)/ft_split.c $(EXECUTION_DIR)/builtins.c $(EXECUTION_DIR)/execution.c $(PARSING_DIR)/parsing.c
# parsing.c 

INC = inc/minishell.h

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

debug: $(SRC)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re