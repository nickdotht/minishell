/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:50:00 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/19 22:50:27 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pathjoin(char *p1, char *p2)
{
	if (!ft_strendswith(p1, "/"))
		return (ft_strjoin(ft_strjoinch(p1, '/'), p2));
	return (ft_strjoin(p1, p2));
}
