/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:08:48 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/29 21:27:57 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	execute_commands(t_mini shell)
// {
// 	int saved_stdout;
// 	int saved_stdin;
	
// 	saved_stdout = dup(STDOUT_FILENO);
// 	saved_stdin = dup(STDIN_FILENO);
	
// 	if (shell.redirection != 0)
// 	{
// 		setup_redirection(&shell);
// 	}
// 	if (ft_strncmp(shell.cmd, "echo", 4) == 0)
// 		ft_echo(shell.cmd, shell.str);
// 	else if (ft_strncmp(shell.cmd, "cd", 2) == 0)
// 		ft_cd(shell.str);
// 	else if (ft_strncmp(shell.cmd, "pwd", 3) == 0)
// 		ft_pwd();
// 	else if (ft_strncmp(shell.cmd, "env", 3) == 0)
// 		ft_env(shell.local_envp);
// 	else if (ft_strncmp(shell.cmd, "unset", 5) == 0)
// 		ft_unset(shell.str, shell.local_envp);
// 	else if (ft_strncmp(shell.cmd, "export", 6) == 0)
// 		ft_export(shell.str, shell.file, shell.local_envp);
// 	else
// 		ft_execute(shell.cmd, shell.local_envp);
// 	dup2(saved_stdin, STDIN_FILENO);
//     dup2(saved_stdout, STDOUT_FILENO);
//     close(saved_stdin);
//     close(saved_stdout);
// }


int	cmd_is_a_builtin(t_mini *node)
{
	if (!ft_strncmp(node->cmd, "echo", 4)
		|| !ft_strncmp(node->cmd, "cd", 2)
		|| !ft_strncmp(node->cmd, "pwd", 3)
		|| !ft_strncmp(node->cmd, "export", 6)
		|| !ft_strncmp(node->cmd, "unset", 5)
		|| !ft_strncmp(node->cmd, "env", 3)
		|| !ft_strncmp(node->cmd, "exit", 4))
		return (1);
	else
		return (0);
}


int	call_builtin(char *cmd, t_mini *shell)
{
	int		exit_code;
	exit_code = 0;

	if (ft_strncmp(cmd, "echo", 4) == 0)
		exit_code = ft_echo(cmd, shell->str);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		exit_code =ft_cd(shell->str);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		exit_code = ft_pwd();
	else if (ft_strncmp(cmd, "env", 3) == 0)
		exit_code = ft_env(shell->local_envp);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		exit_code = ft_unset(shell->str, shell->local_envp);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		exit_code = ft_export(shell->str, shell->file, shell->local_envp);
	return (exit_code); //update with exit function
}
