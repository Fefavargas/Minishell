/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:56:35 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/29 23:59:39 by janaebyrne       ###   ########.fr       */
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
