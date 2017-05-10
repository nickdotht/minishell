/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 04:49:25 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/10 11:56:43 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_path(void)
{
	int i;

	i = -1;
	while (g_envv[++i])
	{
		if (ft_strstartswith(g_envv[i], "HOME"))
			return g_envv[i] + 5;
	}
	return (NULL);
}

char	*parse_home_path(char *path, int reverse_parse)
{
	char	*home_path;
	char	*new;
	char	*compare;

	if (!path)
		return (NULL);
	home_path = get_home_path();
	compare = reverse_parse ? ft_strdup("~") : home_path;
	if (!ft_strstartswith(path, compare))
		return (path);
	if (reverse_parse)
		new = ft_pathjoin(home_path, path + 1);
	else
		new = ft_pathjoin("~", path + ft_strlen(home_path));
	// free(compare);
	return (new);
}

void	display_prompt(void)
{
	char	*cwd;
	char	buff[4096 + 1];

	cwd = getcwd(buff, 4096);
	ft_putstr(parse_home_path(cwd, 0)); // free that new string later
	ft_putstr(" \033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ");
	ft_putstr("\033[0m\033[34m═\033[0m\033[35m—\033[0m$ ");
}