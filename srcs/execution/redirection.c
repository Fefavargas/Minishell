/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:31:55 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/23 22:52:05 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  

int open_file(const char *file, int flags, mode_t mode)
{
    int fd;
    fd = open(file, flags, mode);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return fd;
}
void redirect_fd(int oldfd, int newfd)
{
    int result;
    result = dup2(oldfd, newfd) 
    if (result == -1)
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
        fd = handle_heredoc(node->file);
        redirect_fd(fd, STDIN_FILENO);   
    }
    
}


int handle_heredoc(const char *delimiter)
{
    char *line = NULL;
    size_t line_len = 0;
    ssize_t bytes_read;
    int fd;
    ssize_t bytes_written;
    
    fd = open_file("execution/files/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("error opening heredoc file");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        printf("> ");
        bytes_read = get_next_line(&line, &line_len, stdin);
        if (bytes_read == -1)
        {
            break;
        }
        if (strcmp(line, delimiter) == 0)
        {
            break;
        }
        bytes_written = write(fd, line, bytes_read);
        if (bytes_written == -1)
        {
            perror("Error writing to temp file");
            close(fd);
            free(line);
            exit(EXIT_FAILURE);
        }
        free(line);
        close(fd);
        
    }
    