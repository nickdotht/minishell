/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:56:23 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/09 21:51:05 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pth(char *path)
{
	char	*home_path;

	home_path = get_env_var("HOME");
	if (ft_strstartswith(path, home_path))
		ft_putstr(ft_pathjoin("~", path + ft_strlen(home_path)));
	else
		ft_putstr(path);
}

void    change_dir(char *path, int print_path)
{
	char	*cwd;
	char	buff[4097];

	if (!chdir(path))
	{
		if (print_path)
		{
			print_pth(path);
			ft_putchar('\n');
		}
		cwd = getcwd(buff, 4096);
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

void	cd_builtin(char **command)
{
	char	*tmp;
	char	buff[4097];
	char	*cwd;
	char	*home_path;

	home_path = get_env_var("HOME");
	if (!command[0])
		return (change_dir(home_path, 0));
	if (command[2])
		return (ft_putendl("cd: too many arguments"));
	if (command[1])
	{
		cwd = getcwd(buff, 4096);
		if (!(tmp = ft_strreplace(cwd, command[0], command[1])))
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putendl(command[0]);
			return ;
		}
		change_dir(tmp, 1);
		free(tmp);
	}
	else
	{
		if (ft_strstartswith(command[0], "~"))
		{
			tmp = ft_strjoin(home_path, command[0] + 1);
			change_dir(tmp, 0);
			free(tmp);
			return ;
		}
		change_dir(command[0], 0);
	}
}