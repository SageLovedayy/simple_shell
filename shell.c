#include "main.h"

/**
 * argChecker - desc
 * @argc: argument count
 * @cmd: command
 * Return: Returns the command on success, NULL on failure
 */
char *argChecker(int argc, char *cmd)
{
	BuiltInCommand builtInCommand[] = {
	    {"ls", executeLS},
	    {"env", handleEnvCommand},
	    {"cd", executeCD},
	    {NULL, NULL},
	    /* Add more ... */
	};
	int i, status;
	char *token;
	char **args = malloc(BUF_SIZE * sizeof(char *));
	char *command;

	if (cmd == NULL || *cmd == '\0' || *cmd == ' ' || *cmd == '\t')
	{
		return (NULL);
	}

	token = _strtok(cmd, " ");

	if (_strncmp("/bin/", token, 5) == 0)
	{
		token = token + 5;
	}
	if (_strcmp(token, "exit") == 0)
	{
		if (argc > 1)
		{
			status = _atoi(args[1]);
			exit(status);
		}
		exit(0);
	}

	if (args == NULL)
	{
		perror("Memory aLlocation error");
		exit(EXIT_FAILURE);
	}

	i = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = _strtok(NULL, " "); /*Get next token*/
	}

	args[i] = NULL; /*Null-terminate the args array*/
	command = args[0];


	for (i = 0; builtInCommand[i].name != NULL; i++)
	{
		if (_strcmp(command, builtInCommand[i].name) == 0)
		{
			builtInCommand[i].func(argc, args);
			free(args);
			return (command);
		}
	}

	free(args);
	return (command);
}

bool flagChecker(const char *token)
{
	size_t i;
	const char *flags[] = {"-l", "-a", "-R", "--help"}; /* more */


	for (i = 0; i < (sizeof(flags) / sizeof(flags[0])); i++)
	{
		if (_strcmp(token, flags[i]) == 0)
		{
			return true; /*valid flag found*/
		}
	}

	printf("Missing argument for option -- '%s'\n", token);
	printf("Invalid option -- '%s'\n", token);
	return false; /*no valid flag found*/
}

/**
 * main - desc
 * @argc: argument count
 * @argv: agrgument vector
 * Return: Always 0 o success
 */
int main(int argc, char *argv[])
{
	char *input = NULL, *result;
	ssize_t bytes_read;
	size_t input_size = 0;

	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_str("#cisfun$ ");

		bytes_read = getline(&input, &input_size, stdin);
		if (bytes_read == -1)
		{

			if (feof(stdin))
			{
				/*free(input);*/
				break;
			}

			perror("Error getting line");
			exit(EXIT_SUCCESS);
		}
		/* Remove trailing newline */
		if (input[bytes_read - 1] == '\n')
			input[bytes_read - 1] = '\0';

		if (_strcmp(input, "exit") == 0)
        	{
			break;
		}

		result = argChecker(argc, input);
		if (result != NULL)
			printf("%s: 1: %s: not found\n", argv[0], result);
	}
	free(input);

	return (0);
}
