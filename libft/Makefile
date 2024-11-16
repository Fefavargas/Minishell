# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 23:46:46 by fvargas           #+#    #+#              #
#    Updated: 2024/07/17 23:52:09 by fvargas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			libft.a
CC =			cc
CFLAGS =		-Wall -Wextra -Werror

SRCS =			ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strncmp.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strnstr.c \
				ft_memset.c \
				ft_memchr.c \
				ft_memcpy.c \
				ft_memcmp.c \
				ft_memmove.c \
				ft_bzero.c \
				ft_atoi.c \
				ft_strdup.c \
				ft_calloc.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				get_next_line.c \
				get_next_line_utils.c \

OBJS =			${SRCS:.c=.o}

# Target 'all' is the default target, building library specified by $(NAME).
all:	$(NAME)

# Target $(NAME) depends on object files $(OBJS),
# and the 'ar rc' command creates the library.
$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)

# Target 'clean' removes object files.
clean:
	rm -f $(OBJS)

# Target 'fclean' depends on 'clean' and removes the library as well.
fclean:	clean
	rm -f $(NAME)

# Target 're' depends on 'fclean' and 'all', rebuilding the project from scratch.
re:	fclean all