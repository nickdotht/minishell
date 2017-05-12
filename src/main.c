/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 04:17:47 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/11 17:11:42 by jrameau          ###   ########.fr       */
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

void parse_input(char **input)
{
		int		ret;
		char	buf;
		int		i;
		int		count;

		*input = ft_strnew(1);
		count = 1;
		i = 0;
		while ((ret = read(0, &buf, 1)) && buf != '\n')
		{
			*(*input + i++) = buf;
			*input = ft_realloc(*input, count, count + 1);
			count++;
		}
		*(*input + i) = '\0';
		if (!ret) // ctrl D
		{
			// Free env here
			write(1, "\n", 1);
			exit(0);
		}
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
		parse_input(&input);
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
