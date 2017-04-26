/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 04:17:47 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/26 06:16:43 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envv) {
	(void)ac;
	(void)av;
	char *input;
	char **command;
	int ret;

	display_prompt(envv);
	get_next_line(0, &input);
	command = ft_strsplit(input, ' ');
	ret = exec_command(command, envv);
	// while (1)
	// {
	// 	if (ret == -1)
	// 		break ;
	// }
	exit(0);
}