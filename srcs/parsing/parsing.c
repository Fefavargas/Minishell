/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefa <fefa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:08:38 by fvargas           #+#    #+#             */
/*   Updated: 2024/10/27 15:08:25 by fefa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_quotation(char *str)
{
    int     i;
    char    c;

    i = -1;
    while (str[++i])
    {
        if (str[i] == 34 || str[i] == 39)
        {
            c = str[i];
            while (str[i])
            {
                
            }
        }
            while (str[++i] && str[i] != '"')
        if (str[i] == 39)
            while (str[++i] && str[i] != 39)
        if (!str[i])
        {
            //message?
            return (-1);
        }        
    }
}

t_mini	parsing(char *input)
{

}
