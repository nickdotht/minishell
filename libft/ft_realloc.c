/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 01:11:53 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/16 23:31:00 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size)
{
	void	*new;

	if (!ptr)
		return (NULL);
	new = ft_memalloc(new_size);
	ft_memcpy(new, ptr, prev_size < new_size ? prev_size : new_size);
	free(ptr);
	return (new);
}
