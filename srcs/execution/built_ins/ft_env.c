/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:26:17 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/28 20:00:35 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
    {
		perror("Error: envp is NULL\n"); //check later
        return (EXIT_FAILURE);
    }
	while (envp[i] != NULL)
	{
		if (printf("%s\n", envp[i]) < 0)
		{
			perror("Error: printf failed\n"); //check later
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

