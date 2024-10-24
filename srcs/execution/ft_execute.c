/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:16:31 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/24 01:00:37 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// this file contains the function to execute a command

#include "minishell.h"


//util function 
void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

//finds the command path from env
char	*ft_findpath(char *desired_var, char **env)
{
	int		i;
	char	*var_value;

	var_value = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], desired_var, ft_strlen(desired_var)) == 0)
		{
			return (env[i] + ft_strlen(desired_var) + 1);
		}
		i++;
	}
	return (var_value);
}

//joins the path with the directory name
char	*ft_join_path(const char *directory, const char *cmd_name)
{
	char	*temp;
	char	*cmd_path;

	temp = ft_strjoin(directory, "/");
	if (!temp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd_path = ft_strjoin(temp, cmd_name);
	free(temp);
	if (!cmd_path)
	{
		free(temp);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (cmd_path);
}

//builds the full command path
char	*build_command_path(char *cmd_name, char **env)
{
	size_t	i;
	char	*cmd_path;
	char	**directories;
	char	*path_value;

	path_value = ft_findpath("PATH", env);
	if (!path_value)
		return (NULL);
	directories = ft_split(path_value, ':');
	if (!directories)
	{
		perror("Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (directories[i])
	{
		cmd_path = ft_join_path(directories[i], cmd_name);
		if (cmd_path && access(cmd_path, F_OK | X_OK) == 0)
		{
			free_array(directories);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(directories);
	return (NULL);
}


void	ft_execute(char *cmd, char *env[])
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
	{
		perror("Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	cmd_path = build_command_path(cmd_args[0], env);
	if (!cmd_path)
	{
		printf("Error: command not found: %s\n", cmd_args[0]);
		free_array(cmd_args);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd_path, cmd_args, env) == -1)
	
	{
		perror("Error: execve failed");
		free(cmd_path);
		free_array(cmd_args);
		exit(EXIT_FAILURE);
	}
}

/* for testing purposes
int main(int argc, char *argv[], char *envp[])
{
    // Ensure a command is passed as an argument
    if (argc < 2)
    {
        printf("Usage: %s <command>\n", argv[0]);
        return 1;
    }

    // Execute the passed command
    ft_execute(argv[1], envp);

    return 0;
}
*/
