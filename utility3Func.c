#include "main.h"

/**
 * inputBuf - add descr
 * @shellInfo: add descr
 * @buf: add descr
 * @bufferLen: add descr
 * Return: add descr
 */
ssize_t inputBuf(commandInfo *shellInfo, char **buf, size_t *bufferLen)
{
	ssize_t bytesRead = 0;
	size_t lineLength = 0;

	if (!*bufferLen)
	{
		free(*buf);
		*buf = NULL;

		signal(SIGINT, sigintHandler); /*SIGINT:signal sent as ctrl-c is pressed*/

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



/**
 * read_buf - reads a buffer
 * @shellInfo: add descr
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
 * @new_size: add descr
 *
 * Return: add descr.
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
 * @shellInfo: the parameter struct
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
 * @shellInfo: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(commandInfo *shellInfo
, char *buf, size_t *p, size_t i, size_t len)
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

