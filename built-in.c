#include "main.h"

void executeLS(int argc, char *argv[])
{
	/* Create an array to store the environment variables */
	extern char **environ;
	int child_pid;
	(void)argc;

	child_pid = fork();
	if  (child_pid == 0)
	{
		/* Child process */
		execve("/bin/ls", argv, environ);
		perror("failed to execute ls command");
		_exit(EXIT_FAILURE);
	}
	else if (child_pid < 0)
		perror("fork");
	else {
		/* Parent process */
		int status;
		waitpid(child_pid, &status, 0);
	}
}

void handleEnvCommand(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
}