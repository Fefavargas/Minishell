/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyrne <jbyrne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:08:48 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/27 16:53:48 by jbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_mini shell, char **env)
{
	(void)env;
	if (ft_strcmp(shell.cmd, "echo") == 0)
	{
		ft_echo(shell.cmd, shell.str);
	}
	else if (ft_strcmp(shell.cmd, "cd") == 0)
		ft_cd(shell.str);
	else if (ft_strcmp(shell.cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(shell.cmd, "export") == 0)
		ft_export(env);
	else if (ft_strcmp(shell.cmd, "unset") == 0)
		ft_unset(shell.str, env);
	/*
	else if ft_strcmp(shell.cmd, "env") == 0)
		ft_env();
	else if ft_strcmp(shell.cmd, "exit) == 0)
		ft_exit();*/
	// else
	// ft_execute(cmd, env);
	else
		printf("Command not found\n");
}
