/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:41:15 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/18 19:03:20 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		echo_out(char **args, int i)
{
	int		starts_with;
	int		ends_with;
	int		str_len;
	char	*home_path;

	starts_with = IS_QUOTE(args[i][0]);
	str_len = (int)ft_strlen(args[i]);
	ends_with = IS_QUOTE(args[i][str_len - 1]);
	home_path = get_env_var("HOME");
	if (ends_with && starts_with)
		ft_putnstr(args[i] + 1, -1);
	else if (ends_with)
		ft_putnstr(args[i], -1);
	else if (starts_with)
		ft_putstr(args[i] + 1);
	else if (args[i][0] == '~')
		ft_putstr(ft_pathjoin(home_path, args[i] + 1)); // free this mem
	else
		ft_putstr(args[i]);
	if (args[i + 1])
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

	i = -1;
	n_flag = 0;
	if (!args)
		write(1, "\n", 1);
	else if (args[0][0] == '-' && args[0][1] == 'n' && args[0][2] == '\0')
		n_flag = 1;
	else
		echo_out(args, ++i);
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
