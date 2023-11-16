#include "main.h"

/**
 * replaceAlias - add descr
 * @shellInfo: add descr
 * Return: add descr
 */
int replaceAlias(commandInfo *shellInfo)
{
	int i;
	char *p;

	for (i = 0; i < 10; i++)
	{
		listNode *node = shellInfo->alias_list;

		while (node)
		{
			p = string_starts_with(node->value, shellInfo->command_arguments[0]);
			if (p && (*p == '=' || *p == '\0'))
			{
				free(shellInfo->command_arguments[0]);
				p = stCr(node->value, '=');
				if (p)
				{
					p = _strdup(p + 1);
					if (p)
					{
						shellInfo->command_arguments[0] = p;
						return (1);
					}
				}
				return (0);
			}
			node = node->next;
		}
	}

	return (0);
}


/**
 * stCr - add descr
 * @s: add descr
 * @c: add descr
 * Return: add descr
 */
char *stCr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * findReplacementValue - add descr
 * @shellInfo: add descr
 * @variable: add descr
 * Return: add descr
*/
char *findReplacementValue(commandInfo *shellInfo, const char *variable)
{
	const char *prefix = &variable[1];
	char *p = NULL;
	listNode *node = shellInfo->environment_variables;

	while (node)
	{
		p = string_starts_with(node->value, prefix);
		if (p && (!stCr(p, '=') || *(p + 1) == '='))
		{
			return (_strdup(stCr(node->value, '=') + 1));
		}
		node = node->next;
	}

	return (_strdup(""));
}

/**
 * replaceVars - add descr
 * @shellInfo: add descr
 * Return: add descr
*/
void replaceVars(commandInfo *shellInfo)
{
	int i = 0;

	while (shellInfo->command_arguments[i])
	{
		if (shellInfo->command_arguments[i][0] == '$'
		&& shellInfo->command_arguments[i][1])
		{
			if (!_strcmp(shellInfo->command_arguments[i], "$?"))
			{
				free(shellInfo->command_arguments[i]);
				shellInfo->command_arguments[i]
				= _strdup(itoa1(shellInfo->commandExecStatus, 10, 0));
			}
			else if (!_strcmp(shellInfo->command_arguments[i], "$$?"))
			{
				free(shellInfo->command_arguments[i]);
				shellInfo->command_arguments[i]
				= _strdup(itoa1(getpid(), 10, 0));
			}
			else
			{
				char *replacement = findReplacementValue(shellInfo
				, shellInfo->command_arguments[i]);
				free(shellInfo->command_arguments[i]);
				shellInfo->command_arguments[i] = replacement;
			}
		}
		i++;
	}
}

/**
 * itoa1 - itoa converter function
 * @num: add descr
 * @base: add descr
 * @flags: add descr
 * Return: string
 */
char *itoa1(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & 2) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}


