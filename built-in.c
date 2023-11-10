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
			print_str("Invalid option -- '%s'\n", argv[i]);	/* Handle invalid option */
			_exit(EXIT_FAILURE);
		}
		else
		{
			/* Process the valid flag (dummy demonstration: just print it) */
			print_str("Found flag: %s\n", argv[i]);
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

/******************** Still buggy *******************/
/**
 * executeCD - Execute the 'cd' built-in command
 * @argc: argument count
 * @argv: argument vector
 */
void executeCD(int argc, char *argv[])
{
	char current_directory[BUF_SIZE];

	if (argc > 2)
	{
		print_str("cd: too many arguments\n");
		return;
	}

	if (argc == 1 || (argc == 2 && _strcmp(argv[1], "~") == 0))
	{
		/* No argument provided or '~' given, change to the home directory */
		if (chdir(getenv("HOME")) == 0)
		{
			/* Update the PWD environment variable */
			if (getcwd(current_directory, sizeof(current_directory)) != NULL)
			{
				setenv("PWD", current_directory, 1);
			}
			else
			{
				perror("cd");
			}
		}
		else
		{
			perror("cd");
		}
	}
	else if (argc == 2)
	{
		/* Change to the specified directory */
		if (_strcmp(argv[1], "-") == 0)
		{
			/* Handle 'cd -': change to the previous directory */
			char *previous_dir = getenv("OLDPWD");
			if (previous_dir != NULL)
			{
				if (chdir(previous_dir) == 0)
				{
					/* Update PWD and OLDPWD environment variables */
					if (getcwd(current_directory, sizeof(current_directory)) != NULL)
					{
						setenv("PWD", current_directory, 1);
						setenv("OLDPWD", argv[1], 1);
					}
					else
					{
						perror("cd");
					}
				}
				else
				{
					perror("cd");
				}
			}
			else
			{
				print_str("cd: OLDPWD not set\n");
			}
		}
		else
		{
			/* Change to the specified directory */
			if (chdir(argv[1]) == 0)
			{
				/* Update the PWD and OLDPWD environment variables */
				if (getcwd(current_directory, sizeof(current_directory)) != NULL)
				{
					setenv("PWD", current_directory, 1);
					setenv("OLDPWD", argv[1], 1);
				}
				else
				{
					perror("cd");
				}
			}
			else
			{
				perror("cd");
			}
		}
	}
	else
	{
		/* Invalid usage of 'cd' command */
		print_str("cd: too many arguments\n");
	}
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
		print_str("%s\n", *env);
	}
}
