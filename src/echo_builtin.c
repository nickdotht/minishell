/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:41:15 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/20 20:29:53 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints out a string on the screen
**
** @param		str		The string to print
** @param		pos		The position at which to start printing
** @return		N/A
*/

static void		echo_out(char **str, int pos)
{
	int		starts_with;
	int		ends_with;
	int		str_len;

	starts_with = IS_QUOTE(str[pos][0]);
	str_len = (int)ft_strlen(str[pos]);
	ends_with = IS_QUOTE(str[pos][str_len - 1]);
	if (ends_with && starts_with)
		ft_putnstr(str[pos] + 1, -1);
	else if (ends_with)
		ft_putnstr(str[pos], -1);
	else if (starts_with)
		ft_putstr(str[pos] + 1);
	else
		ft_putstr(str[pos]);
	if (str[pos + 1])
		ft_putchar(' ');
}

/*
** Executes the builtin echo command
**
** @param		args		The arguments to pass to echo
** @return		1 on completion
*/

int				echo_builtin(char **args)
{
	int		i;
	int		n_flag;

	n_flag = 0;
	if (!args[0])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (args[0][0] == '-' && args[0][1] == 'n' && args[0][2] == '\0')
		n_flag = 1;
	i = -1;
	if (n_flag)
		++i;
	while (args[++i])
	{
		echo_out(args, i);
		if (!args[i + 1] && !n_flag)
			ft_putchar('\n');
	}
	return (1);
}
