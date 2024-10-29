# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 18:15:11 by fvargas           #+#    #+#              #
#    Updated: 2024/10/29 01:12:27 by janaebyrne       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread -lreadline -Iinc -I$(LIBFT_DIR)

DEBUG_FLAGS = -g

SRC_DIR = srcs
EXECUTION_DIR = $(SRC_DIR)/execution
PARSING_DIR = $(SRC_DIR)/parsing
UTILS_DIR = $(SRC_DIR)/utils

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = $(SRC_DIR)/main.c \
      $(UTILS_DIR)/util.c \
      $(EXECUTION_DIR)/execution.c \
      $(EXECUTION_DIR)/built_ins_1.c \
      $(EXECUTION_DIR)/built_ins_2.c \
      $(EXECUTION_DIR)/ft_execute.c \
      $(UTILS_DIR)/copy_envp.c \
      $(PARSING_DIR)/parsing.c \

INC = inc/minishell.h

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(LIBFT)

debug: $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(NAME) $(LIBFT)

clean:
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) clean

re: clean all

.PHONY: all clean re
