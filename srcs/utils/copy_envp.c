/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:56:35 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/27 20:03:47 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//why do you want to copy envp? why do we can use what we already have envp?
//maybe I need exctly the same function with one more space for the historical commands
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
