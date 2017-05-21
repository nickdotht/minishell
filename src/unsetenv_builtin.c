/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 15:35:14 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/21 01:33:22 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints the environment variable on the screen
**
** @param		N/A
** @returns	N/A
*/

void			print_env(void)
{
	int		i;

	i = -1;
	while (g_envv[++i])
		ft_putendl(g_envv[i]);
}

/*
** Returns the length of the parent shell environment variable
**
** @param	envv	The parent shell environment variable
** @return	The length of envv
*/

static int		envv_len(char **envv)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (envv[++i])
		count++;
	return (count);
}

/*
** Makes a copy of the environment variable of the parent shell into the
** global variable g_envv
** NOTE: I'm using a global variable so I can be able to free the memory once
** the program gets killed
**
** @param	ac		argument counts
** @param	av		argument variables
** @param	envv	The parent shell environment variable
** @return	N/A
*/

void			init_envv(int ac, char **av, char **envv)
{
	int		i;

	(void)ac;
	(void)av;
	g_envv = (char **)ft_memalloc(sizeof(char *) * (envv_len(envv) + 1));
	i = -1;
	while (envv[++i])
	{
		if (!(g_envv[i] = ft_strdup(envv[i])))
			exit_shell();
	}
}

/*
** Removes a variable from the environment variable list
** NOTE: Always make sure to search for the variable before using this
** function, it expects that you're sure the variable already exists
** in the environment
**
** @param		var_pos		The position at which the variable was found
** @return	N/A
*/

static void		remove_env_var(int var_pos)
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

int				unsetenv_builtin(char **args)
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
