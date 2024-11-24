/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:44:58 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/24 18:34:51 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_pipeline(t_mini *node)
{
    int pipefd[2];
    int prev_pipefd[2] = {-1, -1};  //initalise prev as invalid pipe
    pid_t pid;
    
    while (node != NULL)
    {
        if (node->next != NULL)
            setup_pipe(pipefd);
        else
        {
            pipefd[0] = -1;
            pipefd[1] = -1; 
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
            handle_child_process(node, pipefd, prev_pipefd);         
        else
            handle_parent_process(pipefd, prev_pipefd);
        node = node->next;  // Move to the next command in the pipeline
    }
    wait_for_children();
}

void handle_parent_process(int *pipefd, int *prev_pipefd)
{
    if (prev_pipefd[0] != -1)
        close(prev_pipefd[0]);
    if (prev_pipefd[1] != -1)
        close(prev_pipefd[1]);

    // Update previous pipe descriptors for the next iteration
    if (pipefd[0] != -1 && pipefd[1] != -1)
    {
        prev_pipefd[0] = pipefd[0];
        prev_pipefd[1] = pipefd[1];
    }
    else
    {
        prev_pipefd[0] = -1;
        prev_pipefd[1] = -1;
    }
}



void handle_child_process(t_mini *node, int *pipefd, int *prev_pipefd)
{
    int result;

    if (prev_pipefd[0] != -1)
    {
        close(prev_pipefd[1]); //unusued write end of prev pipe
        result = dup2(prev_pipefd[0], STDIN_FILENO);
        if (result == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(prev_pipefd[0]);
    }

    if (pipefd[1] != -1)
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


void wait_for_children()
{
    pid_t pid;

    while ((pid = wait(NULL)) > 0)
    {
        // Waiting for all child processes
    }

    if (pid == -1 && errno != ECHILD)
    {
        perror("wait");
        exit(EXIT_FAILURE);
    }
}