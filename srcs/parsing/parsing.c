/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:08:38 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/29 11:27:13 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_historical(char *line, t_mini *shell)
{
	static char	**array;
	int			i;

	array = copy_array(array, 1);
	while (array && array[i])
		i++;
	array[i] = ft_strdup(line);
	array[i + 1] = NULL;
	shell->hist = array;
}

bool	check_inside_simple_quotes(char *str, int pos)
{
	int	i;
	int	flag;

	i = -1;
	flag = 1;
	while (str[++i] && i < pos)
	{
		if (str[i] == 39)
			flag *= -1;
	}
	if (flag == -1)
		return (1);
	return (0);
}

int	count_dollar_sign(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && str[i] == 39)
		{
			i++;
			while (str[i] && check_inside_simple_quotes(str, i))
				i++;
		}
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] != '$')
		{
			count++;
			i++;
		}
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
			i++;
		if (!str[i])
			i++;
	}
	return (count);
}

char	**get_variable(char *str, char **envp)
{
	char	**var;
	int		i;
	int		k;

	var = (char **)ft_calloc(sizeof(char *), count_dollar_sign(str) + 1);
	if (!var)
		return (0);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] && str[i] == 39)
		{
			i++;
			while (str[i] && check_inside_simple_quotes(str, i))
				i++;
		}
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] != '$')
		{
			var[k++] = get_envp(&str[i], envp);
			i++;
		}
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
			i++;
		if (!str[i])
			i++;
	}
	var[k] = 0;
	return (var);
}

/*t_mini	parsing(char *input)
{

}
*/