#include "main.h"

void executeLS(int argc, char *argv[])
{
	/* Create an array to store the environment variables */
	extern char **environ;
	int child_pid;
	int i;
	/*(void)argc;*/
	/*Why is argc set to void. You used it below*/


	/* Handle command-line options using flagChecker function */
	for (i = 1; i < argc; ++i)
	{
		char *flag = flagChecker(&argv[i]);
		if (flag == NULL)
		{
			/* Handle invalid option */
			print_str("Invalid option -- '%s'\n", argv[i]);
			_exit(EXIT_FAILURE);
		}

		/* Process the valid flag (dummy demonstration: just print it) */
		print_str("Found flag: %s\n", flag);

		/* We can modify ls_args array or perform other actions based on the flag*/
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
