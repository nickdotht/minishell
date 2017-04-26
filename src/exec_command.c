/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 05:44:00 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/26 07:18:36 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_path(char **envv, char ***path) {
	int i = -1;
	while (envv[++i]) {
		if (ft_strstartswith(envv[i], "PATH")) {
			*path = ft_strsplit(envv[i] + 5, ':');
		}
	}
}

void run_cmd(char *path, char **args, char **envv) {
	// Working on that
}

int exec_command(char **command, char **envv) {
	char **path;
	char *bin_path;

	get_path(envv, &path);
	int i = -1;
	while (path[++i]) {
		bin_path = ft_pathjoin(path[i], command[0]);
		if (lstat(bin_path, &f) == -1) {
			free(bin_path);
		} else {
			if ((f.st_mode & S_IFMT) == S_IFREG) {
				run_cmd(bin_path, command + 1, envv);
				break;
			}
		}
	}
	return (0);
}