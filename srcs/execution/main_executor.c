/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:05:22 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/29 20:55:21 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	executor(t_mini *shell)
{
	int			cmd_count;
	int			*fd_pipes;
	pid_t		*pid;

	cmd_count = count_commands(shell);
	pid = (pid_t *) ft_calloc(cmd_count, sizeof(pid_t));
	if (!pid)
		return (EXIT_FAILURE);
	fd_pipes = build_pipes(shell->output_fd, shell->input_fd, cmd_count);
	if (!fd_pipes)
		return (EXIT_FAILURE);
	execute_pipeline(fd_pipes, pid, shell);
	free (fd_pipes);
	free (pid);
	return (EXIT_SUCCESS);
}
