/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:28:22 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/29 21:08:43 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int set_env_var(const char *name, const char *value, char **local_envp) 
{
    int i;
	i = 0;
	char	*temp;
	char	*new_entry;	
	int env_var_count;
	env_var_count = 0;

	if (name == NULL || value == NULL || local_envp == NULL)
		return (EXIT_FAILURE);
	
	while (local_envp[env_var_count] != NULL)
		env_var_count++;
	while (i < env_var_count)
	{
        if (ft_strncmp(name, local_envp[i], ft_strlen(name)) == 0 && local_envp[i][ft_strlen(name)] == '=')
		{
			free(local_envp[i]);
			temp = ft_strjoin(name, "=");
			if (temp == NULL)
				return (EXIT_FAILURE);
			local_envp[i] = ft_strjoin(temp, value);
			if (local_envp[i] == NULL)
				return (EXIT_FAILURE);
			free(temp); 
			return (EXIT_SUCCESS);
        }
        i++;
    }
	local_envp[env_var_count] = ft_strjoin(name, "=");
	if (local_envp[env_var_count] == NULL)
		return (EXIT_FAILURE);
	new_entry = ft_strjoin(local_envp[env_var_count], value);
	if (new_entry == NULL)
		return (EXIT_FAILURE);
	free(local_envp[env_var_count]);
	local_envp[env_var_count] = new_entry;
	local_envp[env_var_count + 1] = NULL;
	i = 0;
	return (EXIT_SUCCESS);
}


int ft_export(char *var, char *var_value, char** local_envp)
{
	if (local_envp == NULL)
	{
		perror("Error: local_envp is NULL\n");
		return (EXIT_FAILURE);
	}
	if (var == NULL || var_value == NULL)
	{
		int i = 0;
		while (local_envp[i] != NULL) 
		{
			printf("%s\n", local_envp[i]);
			i++;
		}
		return (EXIT_SUCCESS);
	}
	return (set_env_var(var, var_value, local_envp));
}
	
