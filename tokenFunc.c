#include "main.h"

/********************************/
/********** print_str ***********/
/*********** _strtok ************/
/********** _strpbrk ************/
/*********** _strspn ************/
/********************************/

/**
 * print_str - prints a string to the STDOUT
 * @format: formatted string containing specifiers
 * Return: number of char printed
 */
int print_str(const char *format, ...)
{
	va_list args;
	int count = 0;

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
			case 's':
			{
				const char *str = va_arg(args, const char *);

				count += print_str(str);
				break;
			}
			/* Add more cases for other specifiers as needed */
			default:
				/* Handle unsupported specifier or just ignore it */
				write(1, "%", 1);
				count++;
				break;
			}
		}
		else
		{
			write(1, format, 1);
			count++;
		}

		format++;
	}
	va_end(args);

	return (count);
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
	static char *token;
	char *result;

	/* Validate delimiter*/
	if (delim == NULL)
		return (NULL);

	/* Initialize or reset the token to the start of the string */
	if (str != NULL)
		token = str;


	/* If the token is at the end of the string, we're done*/
	if (token == NULL || *token == '\0')
		return (NULL);

	/* Skip leading delimiters */
	token += _strspn(token, delim);

	/* Check if the string is only delimiters or empty */
	if (*token == '\0')
		return (NULL);

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
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
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
		return (NULL);

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
size_t _strspn(const char *s, const char *accept)
{
	const char *ptr;
	const char *acc;
	size_t count = 0;

	/* Iterate over the characters in 's' */
	for (ptr = s; *ptr != '\0'; ++ptr)
	{
		/* Check each character against those in 'accept' */
		for (acc = accept; *acc != '\0'; ++acc)
		{
			/* If a match is found, break out of the inner loop */
			if (*ptr == *acc)
				break;
		}
		/* If no match was found in 'accept', return the current count */
		if (*acc == '\0')
			return (count);
		/* Else, increment the count for the matching character */
		++count;
	}

	/* Return the total count of matching characters */
	return (count);
}
