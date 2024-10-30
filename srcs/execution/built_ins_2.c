/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:03:03 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/30 00:15:52 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_path_index(char *desired_var, char **envp)
{
	int		i;
	size_t	var_len;

	var_len = strlen(desired_var);
	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], desired_var, var_len) == 0
			&& envp[i][var_len] == '=')
		{
			return (i); // Return the index if match is found
		}
	}
	return (-1);
}

void	ft_unset(char *var, char **envp)
{
	int	index;
	int	i;

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
	free(envp[index]);
	i = index;
	while (envp[i] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

void ft_export(char *var, char *var_value, char ***envp)
{
	int		i;
	int		index;
	char 	*var_plus_equal;
	char	*new_var;
	char**	new_envp;
	i = 0;

	if (var == NULL)
	{
		while (envp[i] != NULL)
		{
			printf("%s\n", *envp[i]);
			i++;
		}
		return;
	}
	var_plus_equal = ft_strjoin(var, "=");
	new_var = ft_strjoin(var_plus_equal, var_value);
	free(var_plus_equal);
	printf("new_var: %s\n", new_var);
	index = find_path_index(var, *envp);
	printf("index: %d\n", index);
	if (index != -1)
	{
		free((*envp)[index]);
        (*envp)[index] = new_var; 
        return;
	}
	new_envp = copy_array(*envp, true);
	printf("%s\n", (*envp)[i]);
	if (!new_envp)
	{
		perror("Failed to copy envp");
		return;
	}
	
    i = 0;
    while ((new_envp)[i] != NULL) 
	{
        i++;
		printf("%s\n", new_envp[i]);	
    }
    new_envp[i] = new_var;
	printf("%s\n", new_envp[i]);
    new_envp[i + 1] = NULL; 
	printf("%s\n", new_envp[i+1]); // Ensure envp ends with NULL
	envp = &new_envp;
}