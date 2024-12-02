/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyrne <jbyrne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:12:43 by fvargas           #+#    #+#             */
/*   Updated: 2024/12/02 15:58:29 by jbyrne           ###   ########.fr       */
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


/*program parameters*/
# define KEEP_NONE -1
# define KEEP_INPUT 0
# define KEEP_OUTPUT 1
# define KEEP_BOTH 2


#define REDIRECT_INPUT  1  // Represents '<'
#define REDIRECT_OUTPUT 2  // Represents '>'
#define REDIRECT_APPEND 3  // Represents '>>'
#define REDIRECT_HEREDOC 4 // Represents '<<'

#define	SIGINT		2	/* Interactive attention signal.  */
#define	SIGQUIT		3	/* Quit.  */

typedef struct s_command
{
	char				**cmd;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_mini
{
	char			*cmd;
	char			*str;
	char			*file;
	int				redirection;
	char			**local_envp;
	struct s_mini	*next;
	char			**hist;
	int				input_fd;
	int				output_fd;
	int				exit_status;

}	t_mini;

//execution.c
int	cmd_is_a_builtin(t_mini *node);
int	call_builtin(char *cmd, t_mini *shell);


//command.c
void	free_array(char **array);
char	*ft_findpath(char *desired_var, char **env);
char	*ft_join_path(const char *directory, const char *cmd_name);
char	*build_command_path(char *cmd_name, char **env);
int		ft_execute(char *cmd, char *env[]);

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
int		ft_echo(char *cmd, char *str);
int		ft_cd(char *path);
int		ft_pwd(void);
int		ft_env(char **envp);
int		ft_unset(char *var, char **envp);
int		find_path_index(char *desired_var, char **envp);
int		ft_export(char *var, char *var_value, char** local_envp);
int		set_env_var(const char *name, const char *value, char **local_envp);

//redirection.c
int open_file(const char *file, int flags, mode_t mode);
void redirect_fd(int oldfd, int newfd);
void setup_redirection(t_mini *node);
int handle_heredoc(char *delimiter);

//pipeline.c
int	execute_pipeline(int *fd_pipes, pid_t *pid, t_mini *shell);
int	execute_builtin(int *fd_pipes, int pos, t_mini *shell);
int	execute_nonbuiltin(int *fd_pipes, int pos, int *pid, t_mini *shell);
int	catch_child_execs(pid_t *pid, int num, t_mini *shell, int *fd_pipes);

//pipeline_utils.c
int count_commands(t_mini *commands);
void setup_pipe(int *pipefds);
int close_pipe(int *pipefds);
int	*build_pipes(int fd_out, int fd_in, int cmd_count);
int close_unused_fd(int *fd_pipes, int pos, int keep, int len);
int	*build_pipes(int fd_out, int fd_in, int cmd_count);

//main_executor.c
int	executor(t_mini *shell);


//delete later
void setup_test_pipeline(t_mini **pipeline);

#endif
