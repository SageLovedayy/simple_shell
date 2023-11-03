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
		{'\0', NULL},
		/* Add more ... */
	};
	int i;
	char *token = _strtok(cmd, " ");
	char *args[BUF_SIZE];

	if (token != NULL)
	{
		for (i = 0; builtInCommand[i].name[0] != '\0'; i++)
		{
			if (_strcmp(token, builtInCommand[i].name) == 0)
			{
				args[0] = strdup(token);
				args[1] = NULL;
				builtInCommand[i].func(argc, args);
				free(args[0]);
				return;
			}
		}
		/* code for non built-in commands here */
		print_str("coming soon ...");
	}
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

		argChecker(argc, input);
	}

	free(input);

	return (0);
}
