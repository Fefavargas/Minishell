/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:12:43 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/22 18:14:42 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include<stddef.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_mini
{
	char			*cmd;
	char			*str;
	char			*file;
	int				redirection;
	struct s_mini	*next;
}t_mini;

//execution.c
void	execution(t_mini shell);
//parsing.c
t_mini	parsing(char *input);
//util.c
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);

#endif