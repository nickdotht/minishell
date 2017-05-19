/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:56:23 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/18 22:33:19 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pth(char *path)
{
	char	*parsed_home;

	parsed_home = parse_home_path(path, 0);
	ft_putstr(parsed_home);
	free(parsed_home);
}

void    change_dir(char *path, int print_path)
{
	char	*cwd;
	char	buff[4097];

	cwd = getcwd(buff, 4096);
	if (!chdir(path))
	{
		if (print_path)
		{
			print_pth(path);
			ft_putchar('\n');
		}
		set_env_var("OLDPWD", cwd);
		set_env_var("PWD", path);
	}
	else
	{
		ft_putstr("cd: ");
		ft_putstr(strerror(errno));
		ft_putstr(": ");
		ft_putendl(path);
	}
}

int	cd_builtin(char **command)
{
	char	*tmp;
	char	buff[4097];
	char	*cwd;
	char	*home_path;
	char	*parsed_home;

	home_path = get_env_var("HOME");
	if (!command[0])
	{
		change_dir(home_path, 0);
		return (1);
	}
	if (command[2])
	{
		ft_putendl("cd: too many arguments");
		return (1);
	}
	if (command[1])
	{
		cwd = getcwd(buff, 4096);
		if (!(tmp = ft_strreplace(cwd, command[0], command[1])))
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putendl(command[0]);
			return (1);
		}
		change_dir(tmp, 1);
		free(tmp);
	}
	else
	{
		if (ft_strequ(command[0], "--"))
		{
			change_dir(home_path, 0);
			return (1);
		}
		else if (command[0][0] == '-' && !command[0][2])
		{
			change_dir(get_env_var("OLDPWD"), 1);
			return (1);
		}
		parsed_home = parse_home_path(command[0], 1);
		change_dir(parsed_home, 0);
		free(parsed_home);
	}
	return (1);
}
