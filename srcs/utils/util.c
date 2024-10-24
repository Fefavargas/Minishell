/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:59:59 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/23 16:35:41 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

//sorry i need this too...
int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int	i;

	i = 0;
	while (n > 0 && str1[i] && (str1[i] == str2[i]))
	{
		i++;
		n--;
	}
	if (n == 0)
	{
		return (0);
	}
	else
		return ((unsigned char) str1[i] - (unsigned char) str2[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*joined;
	size_t		len1;
	size_t		len2;
	size_t		i;
	size_t		j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	j = 0;
	joined = (char *)malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	while (i < len1)
	{
		*(joined + i++) = *s1++;
	}
	while (j < len2)
	{
		*(joined + i + j++) = *s2++;
	}
	*(joined + i + j) = '\0';
	return (joined);
}
