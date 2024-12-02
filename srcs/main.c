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

static t_mini *create_node(const char *cmd)
{
	t_mini *node = (t_mini *)malloc(sizeof(t_mini));
    if (!node) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    node->cmd = strdup(cmd); // Copy the command string
    node->next = NULL;
    return node;
}


t_mini *initialize_list() {
    // Create the first node
    t_mini *head = create_node("cat");
    
    // Create the second node and link it to the first
    head->next = create_node("wc -l");
    
    // Create the third node and link it to the second
    head->next->next = create_node("ls -l");

    return head;
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_mini		*shell;
	const char	*prompt;
	shell = initialize_list();
	t_mini *current; 
	current = shell;

	while(current != NULL) {
		printf("%s\n", current->cmd);
		current = current->next;
	}
	current = shell;
	current->local_envp = copy_array(envp, false);
	if (!current->local_envp)
	{
		perror("Failed to copy envp");
		return (1);
	}
	prompt = "\033[1;38;5;201mMinishell🐚 \033[0m";

	//for now while parser incomplete
	(void)argc;
	(void)argv;

	//for testing
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
		executor(shell);
		free(input);
	}
	return (0);
}
