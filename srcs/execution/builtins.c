/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:22:22 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/24 23:32:20 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char *cmd, char *str)
 {
    int i = 1;
    int new_line = 1; 

    // Check for -n option
    if (cmd[i] && ft_strcmp(&cmd[i], "-n") == 0) {
        new_line = 0;
        i++; // Skip over the -n
    }
    printf("%s", str);
    if (new_line) 
    {
        printf("\n"); // Add newline if not suppressed
    }
}


void ft_cd(char *path)
 {
    if (path == NULL || strlen(path) == 0) {
        // If no path is provided, change to home directory
        path = getenv("HOME");
    }
    if (chdir(path) != 0) {
        perror("cd");
    }
}


void ft_pwd(void)
{
    char cwd[1024];  // Buffer to hold the current working directory

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

