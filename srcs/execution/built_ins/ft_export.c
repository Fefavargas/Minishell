/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:28:22 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/07 17:30:04 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void set_env_var(const char *name, const char *value, char **local_envp) 
{
    int i;
	i = 0;
	char	*temp;
	char	*new_entry;	
	int env_var_count;
	env_var_count = 0;
	
	while (local_envp[env_var_count] != NULL)
		env_var_count++;
	while (i < env_var_count)
	{
        if (ft_strncmp(name, local_envp[i], ft_strlen(name)) == 0 && local_envp[i][ft_strlen(name)] == '=')
		{
			free(local_envp[i]);
			temp = ft_strjoin(name, "=");
			local_envp[i] = ft_strjoin(temp, value);
			free(temp); 
			return;
        }
        i++;
    }
	//write part if env doesnt exist
	local_envp[env_var_count] = ft_strjoin(name, "=");
	new_entry = ft_strjoin(local_envp[env_var_count], value);
	free(local_envp[env_var_count]);
	local_envp[env_var_count] = new_entry;
	local_envp[env_var_count + 1] = NULL;
	i = 0;
	while (local_envp[i] != NULL) 
	{
		printf("%s\n", local_envp[i]);
		i++;
	}
}


void ft_export(char *var, char *var_value, char** local_envp)
{
	if (var == NULL || var_value == NULL)
	{
		int i = 0;
		while (local_envp[i] != NULL) 
		{
			printf("%s\n", local_envp[i]);
			i++;
		}
		return;
	}
	set_env_var(var, var_value, local_envp);
}
	
