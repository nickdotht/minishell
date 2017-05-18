/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 04:17:47 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/17 23:36:45 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Returns the length of the parent shell environment variable
**
** @param	envv	The parent shell environment variable
** @return	The length of envv
*/
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

/*
** Makes a copy of the environment variable of the parent shell into the
** global variable g_envv
** NOTE: I'm using a global variable so I can be able to free the memory once
** the program gets killed
**
** @param	envv	The parent shell environment variable
** @return	N/A
*/
void	init_envv(char **envv)
{
	int		i;

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

/*
** Displays a prompt on the screen and parses the input character by character
** then adds it to the referenced variable (input)
** TODO: Not the most efficient way, will improve it later
**
** @param	input	The address of the variable to fill with the parsed input
** @return	N/A
*/
void	parse_input(char **input)
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
	if (!ret)
	{
		free_envv();
		write(1, "\n", 1);
		exit(0);
	}
}

/*
** Frees all the memory allocated for the global variable g_envv
**
** @param		N/A
** @return		N/A
*/
void	free_envv(void)
{
	int i;

	i = -1;
	while (g_envv[++i])
	{
		free(g_envv[i]);
	}
	free(g_envv);
}

/*
** Initializes minishell
**
** @param	ac		argument counts
** @param	av		argument variables
** @param	envv	environment variables
** @return	0
*/
int		main(int ac, char **av, char **envv) {
	char	*input;
	int		ret;
	char	**command;

	(void)ac;
	(void)av;
	init_envv(envv);
	while (1)
	{
		display_prompt_msg();
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
	free_envv();
	return (0);
}
