/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:44:58 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/24 02:58:31 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_pipeline(t_mini *node)
{
    int pipefd[2];
    int prev_pipefd[2] = {-1, -1};  // Keep track of previous pipe's file descriptors
    pid_t pid;
    
    
    while (node != NULL)
    {
        if (node->next != NULL)
            setup_pipe(pipefd);

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)  // Child process
            handle_child_process(node, pipefd, prev_pipefd);
        else  // Parent process
        {
            if (prev_pipefd[0] != -1)
            {
                close(prev_pipefd[0]);  // Close previous pipe read end 
            }
            if (prev_pipefd[1] != -1)
            {
                close(prev_pipefd[1]);  // Close previous pipe write end
            }
            handle_parent_process(pipefd);  // Close the current pipe in the parent process
            prev_pipefd[0] = pipefd[0];  // Update previous pipe read end
            prev_pipefd[1] = pipefd[1];  // Update previous pipe write end
        }
        node = node->next;  // Move to the next command in the pipeline
    }
    while (wait(NULL) > 0);
}

void handle_parent_process(int *pipefd)
{
    int result;

    result = close(pipefd[0]);
    if (result == -1)
    {
        perror("close pipe read");
        exit(EXIT_FAILURE);
    }

    result = close(pipefd[1]);
    if (result == -1)
    {
        perror("close pipe write");
        exit(EXIT_FAILURE);
    }
}


void handle_child_process(t_mini *node, int *pipefd, int *prev_pipefd)
{
    int result;

    if (prev_pipefd != NULL)
    {
        result = dup2(prev_pipefd[0], STDIN_FILENO);
        if (result == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(prev_pipefd[0]);
    }

    if (pipefd != NULL)
    {
        result = dup2(pipefd[1], STDOUT_FILENO);
        if (result == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
    }

    execute_commands(*node);  // Execute the current command
    exit(EXIT_SUCCESS);  // Exit child process
}
