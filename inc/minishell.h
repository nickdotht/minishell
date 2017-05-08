/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:40:04 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/08 16:26:03 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include "libft.h"

# define IS_QUOTE(x) (x == '"' || x == '\'')

char **g_envv;

typedef struct			s_bin_files
{
	char				*name;
	struct s_bin_files	*next;
}						t_bin_files;

void					display_prompt(void);
int						exec_command(char *input);
void					echo_builtin(char **command);
void					cd_builtin(char **command);
void					setenv_builtin(char **command);
char					*get_env_var(char *var);
void				    unsetenv_builtin(char **command);
int						envv_len(char **envv);
int						find_env_var(char *var);
char					**realloc_envv(int new_size);
#endif