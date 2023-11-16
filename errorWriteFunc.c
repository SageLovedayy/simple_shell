#include "main.h"

/**
 * _fprintf - custom version of fprintf using write
 * @fd: file descriptor
 * @format: formatted string containing specifiers
 * @...: variable arguments
 * Return: number of characters printed
 */
int _fprintf(int fd, const char *format, ...)
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
				char *str = va_arg(args, char *);

				write(fd, str, _strlen(str));
				count += _strlen(str);
				break;
			}
			/* we will add more cases for more specifiers if ever needed */
			default:
				/* Handle unsupported specifier or just ignore it */
				write(fd, "%", 1);
				count++;
				break;
			}
		}
		else
		{
			write(fd, format, 1);
			count++;
		}

		format++;
	}

	va_end(args);

	return (count);
}


/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		print_error_char(str[i]);
		i++;
	}
}

/**
 * print_error - add descr
 * @shellInfo: add descr
 * @estr: add descr
 * Return: add descr
 */
void print_error(commandInfo *shellInfo, char *estr)
{
	_eputs(shellInfo->file_name);
	_eputs(": ");
	print_d(shellInfo->current_line_number, STDERR_FILENO);
	_eputs(": ");
	_eputs(shellInfo->command_arguments[0]);
	_eputs(": ");
	_eputs(estr);
}


/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}


/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == FLUSH_BUFFER || i >= BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}


/**
 * print_error_char - Writes the character to the standard error stream.
 * @character: The character to print.
 *
 * Return: On success, returns 1. On error, -1 is returned.
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

	return (1);
}




/**
 * print_error_string - Prints an input string to the standard error stream.
 * @error_string: The string to be printed.
 *
 * Return: Nothing.
 */
void print_error_string(char *error_string)
{
	int index = 0;

	if (!error_string)
		return;

	while (error_string[index] != '\0')
	{
		print_error_char(error_string[index]);
		index++;
	}
}


/**
 * write_to_fd - Writes the character to the given file descriptor.
 * @character: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: add descr
 */
int write_to_fd(char character, int fd)
{
	static int buffer_index;
	static char output_buffer[BUF_SIZE];

	if (character == FLUSH_BUFFER || buffer_index >= BUF_SIZE)
	{
		write(fd, output_buffer, buffer_index);
		buffer_index = 0;
	}

	if (character != FLUSH_BUFFER)
		output_buffer[buffer_index++] = character;

	return (1);
}

/**
 * print_to_fd - Prints an input string to the given file descriptor.
 * @input_string: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int print_to_fd(char *input_string, int fd)
{
	int count = 0;

	if (!input_string)
		return (0);

	while (*input_string)
	{
		count += write_to_fd(*input_string++, fd);
	}

	return (count);
}
