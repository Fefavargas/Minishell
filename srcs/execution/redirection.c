/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:31:55 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/16 23:37:54 by janaebyrne       ###   ########.fr       */
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
        fd = handle_heredoc(node->file);
        redirect_fd(fd, STDIN_FILENO);   
    }
    
}


int handle_heredoc(const char *delimiter)
{
    int pipe_fd[2];
    char *line = NULL;
    size_t line_len = 0;
    ssize_t bytes_read;
    char buffer[1024];
    char *newline_pos;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }           

    while(1)
    {
        write(STDOUT_FILENO, ">", 1);
        free(line);
        line = NULL;
        line_len = 0;

        bytes_read = get_next_line(0);
        while(bytes_read > 0)
        {
            buffer[bytes_read] = '\0';
            newline_pos = ft_strchr(buffer, '\n');
            if (newline_pos != NULL)
            {
                *newline_pos = '\0';
                line = realloc(line, line_len + (newline_pos - buffer) + 1);
                if (!line)
                {
                    write(STDERR_FILENO, "Error: failed to allocate memory\n", 33);
                    exit(EXIT_FAILURE);
                }
                memcpy(line + line_len, buffer, newline_pos - buffer);
                line_len += newline_pos - buffer;
                line[line_len] = '\0';
                break;
            }
            else
            {
                line = realloc(line, line_len + bytes_read);
                if (!line)
                {
                    write(STDERR_FILENO, "Error: failed to allocate memory\n", 33);
                    exit(EXIT_FAILURE);
                }
                memcpy(line + line_len, buffer, bytes_read);
                line_len += bytes_read;
            } 
        }
        if (bytes_read == -1)
        {
            write(STDERR_FILENO, "Error: failed to read input\n", 29);
            free(line);
            exit(EXIT_FAILURE);
        }
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, line_len);
        write(pipe_fd[1], "\n", 1);           
}
    close(pipe_fd[1]);
    return pipe_fd[0];
}
