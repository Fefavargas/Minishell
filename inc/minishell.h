/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:12:43 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/25 19:57:42 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include<stddef.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>
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
void	execution(t_mini shell, char **env);

//command.c
void	free_array(char **array);
char	*ft_findpath(char *desired_var, char **env);
char	*ft_join_path(const char *directory, const char *cmd_name);
char	*build_command_path(char *cmd_name, char **env);
void	ft_execute(char *cmd, char *env[]);

//parsing.c
t_mini	parsing(char *input);

//util.c
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

//ft_split.c
char	**ft_split(char const *s, char c);

//copy_envp.c
char	**copy_envp(char **envp);

//built_ins_1.c
void ft_echo(char *cmd, char *str);
void ft_cd(char *path);
void ft_pwd(void);
void ft_export(char **envp);

//built_ins_2.c
void ft_unset(char *var, char **envp);


#endif