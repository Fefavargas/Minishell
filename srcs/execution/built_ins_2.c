/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:03:03 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/25 00:48:14 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void ft_unset(char *var, char **envp) 
{
    int i;
    int found;
    int result;
    int len;
    
    i = 0;
    found = 0;
    len = strlen(var);
    if (var == NULL) 
    {
        write(STDERR_FILENO, "unset: variable name required\n", 30);
        return;
    }
    while (envp[i] != NULL) 
    {
        result = strncmp(envp[i], var, strlen(var));
        if (result == 0 && envp[i][len] == '=') 
        {
            found = 1;
            break; 
        }
        i++;
    }
    if (found) 
    {

        while (envp[i] != NULL) 
        {
            envp[i] = envp[i + 1];
            i++;
        }
        envp[i - 1] = NULL; 
    } 
    else 
    {
        write(STDERR_FILENO, "unset: no such variable\n", 24);
    }
}
