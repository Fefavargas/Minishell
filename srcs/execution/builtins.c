/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:22:22 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/24 23:49:41 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char *cmd, char *str)
 {
    int i;
    int new_line;
    int check_n;
        
    i = 1;
    new_line = 1;
    check_n = ft_strcmp(&cmd[i], "-n");
    if (cmd[i] && check_n == 0)
    {
        new_line = 0;
        i++; 
    }
    printf("%s", str);
    if (new_line) 
    {
        printf("\n"); // Add newline if not suppressed
    }
}


void ft_cd(char *path)
{
    int len;
    len = strlen(path);
    int dest;
    
    if (path == NULL || len == 0) 
        path = getenv("HOME");
    dest = chdir(path);
    if (dest != 0) 
        perror("cd");
}


void ft_pwd(void)
{
    char cwd[1024];
    char *result;
    
    result = getcwd(cwd, sizeof(cwd)); 
    if (result != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd");
}

