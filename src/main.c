/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 04:17:47 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/12 00:46:28 by jrameau          ###   ########.fr       */
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

void 		auto_complete(char **str, int search_count)
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
			break ;
		bin_path = ft_pathjoin(path[i], *str);
		if (lstat(bin_path, &f) != -1) // found it, nothing to be done
			break ;
		you_complete_me(path[i], str, search_count);
	}
}

/*
*
*	Make this function take multiple args so we can free any amount of memory
* if it's really control d
*/
void check_control_d(int ret) {
	if (!ret)
	{
		// Free env here
		write(1, "\n", 1);
		exit(0);
	}
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
					auto_complete(input, pos++);
					while ((ret = read(0, &buf, 1)) && buf != '\n' && buf == '\t')
						auto_complete(input, pos++);
					check_control_d(ret);
				}
				continue ;
			}
			if (buf == 4)
			{
				// free env here
				write(1, "\n", 1);
				exit(0);
			}
			ft_strjoin(*input, &buf);
			write(0, &buf, 1);
		}
		if (buf == '\n')
			return ;
		check_control_d(ret);
}

void 	set_termcap(char **input)
{
	struct termios old;
	struct termios new;

	tcgetattr(STDIN_FILENO,&old);
	new =	old;
	new.c_lflag &= (~ICANON & ~ECHO);
	new.c_cc[VTIME] = 0;
	new.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO,TCSANOW,&new);
	parse_input(input);
	tcsetattr(STDIN_FILENO,TCSANOW,&old);
}

int	main(int ac, char **av, char **envv) {
	(void)ac;
	(void)av;
	char	*input;
	int		ret;
	char **command;

	init_env(envv);
	while (1)
	{
		display_prompt();
		signal(SIGINT, signal_handler);
		set_termcap(&input);
		printf("HMM%sPPPP\n", input);
		if (ft_isemptystr(input, 1))
			continue ;
		command = ft_strsplitall(input);
		free(input);
		input = NULL;
		ret = exec_command(command);
		free_command(command);
		if (ret == -1)
			break ;
	}
	exit(0);
}
