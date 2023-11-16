#include "main.h"

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vectors
 * Return: exit stat
 */
int main(int argc, char **argv)
{
	/*Create array of structures of commandInfo & inits it to COMMAND_INFO_INIT*/
	commandInfo shellInfo[] = {COMMAND_INFO_INIT};
	/*unique fd for custom stream*/
	int fileDescriptor = STDERR_FILENO + CUSTOM_FD_OFFSET;

	if (argc == 2)
	{
		fileDescriptor = open(argv[1], O_RDONLY);
		if (fileDescriptor == -1)
		{
			if (errno == EACCES)
				exit(126); /*indicating no execute permission access*/
			if (errno == ENOENT)
			{
				_fprintf(STDERR_FILENO, "%s: No such file or directory\n", argv[0]);
				fflush(stderr);
				exit(127); /*cmd not found in PATH and not a built-in*/
			}
			return (EXIT_FAILURE);
		}
		shellInfo->input_file_descriptor = fileDescriptor;
	}


	populateEnvironmentList(shellInfo);
	runShell(shellInfo, argv);

	return (EXIT_SUCCESS);
}



/**
 * runShell - add descr
 * @shellInfo: Pointer to the commandInfo structure.
 * @argv: Command-line arguments.
 * Return: Exit status.
 */
int runShell(commandInfo *shellInfo, char **argv)
{
	ssize_t inputResult = 0;
	int builtinReturn = 0;
	char *prompt = "$ ";

	while (inputResult != -1 && builtinReturn != -2)
	{
		clearCommandInfo(shellInfo); /*We can also try commandinfoinit*/

		if ((isatty(STDIN_FILENO) && shellInfo->input_file_descriptor <= 2))
			print_str("%s", prompt);

		print_error_char(FLUSH_BUFFER);
		inputResult = getInput(shellInfo);

		if (inputResult != -1)
		{
			setInfo(shellInfo, argv);
			builtinReturn = findBuiltinCmd(shellInfo);
			if (builtinReturn == -1)
				executeExternalCmd(shellInfo);
		}
		else if ((isatty(STDIN_FILENO) && shellInfo->input_file_descriptor <= 2))
			_putchar('\n');

		/*freeCommandInfo(shellInfo, 0);*/
	}

	/*writeHistory(shellInfo);*/
	/*freeCommandInfo(shellInfo, 1);*/
	if (!((isatty(STDIN_FILENO) && shellInfo->input_file_descriptor <= 2)) &&
	shellInfo->commandExecStatus)
		exit(shellInfo->commandExecStatus);

	if (builtinReturn == -2)
	{
		if (shellInfo->error_number == -1)
			exit(shellInfo->commandExecStatus);
		exit(shellInfo->error_number);
	}
	return (builtinReturn);
}


/*==================================================*/
/*SHELLINFO COMMANDS*/

/**
 * clearCommandInfo - initializes struct
 * @shellInfo: add descr
 */

void clearCommandInfo(commandInfo *shellInfo)
{
	shellInfo->current_argument = NULL;
	shellInfo->command_arguments = NULL;
	shellInfo->executable_path = NULL;
	shellInfo->argument_count = 0;
}


