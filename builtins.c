#include "main.h"

/*=======================================================*/
/*HANDLE BUILT IN COMMANDS*/

/**
 * findBuiltinCmd - add descr
 * @shellInfo: add descr
 * Return: void
 */
int findBuiltinCmd(commandInfo *shellInfo)
{
	int i, builtinReturn = -1;

	commandStruct builtInCommand[] = {
		{"history", NULL},
		{"setenv", NULL},
		{"exit", _exit},
		{"env", NULL},
		{"cd", NULL},
		{"alias", NULL},
		{"help", NULL},
		{"unsetenv", NULL},
		{NULL, NULL}
		 /* Fix, and add more ... */
	};

	for (i = 0; builtInCommand[i].name; i++)
		if (_strcmp(shellInfo->command_arguments[0], builtInCommand[i].name) == 0)
		{
			shellInfo->current_line_number++;
			builtinReturn = builtInCommand[i].CommandFunction(shellInfo);
			break;
		}
	return (builtinReturn);
}


/**
 * executeExternalCmd - finds external exec command in PATH
 * @shellInfo: add descr
 * Return: void
 */
void executeExternalCmd(commandInfo *shellInfo)
{
	char *path = NULL;
	int i, k;

	shellInfo->executable_path = shellInfo->command_arguments[0];
	if (shellInfo->line_count_flag == 1)
	{
		shellInfo->current_line_number++;
		shellInfo->line_count_flag = 0;
	}
	for (i = 0, k = 0; shellInfo->current_argument[i]; i++)
		if (!is_delim(shellInfo->current_argument[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findPath(shellInfo, _getenv(shellInfo, "PATH=")
	, shellInfo->command_arguments[0]);
	if (path)
	{
		shellInfo->executable_path = path;
		fork_cmd(shellInfo);
	}
	else
	{
		if (((isatty(STDIN_FILENO) && shellInfo->input_file_descriptor <= 2)
		|| _getenv(shellInfo, "PATH=") || shellInfo->command_arguments[0][0] == '/')
		&& isCmd(shellInfo, shellInfo->command_arguments[0]))
			fork_cmd(shellInfo);
		else if (*(shellInfo->current_argument) != '\n')
		{
			shellInfo->commandExecStatus = 127;
			print_error(shellInfo, "not found\n");
		}
	}
}

/**
 * is_regular_file - Checks if a given path corresponds to a regular file.
 * @path: add descr
 * Return: 1 if the path is a regular file, 0 otherwise.
 */
int is_regular_file(const char *path)
{
	struct stat st;

	return (path && stat(path, &st) == 0 && S_ISREG(st.st_mode));
}

/**
 * isCmd - add descr
 * @shellInfo: the shellInfo struct
 * @path: add descr
 * Return: add descr
 */
int isCmd(commandInfo *shellInfo, char *path)
{
	struct stat st;

	(void)shellInfo;

	if (!path || stat(path, &st))
		return (0);

	if (S_ISREG(st.st_mode))
	{
		return (1);
	}

	return (0);
}

/**
 * findPath - add descr
 * @shellInfo: the shellInfo struct
 * @pathstr: add descr
 * @cmd: add descr
 *
 * Return: full path of cmd if found or NULL
 */
char *findPath(commandInfo *shellInfo, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && string_starts_with(cmd, "./"))
	{
		if (isCmd(shellInfo, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dupChars(pathstr, curr_pos, i);
			if (!*path)
				string_concatenate(path, cmd);
			else
			{
				string_concatenate(path, "/");
				string_concatenate(path, cmd);
			}
			if (is_regular_file(path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
