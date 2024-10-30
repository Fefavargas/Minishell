/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:21:01 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/22 18:44:29 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_mini		shell;
	const char	*prompt;
	char		**local_envp;

	local_envp = copy_array(envp, false);
	if (!local_envp)
	{
		perror("Failed to copy envp");
		return (1);
	}
	prompt = "\033[1;38;5;201mMinishell🐚 \033[0m";

	//for now
	(void)argc;
	(void)argv;

	//for testing
	shell.cmd = "export";
	shell.str = "MYVAR";
	shell.file = "myvalue";
	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			printf("Exiting...\n");
			free(input);
			break ;
		}
		//t_mini shell = parsing(input);
		printf("one");
		execution(shell, local_envp);
		shell.cmd= "export";
		shell.str = NULL;
		shell.file = NULL;
		execution(shell, local_envp);
		free(input);
	}
	return (0);
}
