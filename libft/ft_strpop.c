/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 17:01:31 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/21 01:11:26 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpop(char *str)
{
	char	*new;

	new = ft_strndup(str, ft_strlen(str) - 1);
	free(str);
	return (new);
}
