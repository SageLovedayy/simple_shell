#include "main.h"

#define MAX_PATH_LENGTH 1024

/**
 * cdCommand - add descr
 * @shellInfo: add descr
 * Return: add descr
 */
int cdCommand(commandInfo *shellInfo)
{
	char *targetDirectory;
	char currentDirectory[MAX_PATH_LENGTH];

	if (shellInfo->command_arguments[1] == NULL
	|| _strcmp(shellInfo->command_arguments[1], "~") == 0)
	{
		targetDirectory = getenv("HOME");
	}
	else if (_strcmp(shellInfo->command_arguments[1], "-") == 0)
	{

		targetDirectory = getenv("OLDPWD");
	}
	else
	{
		targetDirectory = shellInfo->command_arguments[1];
	}


	getcwd(currentDirectory, sizeof(currentDirectory));


	if (chdir(targetDirectory) != 0)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}

	if (setenv("PWD", getcwd(NULL, 0), 1) != 0)
	{
		perror("setenv");
		return (EXIT_FAILURE);
	}

	printf("%s\n", getcwd(NULL, 0));

	return (EXIT_SUCCESS);
}
