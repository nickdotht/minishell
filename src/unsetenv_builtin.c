/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:35:14 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/17 17:26:58 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    remove_env_var(int var_pos)
{
	int		i;
	int		j;
	int		var_count;

	i = -1;
	j = 0;
	var_count = 0;
	while (g_envv[++i])
	{
		if (i == var_pos)
		{
			free(g_envv[i]);
			g_envv[i] = NULL;
			continue ;
		}
		g_envv[j++] = ft_strdup(g_envv[i]);
		if (!g_envv[i + 1])
		{
			free(g_envv[i]);
			g_envv[i] = NULL;
		}
		var_count++;
	}
	g_envv[j] = NULL;
	g_envv = realloc_envv(var_count);
}

void    unsetenv_builtin(char **command)
{
	int     i;
	int		var_pos;

	if (!command[0])
		return (ft_putendl("unsetenv: Too few arguments."));
	i = -1;
	while (command[++i])
	{
		var_pos = find_env_var(command[i]);
		if (g_envv[var_pos])
			remove_env_var(var_pos);
	}
}
