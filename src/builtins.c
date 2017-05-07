#include "minishell.h"

void echo_builtin(char **command)
{
	int		i;
	int		n_flag;

	i = -1;
	n_flag = 0;
	while (command[++i])
	{
		if (i == 0 && command[0][0] == '-')
		{
			if (command[0][1] == 'n')
				n_flag = 1;
		}
		else
		{
			ft_putstr(command[i]);
			if (command[i + 1])
				ft_putchar(' ');
		}
		if (!command[i + 1])
		{
			if (n_flag)
				ft_putchar('%');
			ft_putchar('\n');
		}
  	}
}

int check_builtins(char *input)
{
	char **command;

	command = ft_strsplit(input, ' ');
	if (ft_strequ(command[0], "exit")) {
		// Clean stuff here first (memory leaks)
		exit(0);
	} else if (ft_strequ(command[0], "echo")) {
		echo_builtin(command + 1);
		return (1);
	} else if (ft_strequ(command[0], "cd")) {
		// cd_builtin(command + 1);
		return (1);
	}
	return (0);
}