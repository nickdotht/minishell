/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 05:44:00 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/16 23:35:09 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path(char ***path)
{
	int i = -1;
	while (g_envv[++i])
	{
		if (ft_strstartswith(g_envv[i], "PATH"))
		{
			*path = ft_strsplit(g_envv[i] + 5, ':');
			return ;
		}
	}
	*path = NULL;
}

int		run_cmd(char *path, char **args, int has_mem)
{
	 pid_t	pid;

	 pid = fork();
	 signal(SIGINT, proc_signal_handler);
	if (pid == 0)
		execve(path, args, g_envv);
	 else if (pid < 0)
	 {
		 ft_putendl("Fork failed to create a new process.");
		 return (-1);
	 }
	wait(&pid);
	if (path && has_mem)
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
	else if (ft_strequ(command[0], "env"))
	{
		print_env();
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
	char		*parsed_home;

	if (check_builtins(command))
		return (0);
	get_path(&path);
	int i = -1;
	while (path && path[++i])
	{
		if (ft_strstartswith(command[0], path[i]))
			bin_path = ft_strdup(command[0]);
		else
			bin_path = ft_pathjoin(path[i], command[0]);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else
			if (f.st_mode & S_IFREG)
			{
				if (f.st_mode & S_IXUSR)
					return (run_cmd(bin_path, command, 1));
				else
				{
					ft_putstr("minishell: permission denied: ");
					ft_putendl(bin_path);
					return (0);
				}
			}
	}
	parsed_home = parse_home_path(command[0], 1);
	if (lstat(parsed_home, &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
		{
			change_dir(parsed_home, 0);
			if (!ft_strequ(parsed_home, command[0]))
				free(parsed_home);
			return (0);
		}
		else if (f.st_mode & S_IXUSR)
			return (run_cmd(parsed_home, command, 0));
	}
	if (path)
		clean_path(path);
	ft_putstr("minishell: command not found: ");
	ft_putendl(command[0]);
	return (0);
}
