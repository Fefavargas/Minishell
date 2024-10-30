/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:08:48 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/30 00:16:33 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_mini shell, char **env)
{
	(void)env;
	if (ft_strncmp(shell.cmd, "echo", 4) == 0)
	{
		ft_echo(shell.cmd, shell.str);
	}
	else if (ft_strncmp(shell.cmd, "cd", 2) == 0)
		ft_cd(shell.str);
	else if (ft_strncmp(shell.cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(shell.cmd, "env", 3) == 0)
		ft_env(env);
	else if (ft_strncmp(shell.cmd, "unset", 5) == 0)
		ft_unset(shell.str, env);
	else if (ft_strncmp(shell.cmd, "export", 6) == 0)
		ft_export(shell.str, shell.file, &env);
	/*else if ft_strncmp(shell.cmd, "exit" 4) == 0)
		ft_exit();*/
	// else
	// ft_execute(cmd, env);
	else
		printf("Command not found\n");
}
