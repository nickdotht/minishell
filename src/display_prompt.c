/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 04:49:25 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/07 16:58:48 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_home_path(void)
{
	int i;

	i = -1;
	while (g_envv[++i]) {
		if (ft_strstartswith(g_envv[i], "HOME")) {
			return g_envv[i] + 5;
		}
	}
	return (NULL);
}

void display_prompt(void)
{
	char	*cwd;
	char	buff[4096 + 1];
	char	*home_path;

	home_path = get_home_path();
	cwd = getcwd(buff, 4096);
	if (ft_strstartswith(cwd, home_path))
	{
		ft_putstr("~");
		ft_putstr(cwd + ft_strlen(home_path));
	}
	else
		ft_putstr(cwd);
	ft_putstr(" \033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ");
	ft_putstr("\033[0m\033[34m═\033[0m\033[35m—\033[0m$ ");
}