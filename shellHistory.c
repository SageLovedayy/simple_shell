#include "main.h"

/**
 * fdWrite - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int fdWrite(char c, int fd)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == FLUSH_BUFFER || i >= BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 * fdWrites - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int fdWrites(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += fdWrite(*str++, fd);
	}
	return (i);
}

/**
 * exitCommand - add descr
 * @shellInfo: add descr
 * Return: add descr
 */
int exitCommand(commandInfo *shellInfo)
{
	int exitStatus = EXIT_SUCCESS;

	if (shellInfo->command_arguments[1] != NULL)
	{
		exitStatus = atoi(shellInfo->command_arguments[1]);
	}

	shellInfo->commandExecStatus = exitStatus;

	exit(exitStatus);


	return (exitStatus);
}


/**
 * envCommand - add descr
 * @shellInfo: add descr
 * Return: add descr
 */
int envCommand(commandInfo *shellInfo)
{
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		printf("%s\n", *env);
	}


	shellInfo->commandExecStatus = EXIT_SUCCESS;

	return (EXIT_SUCCESS);
}
