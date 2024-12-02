/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyrne <jbyrne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:44:58 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/12/02 16:00:24 by jbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(int *fd_pipes, int pos, t_mini *shell)
{
	int	original_fd[2];
	int	exit_code;

	original_fd[0] = dup(STDIN_FILENO);
	original_fd[1] = dup(STDOUT_FILENO);
	if (original_fd[0] == -1 || original_fd[1] == -1)
		return (EXIT_FAILURE);
	if (dup2(fd_pipes[pos], STDIN_FILENO) == -1 || \
		dup2(fd_pipes[pos + 3], STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	close_unused_fd(fd_pipes, pos, KEEP_BOTH, pos + 1);
	exit_code = call_builtin(shell->cmd, shell);
	close_pipe(&fd_pipes[pos]);
	close_pipe(&fd_pipes[pos + 3]);
	if (dup2(original_fd[0], STDIN_FILENO) == -1 || \
		dup2(original_fd[1], STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	shell->exit_status = exit_code;
	return (exit_code);
}



int	execute_pipeline(int *fd_pipes, pid_t *pid, t_mini *shell)
{
	int			i;
	t_mini		*current;
	current = shell;
	int result;
	if (!fd_pipes || !pid || !shell)
		return(EXIT_FAILURE);
	i = 0;
	while (current)
	{
		if (cmd_is_a_builtin(current))
		{
			result = execute_builtin(fd_pipes, i * 2, shell);
			if (result == EXIT_FAILURE)
			{
				perror("Failed to execute builtin");
				return (EXIT_FAILURE);
			}
		}
		else
		{
			execute_nonbuiltin(fd_pipes, i * 2, &pid[i], shell);
		}

		current = current->next;
		i++;
	}
	catch_child_execs(pid, i, shell, fd_pipes);
	return (EXIT_SUCCESS);
}

int	execute_nonbuiltin(int *fd_pipes, int pos, int *pid, t_mini *shell)
{
	int			i;
	t_mini	*current;

	i = 0;
	current = shell;
	while (current && i < pos/2)
	{
			current = current->next;
			i++;
	}
	if (!current)
	{
		perror("Command not found");
		return (EXIT_FAILURE);
	}
	*pid = fork();
	if (*pid < 0)
		return (EXIT_FAILURE);
	if (*pid == 0)
	{
		if (fd_pipes[pos] != -1 && dup2(fd_pipes[pos], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
		if (fd_pipes[pos + 3] != -1 && dup2(fd_pipes[pos + 3], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
		close_unused_fd(fd_pipes, pos, KEEP_BOTH, 2 * count_commands(shell));
		exit (ft_execute(shell->cmd, shell->local_envp));
	}
	close_pipe(&fd_pipes[pos]);
	return (EXIT_SUCCESS);
}

int	catch_child_execs(pid_t *pid, int num, t_mini *shell, int *fd_pipes)
{
	int	i;
	int	exit_code;

	i = -1;
	if (!pid || !num || !shell || !fd_pipes)
		return (EXIT_FAILURE);
	while (++i < num)
	{
		if (pid[i] > 0)
		{
			waitpid(pid[i], &exit_code, 0);
			if (i == num - 1 && WIFEXITED(exit_code))
				shell->exit_status = WEXITSTATUS(exit_code);
			else if (i == num - 1 && WIFSIGNALED(exit_code))
				shell->exit_status = WTERMSIG(exit_code) + 128;
			else if (i == num - 1)
				shell->exit_status = -1;
			if (fd_pipes[(i * 2)] != -1)
			{
				close(fd_pipes[(i * 2)]);
				fd_pipes[(i * 2)] = -1;
			}
			if (fd_pipes[(i * 2) + 3] != -1)
			{
    			close(fd_pipes[(i * 2) + 3]);
    			fd_pipes[(i * 2) + 3] = -1;
			}
		}
	}
	return (EXIT_SUCCESS);
}
