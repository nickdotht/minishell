/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 04:17:47 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/18 23:04:33 by jrameau          ###   ########.fr       */
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

/*
** Kills the shell gracefully
**
** @param		N/A
** @return		N/A
*/
void	exit_shell(void)
{
	ft_freestrarr(g_envv);
	write(1, "\n", 1);
	exit(0);
}

/*
** Parses a string to convert variables to their value then returns the parsed
** string
**
** @param		str		The input string to parse
** @param		pos		The position from which to start in the string
*/
char	*parse_env_var(char *str, int pos)
{
	char	*value;
	char	*key;
	char	c;

	key = ft_strnew(1);
	while (str[pos] && !IS_SPACE(str[pos]))
	{
		c = str[pos];
		key = ft_strjoincl(key, &c, 0);
		pos++;
	}
	printf("HMMM%sLMAO\n", key);
	if (!(value = get_env_var(key)))
	{
		free(key);
		return (NULL);
	}
	free(key);
	return (value);
}

/*
** Parses the input by changing $VAR_NAME to the value of VAR_NAME in the
** environment variable or by nothing if it doesn't exist and by changing ~
** to the value of the user's home path then returns the parsed string
**
** @param		input		The input string
** @return		The parsed string
*/
char	*parse_input(char *input)
{
	int		i;
	char	*new;
	int		should_parse_vars;
	int		should_parse_home;
	char	c;

	i = -1;
	new = ft_strnew(1);
	should_parse_vars = (ft_strchr(input, '$') != NULL);
	should_parse_home = (ft_strchr(input, '~') != NULL);
	while (input[++i])
	{
		if (input[i] == '$' && should_parse_vars)
		{
			new = ft_strjoincl(new, parse_env_var(input, i + 1), 0);
			while (input[i + 1] && !IS_SPACE(input[i + 1]))
				i++;
		}
		else if (input[i - 1] && IS_SPACE(input[i - 1]) && input[i] == '~'
			&& should_parse_home)
			new = ft_strjoincl(new, parse_home_path(input + i, 1), 1);
		else
		{
			c = input[i];
			new = ft_strjoincl(new, &c, 0);
		}
	}
	return (new);
}

/*
** Displays a prompt on the screen and fills the input character by character
** then adds it to the referenced variable (input)
** TODO: Not the most efficient way, will improve it later
**
** @param	input	The address of the variable to fill with the parsed input
** @return	N/A
*/
static void	get_input(char **input)
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
		exit_shell();
	printf("Final string is: %s\n", *input);
	*input = parse_input(*input);
	printf("Parsed string is: %s\n", *input);
	exit(0);
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
		get_input(&input);
		if (ft_isemptystr(input, 1))
			continue ;
		command = ft_strsplitall(input);
		free(input);
		input = NULL;
		ret = exec_command(command);
		ft_freestrarr(command);
		if (ret == -1)
			break ;
	}
	ft_freestrarr(g_envv);
	return (0);
}
