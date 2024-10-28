/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:12:43 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/27 21:58:42 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/*typedef struct s_command
{
	char				**cmd;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;*/

typedef struct s_mini
{
	char			*cmd;
	char			*str;
	char			*file;
	int				redirection;
	struct s_mini	*next;
	char			**hist;
}	t_mini;

//execution.c
void	execution(t_mini shell, char **env);

//command.c
void	free_array(char **array);
char	*ft_findpath(char *desired_var, char **env);
char	*ft_join_path(const char *directory, const char *cmd_name);
char	*build_command_path(char *cmd_name, char **env);
void	ft_execute(char *cmd, char *env[]);

//parsing.c
bool	check_quotation(char *str);
t_mini	parsing(char *input);

//util.c
bool	check_quotation(char *str);
int		check_dollar_sign(char *str);
char	*get_envp(char *str, char **envp)

//copy_envp.c
char	**copy_array(char **array, bool plusone);

//built_ins_1.c
void	ft_echo(char *cmd, char *str);
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(char **envp);

//built_ins_2.c
void	ft_unset(char *var, char **envp);

#endif