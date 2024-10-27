/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:03:03 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/25 20:15:01 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int find_path_index(char *desired_var, char **envp)
{
    int i;
    size_t var_len;

    var_len = strlen(desired_var);
    for (i = 0; envp[i] != NULL; i++)
    {
        printf("Checking envp[%d]: %s\n", i, envp[i]);  // Debug print each variable
        // Check if envp[i] starts with `desired_var` and is followed by `=`
        if (strncmp(envp[i], desired_var, var_len) == 0 && envp[i][var_len] == '=')
        {
            printf("Match found for %s at index %d\n", desired_var, i);  // Debug success
            return i; // Return the index if match is found
        }
    }
    printf("No match found for %s\n", desired_var);  // Debug failure
    return -1; // Return -1 if variable not found
}



void ft_unset(char *var, char **envp) 
{
    int index;
    int i;

    if (var == NULL) 
    {
        write(STDERR_FILENO, "unset: variable name required\n", 30);
        return;
    }
    index = find_path_index(var, envp);
    if (index == -1) 
    {
        write(STDERR_FILENO, "unset: no such variable\n", 24);
        return;
    }
    i = index; 
    while (envp[i] != NULL)
    {
        if (envp[i + 1] == NULL)
        {   
            printf("Unsetting %s\n", envp[i]);  // Debug print the variable being unset
            envp[i] = NULL;
            break;
        }  
        envp[i] = envp[i + 1];
        i++;
        printf("Moving %s to index %d\n", envp[i], i - 1);  // Debug print the variable being moved
    }
    envp[i - 1] = NULL;
}