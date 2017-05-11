/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 00:50:10 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/11 01:58:05 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    proc_signal_handler(int signo)
{
  if (signo == SIGINT)
	{
		ft_putstr("\n");
    signal(SIGINT, proc_signal_handler);
	}
}

void    signal_handler(int signo)
{
  if (signo == SIGINT)
	{
		ft_putstr("\n");
		display_prompt();
    signal(SIGINT, signal_handler);
	}
}
