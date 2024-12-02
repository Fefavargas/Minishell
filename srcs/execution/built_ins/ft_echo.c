/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:22:22 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/11/28 19:25:12 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char *cmd, char *str)
{
	int	i;
	int	new_line;
	int	check_n;

	i = 1;
	new_line = 1;
	check_n = ft_strncmp(&cmd[i], "-n", 2);
	if (cmd[i] && check_n == 0)
	{
		new_line = 0;
		i++;
	}
	printf("%s", str);
	if (new_line)
	{
		printf("\n"); // Add newline if not suppressed
	}
	return (EXIT_SUCCESS);
}
