/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:31:55 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/08 23:08:41 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  

int open_file(const char *file, int flags, mode_t mode)
{
    int fd = open(file, flags, mode);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return fd;
}
void redirect_fd(int oldfd, int newfd)
{
    if (dup2(oldfd, newfd) == -1)
    {
        perror("dup2");
        close(oldfd);
        exit(EXIT_FAILURE);
    }
    close(oldfd);
}

void setup_redirection(t_mini *node)
{
    int fd;

    if (node->redirection == REDIRECT_INPUT)
    {
        // Redirect input from file (`<`)
        fd = open_file(node->file, O_RDONLY, 0);
        redirect_fd(fd, STDIN_FILENO);
    } 
    else if (node->redirection == REDIRECT_OUTPUT)
    {
        // Redirect output to file, overwriting (`>`)
        fd = open_file(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        redirect_fd(fd, STDOUT_FILENO);
    } 
    else if (node->redirection == REDIRECT_APPEND)
    {
        // Redirect output to file, appending (`>>`)
        fd = open_file(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        redirect_fd(fd, STDOUT_FILENO);
    } 
    else if (node->redirection == REDIRECT_HEREDOC)
    {
        //implement here doc
    }
    
}
