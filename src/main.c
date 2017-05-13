/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 04:17:47 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/12 17:20:01 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		envv_len(char **envv)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (envv[++i])
		count++;
	return (count);
}

void	init_env(char **envv)
{
	int		i;

	if (!envv)
		return ;
	g_envv = (char **)ft_memalloc(sizeof(char *) * (envv_len(envv) + 1));
	i = -1;
	while (envv[++i])
	{
		if (!(g_envv[i] = ft_strdup(envv[i])))
			exit(1);
	}
}

void	free_command(char **command)
{
	int		i;

	i = -1;
	while (command[++i])
		free(command[i]);
	free(command);
	command = NULL;
}

void you_complete_me(char *path, char **str, int search_count)
{
	DIR *dir;
	struct dirent *sd;
	int		c;

	dir = opendir(path);
	c = 0;
	while ((sd = readdir(dir)))
	{
		if (ft_strstr(sd->d_name, *str) && c == search_count)
		{
			free(*str);
			*str = ft_strdup(sd->d_name);
			// write to fd wth \b
			ft_putstr_fd(*str, 0);
			c++;
		}
	}
	if (dir)
		closedir(dir);
}

int 		auto_complete(char **str, int search_count)
{
	char	**path;
	int		i;
	struct stat f;
	char *bin_path;

	get_path(&path);
	i = -1;
	while (path && path[++i])
	{
		if (ft_strstartswith(path[i], *str)) // We're not handling absolute paths
			return (0);
		bin_path = ft_pathjoin(path[i], *str);
		if (lstat(bin_path, &f) != -1) // found it, nothing to be done
			return (0);
		you_complete_me(path[i], str, search_count);
	}
	return (1);
}

/*
*
*	Make this function take multiple args so we can free any amount of memory
* if it's really control d
*/
void check_control_d(int n) {
	if (!n || n == 0x04) // if 0 or eot (ascii)
	{
		// Free env here
		write(1, "\n", 1);
		exit(0);
	}
}

int check_backspace(char n, char **input) {
	if (n == 0x7f)
	{
		if (ft_strlen(*input))
		{
			write(1, "\b", 1);
			write(1, " ", 1);
			write(1, "\b", 1);
			*input = ft_strpop(*input);
		}
		return (1);
	}
	return (0);
}

void parse_input(char **input)
{
		int		ret;
		char	buf;
		int		pos;

		*input = ft_strnew(1);
		pos = 0;
		while ((ret = read(0, &buf, 1)) && buf != '\n')
		{
			if (buf == '\t')
			{
				if (*input && !ft_strchr(*input, ' '))
				{
					if (auto_complete(input, pos++))
						continue ;
				}
			}
			if (check_backspace(buf, input))
				continue ;
			check_control_d(buf);
			*input = ft_strjoinch(*input, buf);
			write(0, &buf, 1);
		}
		if (buf == '\n')
			return ;
		check_control_d(ret);
}

int 	set_termcap(void)
{
	struct termios old;
	struct termios new;
	int		ret;
	char **command;
	char *input;

	tcgetattr(STDIN_FILENO,&old);
	new =	old;
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&new);
	parse_input(&input);
	if (ft_isemptystr(input, 1))
		return (1);
	command = ft_strsplitall(input);
	free(input);
	input = NULL;
	ret = exec_command(command);
	free_command(command);
	if (ret == -1)
		return (ret);
	tcsetattr(STDIN_FILENO,TCSANOW,&old);
	return (0);
}

int	main(int ac, char **av, char **envv) {
	(void)ac;
	(void)av;
	int ret;

	init_env(envv);
	while (1)
	{
		display_prompt();
		signal(SIGINT, signal_handler);
		if ((ret = set_termcap()) == 1)
			continue ;
		else if (ret == -1)
			break ;
	}
	exit(0);
}
