/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:59:59 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/27 22:06:56 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//libft is authorized! \0/

bool	check_quotation(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			c = str[i];
			while (str[++i])
			{
				if (str[i] == c)
					break ;
			}
		}
		if (!str[i])
		{
			//error message?
			return (0);
		}
	}
	return (1);
}

int	check_dollar_sign(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (i);
	}
	return (-1);
}

char	*get_envp(char *str, char **envp)
{
	int		j;
	char	*path;

	j = 0;
	while (str[j] && str[j] != ' ')
		j++;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], str, j))
		i++;
	if (envp[i])
		return (envp[i] + j + 1);
	return (0);
}
