#include "main.h"

/**
 * _strdup - add descr
 * @str: original string
 *
 * Return: pointer to duplicated string
 */
char *_strdup(const char *str)
{
	size_t length, i = 0;
	const char *temp = str;
	char *duplicate;

	while (*temp++)
		length++;

	duplicate = malloc(sizeof(char) * (length + 1));

	if (!duplicate)
		return (NULL);

	for (i = 0; i <= length; ++i)
		duplicate[i] = str[i];

	return (duplicate);

}


/**
 * _strlen - add descr
 * @s: add descr
 * Return: length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s)
	{
		s++;
		i++;
	}

	return (i);
}
