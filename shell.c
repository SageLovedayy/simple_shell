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
	char *token = _strtok(cmd, " "), *args[BUF_SIZE];

	args[0] = token;
	while (token != NULL)
	{
		token = _strtok(NULL, " ");
		if (token != NULL)
		{
			char *flag = flagChecker(&token);

			if (flag == NULL)
			{
				printf("Invalid option -- '%s'\n", token);
				return;
			}
			args[i] = flag;
			i++;
		}
	}
	for (i = 0; builtInCommand[i].name[0] != '\0'; i++)
	{
		if (_strcmp(token, builtInCommand[i].name) == 0)
		{
			builtInCommand[i].func(argc, args);
			return;
		}
	}
	/* code for non built-in commands here */
	print_str("coming soon ...");
}

char *flagChecker(char **args)
{
	int i, j, k;
	char *flags[BUF_SIZE] = {"-l", "-a", "-R", "--help"}; /* more */
	for (i = 0; args[i] != NULL; i++)
	{
		k = sizeof(flags) / sizeof(flags[0]);
		for (j = 0; j < k; j++)
		{
			if (_strcmp(args[i], flags[j]) == 0)
				*args = _strtok(NULL, " "); /* doesn't even check if _strcmp return a positive or negative num yet */
		}
	}
	return (*args);
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
