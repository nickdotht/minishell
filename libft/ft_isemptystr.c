/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isemptystr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 00:03:25 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/21 01:09:11 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isemptystr(char *str, int consider_space)
{
	int		i;
	int		min;
	int		max;

	i = -1;
	min = 32 + consider_space;
	max = 126;
	while (str[++i])
	{
		if (str[i] >= min && str[i] <= max)
			return (0);
	}
	return (1);
}
