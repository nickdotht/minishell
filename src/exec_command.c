/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 05:44:00 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/26 20:00:16 by jrameau          ###   ########.fr       */
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

int run_cmd(char *path, char **args, char **envv) {
	 pid_t pid;

	 pid = fork();
	 if (pid == 0) {
		execve(path, args, envv);
	 } else if (pid < 0) {
		 ft_putendl("Fork failed to create a new process.");
		 return (-1);
	 }
	wait(&pid);
	if (path)
		free(path);
	return (0);
}

int exec_command(char **command, char **envv) {
	char **path;
	char *bin_path;
	struct stat f;

	get_path(envv, &path);
	int i = -1;
	while (path[++i]) {
		bin_path = ft_pathjoin(path[i], command[0]);
		if (lstat(bin_path, &f) == -1) {
			free(bin_path);
		} else {
			if ((f.st_mode & S_IFMT) == S_IFREG) {
				return (run_cmd(bin_path, command, envv));
			}
		}
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(command[0]);
	return (0);
}