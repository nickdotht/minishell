/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:09:38 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 22:47:25 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		higher_nums(int num)
{
	if (num >= 10000000)
	{
		if (num >= 1000000000)
			return (10);
		if (num >= 100000000)
			return (9);
		return (8);
	}
	if (num >= 1000000)
		return (7);
	return (6);
}

int		ft_intlen(int num)
{
	if (num >= 100000)
		return (higher_nums(num));
	else
	{
		if (num >= 1000)
		{
			if (num >= 10000)
				return (5);
			return (4);
		}
		else
		{
			if (num >= 100)
				return (3);
			if (num >= 10)
				return (2);
		}
		return (1);
	}
}
