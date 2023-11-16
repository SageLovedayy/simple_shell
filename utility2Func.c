#include "main.h"

/*===========================================*/
/*REALLOC FUNCtions*/

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/*===========================================*/


/**
 * checkDelim - check if delimiter
 * @c: add descr
 * @delim: add descr
 * Return: 1 if true, 0 if false
 */
int checkDelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}


/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * sigintHandler - gets the next line of input from STDIN
 * @sig_num: add descr
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_putchar('\n');
	_putchar('$');
	_putchar(FLUSH_BUFFER);
}

/**
 * getLine - gets the next line of input from STDIN
 * @shellInfo: add descr
 * @ptr: add descr
 * @length: add descr
 * Return: add descr
 */
int getLine(commandInfo *shellInfo, char **ptr, size_t *length)
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

	r = readBuffer(shellInfo, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = stCr(buf + i, '\n');
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

