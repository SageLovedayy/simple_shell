#include "main.h"

/**
 * list of functions here:
 * print_str
 * _strlen
 * _strpbrk
 * _strtok
 * _strcmp
 */

/**
 *print_str - prints a string to the STDOUT
 *@str: string to print out
 *Return: number of char printed
 */
size_t print_str(const char *str)
{
	size_t i;

	write(1, str, _strlen(str));
	i = _strlen(str);

	return (i);
}

/**
 *_strlen - calculates the length of a string
 *@s: pointer to string
 *Return: string length
 */
size_t _strlen(const char *s)
{
	size_t i = 0;

	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

/**
 *_strpbrk - find the first occurence of any character
 * from accept string in the s string
 *@s: string to search from
 *@accept: string we are searching for
 *Return: pointer to first occurence of accept
 */
char *_strpbrk(char *s, const char *accept)
{
	int i;

	if (s == NULL || accept == NULL)
		return NULL;

	while (*s)
	{
		for (i = 0; accept[i]; i++)
		{
			if (*s == accept[i])
				return (s);
		}
	s++;
	}

	return (NULL);
}

/**
 *_strspn - extract tokens from strings
 *@s: add descr
 *@accept: add descr
 *Return: pointer to the next token or NULL if there are no more
 */
size_t _strspn(const char *s, const char *accept) {
	const char *ptr;
	const char *acc;
	size_t count = 0;

	/* Iterate over the characters in 's' */
	for (ptr = s; *ptr != '\0'; ++ptr) {
		/* Check each character against those in 'accept' */
		for (acc = accept; *acc != '\0'; ++acc) {
			/* If a match is found, break out of the inner loop */
			if (*ptr == *acc) {
				break;
			}
		}
		/* If no match was found in 'accept', return the current count */
		if (*acc == '\0') {
			return count;
		}
		/* Else, increment the count for the matching character */
		++count;
	}

	/* Return the total count of matching characters */
	return count;
}

/**
 *_strtok - extract tokens from strings
 *@str: string to tokenise
 *@delim: set of byte that delimit the token
 *Return: pointer to the next token or NULL if there are no more
 */
char *_strtok(char *str, const char *delim)
{
	/* Static variable to maintain state between calls */
	static char *token = NULL;
	char *result;

	/* Validate delimiter*/
	if (delim == NULL) {
		return NULL;
	}

	/* Initialize or reset the token to the start of the string */
	if (str != NULL)
		token = str;

	/* If the token is at the end of the string, we're done*/
	if (token == NULL || *token == '\0')
		return NULL;

	/* Skip leading delimiters */
	token += _strspn(token, delim);

	/* Check if the string is only delimiters or empty */
	if (*token == '\0') {
		return NULL;
	}

	result = token; /* Store the current token's starting address */

	/* Find the next occurrence of the delimiter */
	token = _strpbrk(token, delim);

	if (token != NULL)
	{
		*token = '\0';
		token++;
	}

	return (result);
}

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: 0 if equal, negative if s1 is less than s2
 *  positive if s1 is less than s2
 */

int _strcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}
	return (0);
}
