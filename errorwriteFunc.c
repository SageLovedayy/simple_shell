#include "main.h"


/**
 * print_error_char - Writes the character to the standard error stream.
 * @character: The character to print.
 *
 * Return: On success, returns 1. On error, -1 is returned, and errno is set appropriately.
 */
int print_error_char(char character)
{
	static int buffer_index;
	static char output_buffer[BUF_SIZE];

	if (character == FLUSH_BUFFER || buffer_index >= BUF_SIZE)
	{
		write(STDERR_FILENO, output_buffer, buffer_index);
		buffer_index = 0;
	}

	if (character != FLUSH_BUFFER)
		output_buffer[buffer_index++] = character;

	return 1;
}
