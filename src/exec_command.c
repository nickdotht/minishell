/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 05:44:00 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/18 01:03:58 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees all the memory allocated for the path variable
**
** @param		path	The path to free, which is an array of strings
** @return		N/A
*/
void	clear_path(char **path)
{
	int		i;

	if (!path)
		return ;
	i = -1;
	while (path[++i])
	{
		free(path[i]);
	}
	free(path);
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

/*
** Checks if the path is a regular file and is an executable, if it is,
** it executes it, if not, it prints an error on the screen then it returns
** whether it executed successfully or not
**
** @param		bin_path	The path to search for
** @param		f			The path information from stat/lstat
** @param		command		The array of strings containing each word from the
** 							input
** @return		0 if the first path is not an executable or if the command
** 				was not executed properly or 1 for the opposite
*/
int		is_executable(char *bin_path, struct stat f, char **command)
{
	if (f.st_mode & S_IFREG)
	{
		if (f.st_mode & S_IXUSR)
			return (run_cmd(bin_path, command));
		else
		{
			ft_putstr("minishell: permission denied: ");
			ft_putendl(bin_path);
		}
	}
	free(bin_path);
	return (0);
}

/*
** Uses the first word of the input to search for an existing executable on the
** system, executes it if it found it and returns whether it found it or not
**
** @param		command		The array of strings containing each word from the
** 							input
** @param		path		The value of the PATH environment variable
** @return		0 if the first word is not an executable or if the command
**				was not executed properly or 1 for the opposite
*/
int		check_bins(char **command)
{
	int				i;
	char			*bin_path;
	char			**path;
	struct stat		f;

	path = ft_strsplit(get_env_var("PATH"), ':');
	i = -1;
	while (path && path[++i])
	{
		if (ft_strstartswith(command[0], path[i]))
			bin_path = ft_strdup(command[0]);
		else
			bin_path = ft_pathjoin(path[i], command[0]);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else
		{
			clear_path(&path);
			return (is_executable(bin_path, f, command));
		}
	}
	clear_path(&path);
	return (0);
}

/*
** Executes a command and prints the result on the screen then returns whether
** there was a an exit or not
** TODO: cheche tt kote mwen use parse_home_path pou m free memory yo epi cheche
** tout kote m use run_cmd pou m retire deny argument an
**
** @param		command		The command to execute
** @return		-1 if there was an interruption (exit) or 0 if not
*/
int		exec_command(char **command)
{
	struct stat	f;
	char		*parsed_home;

	if (check_builtins(command) || check_bins(command))
		return (0);
	parsed_home = parse_home_path(command[0], 1);
	if (lstat(parsed_home, &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
		{
			change_dir(parsed_home, 0);
			free(parsed_home);
			return (0);
		}
		else if (f.st_mode & S_IXUSR)
			return (run_cmd(parsed_home, command));
	}
	free(parsed_home);
	ft_putstr("minishell: command not found: ");
	ft_putendl(command[0]);
	return (0);
}
