#include "minishell.h"

void echo_builtin(char **command)
{
	int i;
	int len;

	i = -1;
	while (command[++i]) {
		len = ft_strlen(command[i]);
		if (command[i][0] == '"' && command[i][len - 1] == '"')
			ft_putnstr(command[i] + 1, len - 1);
		else if (command[i][0] == '"')
			ft_putstr(command[i] + 1);
		else if (command[i][len - 1] == '"')
			ft_putnstr(command[i], len - 1);
		else
			ft_putstr(command[i]);
		if (command[i + 1])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

int count_args(char *str)
{
	int i;
	int count;

	i = -1;
	count  = 0;
	while (str[++i]) {
		while (str[i] == ' ')
			i++;
		count++;
		if (str[i++] == '"') {
			while (str[i] != '"')
				i++;
		} else {
			while (str[i] != ' ')
				i++;
		}
	}
	return (count);
}

// char **split_args(char *input)
// {
// 	int i = -1;
// 	char **res;

// 	res = (char **)ft_memalloc(sizeof(char) * count_args(input));
// 	while (input[++i])
// 	{
// 		while 
// 	}
// }

int check_builtins(char *input)
{
	char **command;

	// command = split_args(input);
	printf("Num args: %d\n", count_args(input));
	exit(0);
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