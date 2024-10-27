/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:56:35 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/25 19:59:54 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy_envp(char **envp)
{
    int i = 0;
    while (envp[i]) i++;  
    char **local_envp = malloc(sizeof(char *) * (i + 1));
    if (!local_envp) 
        return NULL;
    i = 0;
    while (envp[i]) 
    {
        local_envp[i] = strdup(envp[i]);
        i++;
    }
    local_envp[i] = NULL;
    return local_envp;
}