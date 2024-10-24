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
	char	*input;
	t_mini shell;
	const char *prompt;

	//for now
	(void)argc;
	(void)argv;
	
	prompt = "\033[1;38;5;201mMinishell🐚 \033[0m";
	
	//for testing
	shell.cmd = "export";
	shell.str = "";
	while (1)
	{
		input = readline(prompt);
		if (input == NULL) 
		{
			printf("\n");
			break ;
		}
		if (ft_strcmp(input, "exit") == 0) 
		{
			printf("Exiting...\n");
			free(input);
			break ;
		}
		//t_mini shell = parsing(input);
		execution(shell, envp);
		shell.cmd = "unset";
		shell.str = "HOME";
		execution(shell, envp);
		free(input);
	}
	return (0);
}
