#include "main.h"
#include <errno.h>

static char buffer[BUF_SIZE];
static int buf_index = 0;
static int buf_size = 0;

char *appendToLine(char *line, size_t len, char c, size_t *bytes_read, size_t *n)
{
	(void)len;
	if (line == NULL || *n <= *bytes_read + 1)
	{
		size_t new_len = (*n > 0) ? *n * 2 : 128; /* Initial allocation size */
		char *new_line = (char *)realloc(line, new_len);
		if (new_line == NULL)
		{
			if (line != NULL)
				free(line);
			return (NULL);
		}
		line = new_line;
		*n = new_len;
	}
	line[(*bytes_read)++] = c;
	return (line);
}

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char c, *line = NULL;
	size_t bytes_read = 0;
	ssize_t len = 0;

	(void)stream;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	while (1)
	{
		if (buf_index >= buf_size)
		{
			/* Refill the buffer */
			buf_size = read(STDIN_FILENO, buffer, BUF_SIZE);
			if (buf_size <= 0)
			{
				if (line != NULL)
					free(line);
				return (-1); /* End of input or error */
			}
			buf_index = 0;
		}

		c = buffer[buf_index++];

		if (c == '\n' || c == '\0')
		{
			if (bytes_read == 0)
			{
				if (line != NULL)
					free(line);
				return (-1);
			}
			line = appendToLine(line, len, c, &bytes_read, n);
			if (line == NULL)
				return (-1);
			return (bytes_read);
		}
		else
		{
			line = appendToLine(line, len, c, &bytes_read, n);
			if (line == NULL)
				return (-1);
		}
	}
}
