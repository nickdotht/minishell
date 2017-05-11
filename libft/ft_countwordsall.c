/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwordsall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 15:17:40 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/11 00:23:19 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countwordsall(char const *str)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (IS_SPACE(str[i]))
			i++;
		if (!IS_SPACE(str[i]) && str[i] != '\0')
			count++;
		while (!IS_SPACE(str[i]) && str[i] != '\0')
			i++;
	}
	return (count);
}
