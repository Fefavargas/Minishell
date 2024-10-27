/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyrne <jbyrne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:22:22 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/27 16:53:34 by jbyrne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *cmd, char *str)
{
	int	i;
	int	new_line;
	int	check_n;

	i = 1;
	new_line = 1;
	check_n = ft_strcmp(&cmd[i], "-n");
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
}

void	ft_cd(char *path)
{
	int	len;
	int	dest;

	len = strlen(path);
	if (path == NULL || len == 0)
		path = getenv("HOME");
	dest = chdir(path);
	if (dest != 0)
		perror("cd");
}

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

void	ft_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
