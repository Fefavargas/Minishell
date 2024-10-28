/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:12:09 by fvargas           #+#    #+#             */
/*   Updated: 2024/07/18 15:47:44 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ldst;
	size_t	lsrc;
	size_t	k;
	size_t	j;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	k = 0;
	j = ldst;
	if (ldst < size)
	{
		while (src[k] && (ldst + k) < (size - 1))
		{
			dst[j] = src[k];
			k++;
			j++;
		}
		dst[j] = '\0';
	}
	else
		return (size + lsrc);
	return (ldst + lsrc);
}
