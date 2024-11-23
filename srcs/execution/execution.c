/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:08:48 by fvargas           #+#    #+#             */
/*   Updated: 2024/11/23 23:00:44 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(const char *cmd)
{
    if (ft_strncmp(cmd, "echo", 4) == 0)
        return 1;
    if (ft_strncmp(cmd, "cd", 2) == 0)
        return 1;
    if (ft_strncmp(cmd, "pwd", 3) == 0)
        return 1;
    if (ft_strncmp(cmd, "env", 3) == 0)
        return 1; 
    if (ft_strncmp(cmd, "unset", 5) == 0)
        return 1;
    if (ft_strncmp(cmd, "export", 6) == 0) 
        return 1;  
    return 0; 
}
void	execute_commands(t_mini shell)
{
	int saved_stdout;
	int saved_stdin;
	
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	
	if (shell.redirection != 0)
	{
		setup_redirection(shell);
	}
	if (is_builtin(shell.cmd))
	{
		if (ft_strncmp(shell.cmd, "echo", 4) == 0)
		{
			ft_echo(shell.cmd, shell.str);
		}
		else if (ft_strncmp(shell.cmd, "cd", 2) == 0)
			ft_cd(shell.str);
		else if (ft_strncmp(shell.cmd, "pwd", 3) == 0)
			ft_pwd();
		else if (ft_strncmp(shell.cmd, "env", 3) == 0)
			ft_env(shell.local_envp);
		else if (ft_strncmp(shell.cmd, "unset", 5) == 0)
			ft_unset(shell.str, shell.local_envp);
		else if (ft_strncmp(shell.cmd, "export", 6) == 0)
			ft_export(shell.str, shell.file, shell.local_envp);
	}
	else
		ft_execute(shell.cmd, shell.local_envp);
}

