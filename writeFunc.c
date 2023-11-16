#include "main.h"

/**
 * string_to_integer - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: 0 if no numbers in the string, converted number otherwise.
 *		 -1 on error.
 */
int string_to_integer(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result);
}


/**
 * print_decimal - Prints a decimal (integer) number (base 10).
 * @input: The input.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int print_decimal(int input, int fd)
{
	int (*output_char)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		output_char = print_error_char;

	if (input < 0)
	{
		absolute_value = -input;
		output_char('-');
		count++;
	}
	else
	{
		absolute_value = input;
	}

	current = absolute_value;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			output_char('0' + current / i);
			count++;
		}
		current %= i;
	}

	output_char('0' + current);
	count++;

	return (count);
}

/**
 * number_to_string - Converts a number to a string.
 * @num: Number.
 * @base: Base.
 * @flags: Argument flags.
 *
 * Return: String.
 */
char *number_to_string(long int num, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & 2) && num < 0) /*2 = unsigned, 1 = lowercase*/
	{
		n = -num;
		sign = '-';
	}

	digits = flags & 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = digits[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments_in_string - Replaces the first instance of '#' with '\0'.
 * @buffer: Address of the string to modify.
 *
 * Return: Always 0.
 */
void remove_comments_in_string(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}
