/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:08:48 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/23 18:09:47 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_mini shell, char **env)
{

   (void)env;
   
   if (ft_strcmp(shell.cmd, "echo") == 0)
    {
        ft_echo(shell.cmd, shell.str);
    }
    /*else if (cmd == cd)
        ft_cd(str);
    else if (cmd == pwd)
        ft_pwd();
    else if (cmd == export)
        ft_export(str);
    else if (cmd == unset)
        ft_unset(str);
    else if (cmd == env)
        ft_env();
    else if (cmd == exit)
        ft_exit();*/
    //else
        //ft_execute(cmd, env);
    else 
        printf("Command not found\n"); 
}

