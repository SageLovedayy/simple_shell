#include "main.h"

/**
 * executeLS - execute command that list directory contents
 * @argc: Argument count
 * @argv: Argument vector
 * Return: void
 */
void executeLS(int argc, char *argv[])
{
	/* Create an array to store the environment variables */
	int child_pid;
	int i;

	/* Handle command-line options using flagChecker function */
	for (i = 1; i < argc; i++)
	{
		if (!flagChecker(argv[i]))
		{
			printf("Invalid option -- '%s'\n", argv[i]);	/* Handle invalid option */
			_exit(EXIT_FAILURE);
		}
		else
		{
			/* Process the valid flag (dummy demonstration: just print it) */
			printf("Found flag: %s\n", argv[i]);
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

/**
 * executeCD - Execute command that change directory
 * @argc: Argument count
 * @argv: Argument vector
 * Return: void
 */
void executeCD(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
}

/**
 * handleEnvCommand - Executes command that run a program
 *	in a modified environment
 * @argc: Argument count
 * @argv: Argument vector
 * Return: void
 */
void handleEnvCommand(int argc, char *argv[])
{
	char **env;
	(void)argv;
	(void)argc;

	/* Iterate through the environment variables and print them */
	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}
}
