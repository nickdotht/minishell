/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 04:17:47 by jrameau           #+#    #+#             */
/*   Updated: 2017/04/24 05:46:36 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av) {
	(void)ac;
	(void)av;
	printf("I am %d\n", (int)getpid());
	pid_t pid = fork();
	if (pid == 0) {
		printf("Do something big in the child\n");
		sleep(5);
		printf("Child ending\n");
		exit(42);
	}
	else if (pid < 0) {
		printf("Something wrong happened\n");
	}
	printf("Do some other big stuff while child is working\n");
	wait(&pid);
	printf("Child returned %d\n", WEXITSTATUS(pid));	
	printf("Do something else after child is done\n");
	return (0);
}