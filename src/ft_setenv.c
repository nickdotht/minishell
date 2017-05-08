/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:16:55 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/07 18:32:52 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_env(void)
{
	int     i;

	i = -1;
	while (g_envv[++i])
		ft_putendl(g_envv[i]);
}

int    find_env_var(char **command)
{
	int     i;

	i = -1;
	while (g_envv[++i])
	{
		if (ft_strstartswith(g_envv[i], ft_strjoinch(command[0], '=')))
			return (i);
	}
	return (i);
}

void    ft_setenv(char **command)
{
	int     i;
	int     pos;

	i = -1;
	if (!command[0])
		return (print_env());
	pos = find_env_var(command);
	if (g_envv[pos])
	{
		if (command[1])
			g_envv[pos] = ft_strjoin(command[0], ft_strjoin("=", command[1]));
		else
			g_envv[pos] = ft_strjoin(command[0], "=");        
	}
	else
	{
		g_envv = ft_realloc(g_envv, pos, pos + 1);
		if (command[1])
			g_envv[pos] = ft_strjoin(command[0], ft_strjoin("=", command[1]));
		else
			g_envv[pos] = ft_strjoin(command[0], "="); 
	}
}