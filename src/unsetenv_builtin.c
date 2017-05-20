/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:35:14 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/18 22:31:55 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Removes a variable from the environment variable list
** NOTE: Always make sure to search for the variable before using this
** function, it expects that you're sure the variable already exists
** in the environment
**
** @param		var_pos		The position at which the variable was found
** @return	N/A
*/
void    remove_env_var(int var_pos)
{
	int		i;
	int		var_count;

	free(g_envv[var_pos]);
	g_envv[var_pos] = NULL;
	i = var_pos;
	var_count = var_pos + 1;
	while (g_envv[i + 1])
	{
		g_envv[i] = ft_strdup(g_envv[i + 1]);
		free(g_envv[i + 1]);
		i++;
		var_count++;
	}
	g_envv = realloc_envv(var_count - 1);
}

/*
** Executes the builtin unsetenv command
**
** @param		args		The arguments to pass to unsetenv
** @return	1 on completion
*/
int    unsetenv_builtin(char **args)
{
	int			i;
	int			var_pos;

	if (!args[0])
	{
		ft_putendl("unsetenv: Too few arguments.");
		return (1);
	}
	i = -1;
	while (args[++i])
	{
		var_pos = find_env_var(args[i]);
		if (g_envv[var_pos])
			remove_env_var(var_pos);
	}
	return (1);
}
