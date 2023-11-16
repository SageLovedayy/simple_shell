#include "main.h"

/**
 * copy_string - Copies a string from source to destination.
 * @destination: The destination buffer.
 * @source: The source string.
 * Return: Pointer to the destination buffer.
 */
char *copy_string(char *destination, const char *source)
{
	int index = 0;

	if (destination == source || source == NULL)
		return (destination);

	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}

	destination[index] = '\0';
	return (destination);
}

/**
 * duplicate_string - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *duplicate_string(const char *str)
{
	int length = 0;
	char *duplicate;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	duplicate = malloc(sizeof(char) * (length + 1));

	if (!duplicate)
		return (NULL);

	for (length++; length--;)
		duplicate[length] = *--str;

	return (duplicate);
}

/**
 * print_string - Prints a string to the standard output.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void print_string(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		write(1, &str[index], 1);
		index++;
	}
}

/**
 * write_character - Writes a character to the standard output buffer.
 * @character: The character to write.
 *
 * Return: On success, returns 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_character(char character)
{
	static int buffer_index;
	static char output_buffer[BUF_SIZE];

	if (character == FLUSH_BUFFER || buffer_index >= BUF_SIZE)
	{
		write(1, output_buffer, buffer_index);
		buffer_index = 0;
	}

	if (character != FLUSH_BUFFER)
		output_buffer[buffer_index++] = character;

	return (1);
}



/*=============USED===============================*/
/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}
