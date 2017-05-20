/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchcl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 19:30:53 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/19 20:57:44 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinchcl(char *s1, char c)
{
	char	*new;

	if (!(new = ft_strjoinch(s1, c)))
		return (NULL);
	free(s1);
	s1 = NULL;
	return (new);
}
