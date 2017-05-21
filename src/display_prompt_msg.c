/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt_msg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 04:49:25 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/21 01:04:42 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Kills the shell gracefully
**
** @param		N/A
** @return		N/A
*/

void	exit_shell(void)
{
	ft_freestrarr(g_envv);
	write(1, "\n", 1);
	exit(0);
}

/*
** Parses a path string from ~ to the home path or from the home path to ~
** depending on reverse_parse and returns the parsed string
**
** @param	path	the string to parse
** @param	reverse_parse	0 to parse from home path to ~, 1 to parse from ~
** 						to home path
** @return	NULL if path doesn't exist or the parsed string (new) or a copy of
** path if path is not a fit
*/

char	*parse_home_path(char *path, int reverse_parse)
{
	char	*home_path;
	char	*new;

	if (!path)
		return (NULL);
	home_path = get_env_var("HOME");
	if (!ft_strstartswith(path, reverse_parse ? "~" : home_path))
		return (ft_strdup(path));
	if (reverse_parse)
		new = ft_pathjoin(home_path, path + 1);
	else
	{
		if (*(path + ft_strlen(home_path)) == '\0')
			new = ft_strdup("~");
		else
			new = ft_pathjoin("~", path + ft_strlen(home_path));
	}
	return (new);
}

/*
** Displays a prompt message on the screen
**
** @param	N/A
** @return	N/A
*/

void	display_prompt_msg(void)
{
	char	*cwd;
	char	buff[4096 + 1];
	char	*parsed_cwd;

	cwd = getcwd(buff, 4096);
	parsed_cwd = parse_home_path(cwd, 0);
	ft_putstr(parsed_cwd);
	free(parsed_cwd);
	ft_putstr(" \033[31m︻\033[0m\033[32m┳\033[0m\033[33mデ");
	ft_putstr("\033[0m\033[34m═\033[0m\033[35m—\033[0m$ ");
}
