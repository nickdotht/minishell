/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 01:11:53 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/24 20:46:22 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_realloc(void *ptr, size_t size)
{
	char *new;

	if (!size && ptr)
	{
		if (!(new = (char*)malloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return (new);
	}
	new = (char*)malloc(size);
	if (ptr)
	{
		ft_memcpy(new, ptr, size);
		ft_memdel(&ptr);
	}
	return (new);
}
