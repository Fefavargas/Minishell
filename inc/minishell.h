/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:12:43 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/24 18:45:31 by janaebyrne       ###   ########.fr       */
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
# include <stdbool.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>


#define REDIRECT_INPUT  1  // Represents '<' 
#define REDIRECT_OUTPUT 2  // Represents '>'
#define REDIRECT_APPEND 3  // Represents '>>' 
#define REDIRECT_HEREDOC 4 // Represents '<<'

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
	char			**local_envp;
	struct s_mini	*next;
	char			**hist;
	
}	t_mini;

//execution.c
void	execute_commands(t_mini shell);

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
char	*get_envp(char *str, char **envp);

//copy_envp.c
char	**copy_array(char **array, bool plusone);

//built_ins
void	ft_echo(char *cmd, char *str);
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(char **envp);
void	ft_unset(char *var, char **envp);
int	find_path_index(char *desired_var, char **envp);
void ft_export(char *var, char *var_value, char** local_envp);
void set_env_var(const char *name, const char *value, char **local_envp);

//redirection.c
int open_file(const char *file, int flags, mode_t mode);
void redirect_fd(int oldfd, int newfd);
void setup_redirection(t_mini *node);
int handle_heredoc(char *delimiter);

//pipeline.c
void execute_pipeline(t_mini *node);
void handle_parent_process(int *pipefd, int *prev_pipefd);
void handle_child_process(t_mini *node, int *pipefd, int *prev_pipefd);
void wait_for_children(void);

//pipeline_utils.c
int count_commands(t_mini *commands);
void setup_pipe(int *pipefds);
void close_pipe(int *pipefds);


//delete later
void setup_test_pipeline(t_mini **pipeline);

#endif
