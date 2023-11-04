#include "main.h"

/**
 * argChecker - desc
 * @cmd: command
 */
void argChecker(int argc, char *cmd)
{
	BuiltInCommand builtInCommand[] = {
	    {"ls", executeLS},
	    {"env", handleEnvCommand},
	    {NULL, NULL},
	    /* Add more ... */
	};
	int i;
	char *token = _strtok(cmd, " ");
	char **args = malloc(BUF_SIZE * sizeof(char *));
	char *command;

	if (args == NULL)
	{
		perror("Memory aLlocation error");
		exit(EXIT_FAILURE);
	}

	i = 0;

	args[i] = token;
	while (token != NULL)
	{
		token = _strtok(NULL, " ");
		if (token != NULL)
		{
			char *flag = flagChecker(&args[i]); /*Previous value = &token, in place of &args*/

			if (flag == NULL)
			{
				printf("Invalid option -- '%s'\n", token);
				free(args);
				return;
			}

			args[++i] = flag;
		}
	}

	command = args[0];

	for (i = 0; builtInCommand[i].name != NULL; i++)
	{
		if (_strcmp(command, builtInCommand[i].name) == 0)
		{
			builtInCommand[i].func(argc, args);
			free(args);
			return;
		}
	}
	/* code for non built-in commands here */
	print_str("coming soon ...");

	free(args);
}

char *flagChecker(char **args)
{
	size_t i;
	const char *flags[] = {"-l", "-a", "-R", "--help"}; /* more */
	char *token = _strtok(NULL, " ");

	if (token == NULL)
	{
		printf("Missing argument for option -- '%s'\n", args[-1]);
		return NULL;
	}

	for (i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		if (_strcmp(token, flags[i]) == 0)
		{
			return token;
		}
	}

	printf("Invalid option -- '%s'\n", token);
	return NULL;
}

/**
 * main - desc
 * @argc: argument count
 * @argv: agrgument vector
 * Return: Always 0 o success
 */
int main(int argc, char *argv[])
{
	char *input = NULL;
	ssize_t bytes_read;
	size_t input_size = 0;

	(void)argc;
	(void)argv;

	while (1)
	{
		print_str("#cisfun$ ");

		bytes_read = getline(&input, &input_size, stdin);
		if (bytes_read == -1)
		{
			perror("Error getting line");
			exit(EXIT_FAILURE);
		}
		/* Remove trailing newline */
		input[bytes_read - 1] = '\0';

		if (_strcmp(input, "exit") == 0)
        	{
			free(input); /* Free allocated memory before exiting */
			exit(EXIT_SUCCESS);
		}

		argChecker(argc, input);
	}

	free(input);

	return (0);
}
