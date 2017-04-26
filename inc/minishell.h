/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:40:04 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/26 05:45:47 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include "libft.h"

typedef struct			s_bin_files
{
	char			*name;
	struct s_bin_files	*next;
}				t_bin_files;

void display_prompt(char **envv);
int exec_command(char **command, char **envv);
#endif