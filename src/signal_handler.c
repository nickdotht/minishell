/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 00:50:10 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/20 20:38:32 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handles interruption signals on a running process
**
** @param		signo		The signal number
** @return		N/A
*/

void	proc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, proc_signal_handler);
	}
}

/*
** Handles interruption signals on the program
**
** @param		signo		The signal number
** @return		N/A
*/

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		display_prompt_msg();
		signal(SIGINT, signal_handler);
	}
}
