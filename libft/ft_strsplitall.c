/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 13:18:35 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/11 00:24:28 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_word_len(char const *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (IS_SPACE(str[i]))
		i++;
	while (!IS_SPACE(str[i]) && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char			**ft_strsplitall(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	**str2;

	if (!s || !(str2 = (char **)malloc(sizeof(*str2) *
		(ft_countwordsall(s) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_countwordsall(s))
	{
		k = 0;
		if (!(str2[i] = ft_strnew(get_word_len(&s[j]) + 1)))
			str2[i] = NULL;
		while (IS_SPACE(s[j]))
			j++;
		while (!IS_SPACE(s[j]) && s[j])
			str2[i][k++] = s[j++];
		str2[i][k] = '\0';
	}
	str2[i] = 0;
	return (str2);
}
