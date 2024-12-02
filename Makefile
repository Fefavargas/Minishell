# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 18:15:11 by fvargas           #+#    #+#              #
#    Updated: 2024/11/29 15:48:33 by janaebyrne       ###   ########.fr        #
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
      $(EXECUTION_DIR)/built_ins/ft_echo.c \
      $(EXECUTION_DIR)/built_ins/ft_cd.c \
      $(EXECUTION_DIR)/built_ins/ft_execute.c \
      $(EXECUTION_DIR)/built_ins/ft_env.c \
      $(EXECUTION_DIR)/built_ins/ft_export.c \
      $(EXECUTION_DIR)/built_ins/ft_unset.c \
      $(EXECUTION_DIR)/built_ins/ft_pwd.c \
      $(EXECUTION_DIR)/redirection.c \
      $(EXECUTION_DIR)/pipeline.c \
      $(EXECUTION_DIR)/pipeline_utils.c \
      $(EXECUTION_DIR)/main_executor.c \
      $(UTILS_DIR)/copy_envp.c \
      $(PARSING_DIR)/parsing.c \
      
      

INC = inc/minishell.h

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) -L$(LIBFT_DIR) -lft

debug: $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRC) -o $(NAME) $(LIBFT)

clean:
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean re
