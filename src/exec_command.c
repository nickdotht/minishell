/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 05:44:00 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/08 17:07:29 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path(char ***path)
{
	int i = -1;
	while (g_envv[++i])
	{
		if (ft_strstartswith(g_envv[i], "PATH"))
			*path = ft_strsplit(g_envv[i] + 5, ':');
	}
}

int		run_cmd(char *path, char **args)
{
	 pid_t	pid;

	 pid = fork();
	 if (pid == 0)
		execve(path, args, g_envv);
	 else if (pid < 0)
	 {
		 ft_putendl("Fork failed to create a new process.");
		 return (-1);
	 }
	wait(&pid);
	if (path)
		free(path);
	return (0);
}

int		check_builtins(char **command)
{
	if (ft_strequ(command[0], "exit"))
	{
		// Clean stuff here first (memory leaks)
		exit(0);
	}
	else if (ft_strequ(command[0], "echo"))
	{
		echo_builtin(command + 1);
		return (1);
	}
	else if (ft_strequ(command[0], "cd"))
	{
		cd_builtin(command + 1);
		return (1);
	}
	else if (ft_strequ(command[0], "setenv"))
	{
		setenv_builtin(command + 1);
		return (1);
	}
	else if (ft_strequ(command[0], "unsetenv"))
	{
		unsetenv_builtin(command + 1);
		return (1);
	}
	return (0);
}

void	clean_path(char **path)
{
	int		i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

int		exec_command(char **command)
{
	char		**path;
	char		*bin_path;
	struct stat	f;

	get_path(&path);
	if (check_builtins(command))
		return (0);
	int i = -1;
	while (path[++i])
	{
		if (command[0][0] == '/')
			bin_path = ft_strdup(command[0]);
		else
			bin_path = ft_pathjoin(path[i], command[0]);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else
			if ((f.st_mode & S_IFMT) == S_IFREG)
				return (run_cmd(bin_path, command));
	}
	clean_path(path);
	ft_putstr("minishell: command not found: ");
	ft_putendl(command[0]);
	return (0);
}
