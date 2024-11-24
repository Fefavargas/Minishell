/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:31:55 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/24 02:13:11 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"  

static char *strip_newline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';  // Remove the newline
    }
    return str;
}


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
    result = dup2(oldfd, newfd);
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

    
    if (node->redirection == REDIRECT_HEREDOC)
    {
        fd = handle_heredoc(node->file);
        redirect_fd(fd, STDIN_FILENO);
    }
    else if (node->redirection == REDIRECT_INPUT)
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
}


int handle_heredoc(char *delimiter)
{
    char *line = NULL;
    int fd;
    ssize_t bytes_written;
    
    strip_newline(delimiter);
    fd = open_file("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while (1)
    {
        
        write(STDOUT_FILENO, "heredoc> ", 9);
        line = get_next_line(STDIN_FILENO);
        if (line == NULL)
        {
            perror("Error reading from stdin");
            close(fd);
            exit(EXIT_FAILURE);
        }
        strip_newline(line);
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        bytes_written = write(fd, line, ft_strlen(line));
        if (bytes_written == -1)
        {
            perror("Error writing to temp file");
            close(fd);
            free(line);
            exit(EXIT_FAILURE);
        }
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    fd = open_file("heredoc", O_RDONLY, 0);
    if (fd < 0)
    {
        perror("error opening heredoc file");
        exit(EXIT_FAILURE);
    }
    return fd;
}