/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:56:23 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/08 17:12:34 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_var(char **var, char *key, char *value)
{
    var[0] = ft_strdup(key);
    var[1] = ft_strdup(value);
}

void    change_dir(char *path)
{
    
}

void	cd_builtin(char **command)
{
    char    **var;

    if (!command[0])
        return (change_dir("~"));
}