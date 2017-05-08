/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 04:17:47 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/08 16:49:21 by jrameau          ###   ########.fr       */
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

int	main(int ac, char **av, char **envv) {
	(void)ac;
	(void)av;
	char *input;
	int ret;

	init_env(envv);
	while (1)
	{
		display_prompt();
		get_next_line(0, &input);
		if (input[0] == '\0')
			continue ;
		ret = exec_command(input);
		free(input);
		input = NULL;
		if (ret == -1)
			break ;
	}
	exit(0);
}