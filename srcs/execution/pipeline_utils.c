/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 02:29:28 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/24 02:56:11 by janaebyrne       ###   ########.fr       */
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

void close_pipe(int *pipefds)
{
    if (close(pipefds[0]) == -1 || close(pipefds[1]) == -1)
    {
        perror("close pipe");
        exit(EXIT_FAILURE);
    }
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
