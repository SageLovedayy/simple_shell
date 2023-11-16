#include "main.h"


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
		clearCommandInfo(shellInfo); /*We can also use commandinfoinit*/

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
		freeCommandInfo(shellInfo, 0);
	}
	freeCommandInfo(shellInfo, 1);

	if (!((isatty(STDIN_FILENO) && shellInfo->input_file_descriptor <= 2))
	&& shellInfo->commandExecStatus)
		exit(shellInfo->commandExecStatus);

	if (builtinReturn == -2)
	{
		if (shellInfo->error_number == -1)
			exit(shellInfo->commandExecStatus);

		exit(shellInfo->error_number);
	}
	return (builtinReturn);
}




/**
 * main - Entry point for the shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	commandInfo shellInfo[] = { COMMAND_INFO_INIT };
	int fileDescriptor = STDERR_FILENO + 3;

	if (argc == 2)
	{
		fileDescriptor = open(argv[1], O_RDONLY);
		if (fileDescriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_fprintf(STDERR_FILENO, "%s: 0: Can't open %s\n", argv[0], argv[1]);
				print_error_char(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		shellInfo->input_file_descriptor = fileDescriptor;
	}

	populateEnvironmentList(shellInfo);

	runShell(shellInfo, argv);

	/**
	*readHistory(shellInfo);

	*/

	return (EXIT_SUCCESS);
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

/**
 * setInfo - initializes commandInfo struct
 * @shellInfo: struct address
 * @argv: argument vector
 */
void setInfo(commandInfo *shellInfo, char **argv)
{
	int i = 0;

	shellInfo->file_name = argv[0];
	if (shellInfo->current_argument)
	{
		shellInfo->command_arguments = strtow(shellInfo->current_argument, " \t");
		if (!shellInfo->command_arguments)
		{
			shellInfo->command_arguments = malloc(sizeof(char *) * 2);
			if (shellInfo->command_arguments)
			{
				shellInfo->command_arguments[0] = _strdup(shellInfo->current_argument);
				shellInfo->command_arguments[1] = NULL;
			}
		}
		for (i = 0; shellInfo->command_arguments
		&& shellInfo->command_arguments[i]; i++)
			;
		shellInfo->argument_count = i;

		replaceAlias(shellInfo);
		replaceVars(shellInfo);
	}
}

/*====================================================*/
/*GETLINE COMMANDS*/

/**
 * getInput - add descr
 * @shellInfo: add descr
 *
 * Return: add descr
 */
ssize_t getInput(commandInfo *shellInfo)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(shellInfo->current_argument), *p;

	_putchar(FLUSH_BUFFER);
	r = inputBuf(shellInfo, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		chkChain(shellInfo, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (isChn(shellInfo, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			shellInfo->command_buffer_type = 0;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from getLine() */
	return (r); /* return length of buffer from getLine() */
}

