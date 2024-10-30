/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:25:17 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/30 19:25:49 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];
	char	*result;

	result = getcwd(cwd, sizeof(cwd));
	if (result != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}