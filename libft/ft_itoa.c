/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:56:29 by fvargas           #+#    #+#             */
/*   Updated: 2024/07/18 18:11:49 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_dig(int nbr)
{
	size_t	count;

	count = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		count++;
		nbr *= -1;
	}
	while (nbr != 0)
	{
		count++;
		nbr = nbr / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	count;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = count_dig(n);
	s = malloc((count + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[count] = '\0';
	count --;
	if (n < 0)
	{
		s[0] = '-';
		n *= -1;
	}
	else if (n == 0)
		s[0] = '0';
	while (n > 0)
	{
		s[count] = n % 10 + '0';
		n /= 10;
		count --;
	}
	return (s);
}
