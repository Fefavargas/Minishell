/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 02:29:28 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/30 00:45:18 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void setup_pipe(int *pipefds)
{
    if (pipe(pipefds)  == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

int close_pipe(int *pipefds)
{
    if (*pipefds <= 2)
		return (EXIT_SUCCESS);
	if (close(*pipefds) == -1)
	{
		perror("minishell: error while closing fd");
		return (EXIT_FAILURE);
	}
    *pipefds = -1;
    return (EXIT_SUCCESS);
}


int count_commands(t_mini *commands)
{
    int count = 0;
    t_mini *current = commands;  // Start from the head of the linked list

    while (current != NULL) {
        count++;  // Increment count for each node (command) in the list
        current = current->next;  // Move to the next node in the list
    }

    return count;  // Return the total count of commands in the list
}

int close_unused_fd(int *fd_pipes, int pos, int len)
{
    int	i;
	int	*ptr;
	int	fd_in;
	int	fd_out;

	if (!fd_pipes || pos < 0 || len == 0)
		return (EXIT_FAILURE);
	i = 1;
	ptr = fd_pipes;
	fd_in = -1;
	fd_out = -1;
	if (keep == FDX_RW || keep == FDX_OR)
		fd_in = pos;
	if (keep == FDX_RW || keep == FDX_OW)
		fd_out = pos + 3;
	while (++i < len)
	{
		if (i != fd_in && i != fd_out \
			&& close_fd (&ptr[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
}


int	*build_pipes(int fd_out, int fd_in, int cmd_count)
{
	int	*fd_pipes;
	int	i;
    i = 0;
    
	if (!cmd_count)
		return (0);
	fd_pipes = (int *) ft_calloc((2 * cmd_count) + 2, sizeof(int));
	if (!fd_pipes)
	{
		perror("minishell: error while piping");//check later
		return (NULL);
	}
    while (i < (2 * cmd_count) + 2)
    {
        fd_pipes[i] = -1;
        i++;
    }
	fd_pipes[0] = fd_in;
	fd_pipes[1] = -1;
	fd_pipes[(2 * cmd_count)] = -1;
	fd_pipes[(2 * cmd_count) + 1] = fd_out;
	i = 0;
	while (fd_pipes && ++i < cmd_count)
	{
		if (pipe(&fd_pipes[i * 2]) < 0)
		{
			perror("minishell: error while piping"); //udpate with error handling
			free (fd_pipes);
		}
	}
	return (fd_pipes);
}