#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av) {
	pid_t	father;

	(void)ac;
	father = fork();
	if (father > 0) {
		wait(&father);
		printf("I'm your father!\n");
	}
	if (father == 0) {
		sleep(60);
		execve("/bin/ls", av, NULL);
	}
}