/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: janaebyrne <janaebyrne@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:22:22 by janaebyrne        #+#    #+#             */
/*   Updated: 2024/10/23 18:10:13 by janaebyrne       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char *cmd, char *str)
 {
    int i = 1;
    int new_line = 1; 

    // Check for -n option
    if (cmd[i] && ft_strcmp(&cmd[i], "-n") == 0) {
        new_line = 0;
        i++; // Skip over the -n
    }
    printf("%s", str);
    if (new_line) 
    {
        printf("\n"); // Add newline if not suppressed
    }
}
