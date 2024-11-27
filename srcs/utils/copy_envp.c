/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:56:35 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/27 15:42:30 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_array(char **array, bool plusone)
{
	int		i;
	char	**local_array;

	i = 0;
	while (array && array[i])
		i++;
	if (plusone)
		i++;
	local_array = malloc(sizeof(char *) * (i + 1));
	if (!local_array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		local_array[i] = strdup(array[i]);
		i++;
	}
	local_array[i] = NULL;
	return (local_array);
}

int	is_empty(char *str)
{
	while (*str)
	{
		if (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		return (0);
	}
	return (1);
}
