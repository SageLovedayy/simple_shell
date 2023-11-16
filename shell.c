#include "main.h"


/**
 * runShell - add descr
 * @info: Pointer to the commandInfo structure.
 * @argv: Command-line arguments.
 * Return: Exit status.
 */
int runShell(commandInfo *shellInfo, char **argv)
{
	ssize_t inputResult = 0;
	int builtinReturn = 0;
	char *prompt = "$ ";

	while (inputResult != -1 && builtinReturn != -2) {
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

	/*writeHistory(shellInfo);*/
	freeCommandInfo(shellInfo, 1);

	if (!((isatty(STDIN_FILENO) && shellInfo->input_file_descriptor <= 2)) && shellInfo->commandExecStatus)
		exit(shellInfo->commandExecStatus);

	if (builtinReturn == -2)
	{
		if (shellInfo->error_number == -1) {
			exit(shellInfo->commandExecStatus);
		}
		exit(shellInfo->error_number);
	}

	return builtinReturn;
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
 * clear_info - initializes struct
 * @info: add descr
 */
void clearCommandInfo(commandInfo *shellInfo)
{
	shellInfo->current_argument = NULL;
	shellInfo->command_arguments = NULL;
	shellInfo->executable_path = NULL;
	shellInfo->argument_count = 0;
}

/**
 * set_info - initializes commandInfo struct
 * @info: struct address
 * @av: argument vector
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
		for (i = 0; shellInfo->command_arguments && shellInfo->command_arguments[i]; i++)
			;
		shellInfo->argument_count = i;

		replaceAlias(shellInfo);
		replaceVars(shellInfo);
	}
}

/*====================================================*/
/*GETLINE COMMANDS*/

/**
 * getInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
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

		check_chain(shellInfo, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(shellInfo, buf, &j))
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

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}


ssize_t inputBuf(commandInfo *shellInfo, char **buf, size_t *bufferLen)
{
	ssize_t bytesRead = 0;
	size_t lineLength = 0;

	if (!*bufferLen)
	{
		free(*buf);
		*buf = NULL;

		signal(SIGINT, sigintHandler); /*SIGINT: signal sent when ctrl + c is pressed*/

		bytesRead = _getline(shellInfo, buf, &lineLength);

		if (bytesRead > 0)
		{
			if ((*buf)[bytesRead - 1] == '\n')
			{
				(*buf)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			shellInfo->line_count_flag = 1;
			/*remove_comments_in_string(*buf);*/
			/*buildHistoryList(shellInfo, *buf, shellInfo->history_count++);*/
			*bufferLen = bytesRead;
			shellInfo->command_buffer = buf;
		}
	}

	return (bytesRead);
}

void sigintHandler(__attribute__((unused)) int sig_num)
{
	_putchar('\n');
	_putchar('$');
	_putchar(FLUSH_BUFFER);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(commandInfo *shellInfo, char **ptr, size_t *length)
{
	static char buf[BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(shellInfo, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(commandInfo *shellInfo, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(shellInfo->input_file_descriptor, buf, BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}


/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(commandInfo *shellInfo, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		shellInfo->command_buffer_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		shellInfo->command_buffer_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		shellInfo->command_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}


/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(commandInfo *shellInfo, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (shellInfo->command_buffer_type == CMD_AND)
	{
		if (shellInfo->commandExecStatus)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (shellInfo->command_buffer_type == CMD_OR)
	{
		if (!shellInfo->commandExecStatus)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/*=======================================================*/
/*HANDLE BUILT IN COMMANDS*/
int findBuiltinCmd(commandInfo *shellInfo)
{
	int i, builtinReturn = -1;

	commandStruct builtInCommand[] = {
		{"exit", NULL},
		{"env", NULL},
		{"help", NULL},
		{"history",NULL},
		{"setenv",NULL},
		{"unsetenv", NULL},
		{"cd", NULL},
		{"alias", NULL},
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
 * @info: the parameter & return info struct
 *
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

	path = findPath(shellInfo, _getenv(shellInfo, "PATH="), shellInfo->command_arguments[0]);
	if (path)
	{
		shellInfo->executable_path = path;
		fork_cmd(shellInfo);
	}
	else
	{
		if (((isatty(STDIN_FILENO) && shellInfo->input_file_descriptor <=2) || _getenv(shellInfo, "PATH=")
					|| shellInfo->command_arguments[0][0] == '/') && isCmd(shellInfo, shellInfo->command_arguments[0]))
			fork_cmd(shellInfo);
		else if (*(shellInfo->current_argument) != '\n')
		{
			shellInfo->commandExecStatus = 127;
			print_error(shellInfo, "not found\n");
		}
	}
}

/**
 * Checks if a given path corresponds to a regular file.
 * @param path The path to check.
 * @return 1 if the path is a regular file, 0 otherwise.
 */
int is_regular_file(const char *path)
{
	struct stat st;
	return path && stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

/**
 * findPath - add descr
 * @info: the shellInfo struct
 * @pathstr: add descr
 * @cmd: add descr
 *
 * Return: full path of cmd if found or NULL
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

/*===========================================================*/
/*FORK CMD*/

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(commandInfo *shellInfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(shellInfo->executable_path, shellInfo->command_arguments, get_environ(shellInfo)) == -1)
		{
			freeCommandInfo(shellInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(shellInfo->commandExecStatus));
		if (WIFEXITED(shellInfo->commandExecStatus))
		{
			shellInfo->commandExecStatus = WEXITSTATUS(shellInfo->commandExecStatus);
			if (shellInfo->commandExecStatus == 126)
				print_error(shellInfo, "Permission denied\n");
		}
	}
}

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(commandInfo *shellInfo)
{
	if (!shellInfo->environment || shellInfo->environment_changed_flag)
	{
		shellInfo->environment = list_to_strings(shellInfo->environment_variables);
		shellInfo->environment_changed_flag = 0;
	}

	return (shellInfo->environment);
}



/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(listNode *head)
{
	listNode *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->value) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = copy_string(str, node->value);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/*==================linked list func*/
/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const listNode *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
