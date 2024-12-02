/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:24:56 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/28 19:23:41 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *path)
{
	int	len;
	int	dest;

	len = strlen(path);
	if (path == NULL || len == 0)
		path = getenv("HOME");
	dest = chdir(path);
	if (dest != 0)
	{	
		perror("cd");
		return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
