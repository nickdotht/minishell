/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 15:41:15 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/17 15:30:30 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_out(char **command, int i)
{
	int		starts_with;
	int		ends_with;
	int		str_len;
	char	*home_path;

	starts_with = IS_QUOTE(command[i][0]);
	str_len = (int)ft_strlen(command[i]);
	ends_with = IS_QUOTE(command[i][str_len - 1]);
	home_path = get_env_var("HOME");
	if (ends_with && starts_with)
		ft_putnstr(command[i] + 1, -1);
	else if (ends_with)
		ft_putnstr(command[i], -1);
	else if (starts_with)
		ft_putstr(command[i] + 1);
	else if (command[i][0] == '~')
		ft_putstr(ft_pathjoin(home_path, command[i] + 1)); // free this mem
	else
		ft_putstr(command[i]);
	if (command[i + 1])
		ft_putchar(' ');
}

void	echo_var(char **command, int i)
{
	char *value;

	if (!(value = get_env_var(command[i] + 1)))
		return ;
	ft_putstr(value);
	if (command[i + 1])
		ft_putchar(' ');
}

void	echo_builtin(char **command)
{
	int		i;
	int		n_flag;

	i = -1;
	n_flag = 0;
	if (!command[0])
		write(1, "\n", 1);
	while (command[++i])
	{
		if (i == 0 && command[i][0] == '-')
		{
			if (command[0][1] == 'n' && command[0][2] == '\0')
				n_flag = 1;
			else if (command[0][1] == '\0')
				ft_putchar(' ');
			else
				echo_out(command, i);
		}
		else if (command[i][0] == '$')
			echo_var(command, i);
		else
			echo_out(command, i);
		if (!command[i + 1] && !n_flag)
			ft_putchar('\n');
  	}
}
