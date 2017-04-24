/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 00:50:46 by jrameau           #+#    #+#             */
/*   Updated: 2016/09/27 00:50:47 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	has_whitespaces(char *str, int *i, size_t *j)
{
	while (IS_SPACE(*(str + *i)))
		(*i)++;
	while (IS_SPACE(*(str + *j)))
		(*j)--;
	if (*i || *j < ft_strlen(str))
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	size_t	j;
	int		k;
	char	*new_str;
	size_t	new_size;

	if (!s)
		return (NULL);
	i = 0;
	k = 0;
	j = ft_strlen(s) - 1;
	if (!has_whitespaces((char *)s, &i, &j) || !ft_strlen(s))
		return ((char *)s);
	new_size = (i == (int)ft_strlen(s)) ? 0 : ft_strlen(s) - (size_t)i - \
				(ft_strlen(s) - j);
	new_str = ft_strnew(new_size + 1);
	if (!new_str)
		return (NULL);
	while (i <= (int)j)
		*(new_str + k++) = *(s + i++);
	return (new_str);
}
