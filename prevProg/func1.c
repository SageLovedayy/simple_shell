#include "main.h"

/********************************/
/*********** _strlen ************/
/*********** _strcmp ************/
/********** _strncmp ************/
/************ _atoi *************/
/********************************/

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

/**
 * _strncmp - compares first n byte of two strings
 * @s1: first string
 * @s2: second string
 * @n: n byte to compare
 * Return: 0 if equal, negative if s1 is less than s2
 *  positive if s1 is less than s2
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		if (*s1 == '\0' || *s2 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

/**
 * _atoi - function that convert a string to an integer.
 * @s: The string to be converted.
 * Return: the converted integer.
 */
int _atoi(char *s)
{
	int i = 0, d = 0, n = 0, len = 0, f = 0, digit = 0;

	while (s[len] != '\0')
		len++;
	while (i < len && f == 0)
	{
		if (s[i] == '-')
			++d;
		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (d % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}
		i++;
	}
	if (f == 0)
		return (0);

	return (n);
}
