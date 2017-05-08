/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:16:55 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/08 13:24:35 by jrameau          ###   ########.fr       */
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

int    find_env_var(char *var)
{
	int     i;

	i = -1;
	while (g_envv[++i])
	{
		if (ft_strstartswith(g_envv[i], ft_strjoinch(var, '=')))
			return (i);
	}
	return (i);
}

char	*get_env_var(char *var)
{
	int     i;

	i = -1;
	while (g_envv[++i])
	{
		if (ft_strstartswith(g_envv[i], ft_strjoinch(var, '=')))
			return (ft_strchr(g_envv[i], '=') + 1);
	}
	return (NULL);
}

char	**realloc_envv(int new_size)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (g_envv[++i] && i < new_size)
		new[i] = ft_strdup(g_envv[i]);
	free(g_envv);
	return (new);
}

void    setenv_builtin(char **command)
{
	int     i;
	int     pos;

	i = -1;
	if (!command[0])
		return (print_env());
	pos = find_env_var(command[0]);
	if (g_envv[pos])
	{
		if (command[1])
			g_envv[pos] = ft_strjoin(command[0], ft_strjoin("=", command[1]));
		else
			g_envv[pos] = ft_strjoin(command[0], "=");
	}
	else
	{
		g_envv = realloc_envv(pos + 1);
		if (command[1])
			g_envv[pos] = ft_strjoin(command[0], ft_strjoin("=", command[1]));
		else
			g_envv[pos] = ft_strjoin(command[0], "="); 
	}
}