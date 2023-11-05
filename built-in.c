#include "main.h"

void executeLS(int argc, char *argv[])
{
	/* Create an array to store the environment variables */
	extern char **environ;
	int child_pid;
	int i;


	/* Handle command-line options using flagChecker function */
	for (i = 1; i < argc; i++)
	{
		if (!flagChecker(argv[i]))
		{
			/* Handle invalid option */
			printf("Invalid option -- '%s'\n", argv[i]);
			_exit(EXIT_FAILURE);
		}

		else
		{
			/* Process the valid flag (dummy demonstration: just print it) */
			printf("Found flag: %s\n", argv[i]);

		/* We can modify ls_args array or perform other actions based on the flag*/
		}
	}

	child_pid = fork();
	if  (child_pid == 0)
	{
		/* Child process */
		execve("/bin/ls", argv, environ);
		perror("failed to execute ls command");
		_exit(EXIT_FAILURE);
	}
	else if (child_pid < 0)
	{
		perror("fork failed");
		return;
	}
	else
	{
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
