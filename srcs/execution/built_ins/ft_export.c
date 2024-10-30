/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:28:22 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/30 19:28:44 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void ft_export(char *var, char *var_value, char ***envp)
{
	int		i;
	int		index;
	char 	*var_plus_equal;
	char	*new_var;
	char**	new_envp;
	i = 0;

	printf("start");
	if (var == NULL || var_value == NULL)
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
	free(*envp);
	*envp = new_envp;
}