/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:03:03 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/27 18:48:06 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_path_index(char *desired_var, char **envp)
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
	printf("No match found for %s\n", desired_var); // Debug failure
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
