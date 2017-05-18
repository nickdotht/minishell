/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 01:11:53 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/17 23:30:08 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size)
{
	void	*new;

	if (!ptr || !(new = ft_memalloc(new_size)))
		return (NULL);
	ft_memcpy(new, ptr, prev_size < new_size ? prev_size : new_size);
	free(ptr);
	return (new);
}
