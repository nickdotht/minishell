/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 04:49:25 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/26 06:19:14 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_home_path(char **envv) {
	int i;

	i = -1;
	while (envv[++i]) {
		if (ft_strstartswith(envv[i], "HOME")) {
			return envv[i] + 5;
		}
	}
	return (NULL);
}

void display_prompt(char **envv) {
	(void)envv;
	char *cwd;
	char	buff[4096 + 1];
	char *home_path;

	home_path = get_home_path(envv);
	cwd = getcwd(buff, 4096);
	if (ft_strstartswith(cwd, home_path)) {
		ft_putstr("~");
		ft_putstr(cwd + ft_strlen(home_path));
	} else {
		ft_putstr(cwd);
	}
	ft_putstr(" ︻┳デ═—$ ");
}