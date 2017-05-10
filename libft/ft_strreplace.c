/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 20:14:03 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/09 21:41:41 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *str, char *term, char *replace_by)
{
	int		i;
	char	*new_path;
	int		done;
    char    *tmp;

	if (!ft_strstr(str, term))
		return (NULL);
	new_path = ft_strnew(1);
	i = -1;
	done = 0;
	while (str[++i])
	{
		if (ft_strstartswith(str + i, term) && !done)
		{
            tmp = ft_strjoin(new_path, replace_by);
            free(new_path);
			new_path = ft_strdup(tmp);
            free(tmp);
            tmp = NULL;
			i += ft_strlen(term);
			if (str[i])
            {
                tmp = ft_strjoinch(new_path, str[i]);
                free(new_path);                
				new_path = ft_strdup(tmp);
                free(tmp);
                tmp = NULL;
            }
            else
                break ;
			done = 1;
		}
		else
        {
            tmp = ft_strjoinch(new_path, str[i]);
            free(new_path);
			new_path = ft_strdup(tmp);
            free(tmp);
            tmp = NULL;
        }
	}
	return (new_path);
}