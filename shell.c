#include "main.h"
#include <stdbool.h>

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
	char *token;
	char **args = malloc(BUF_SIZE * sizeof(char *));
	char *command;

	if (cmd == NULL || *cmd == '\0' || *cmd == ' ')
	{
		return;
	}


	token = _strtok(cmd, " ");

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
			return;
		}
	}
	/* code for non built-in commands here */
	print_str("coming soon ...");

	free(args);
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

			if (feof(stdin))
			{
				/*free(input);*/
				print_str("\n");
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

		argChecker(argc, input);
	}

	free(input);

	return (0);
}
