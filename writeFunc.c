#include "main.h"

/**
 * _fprintf - add descr
 * @fd: add descr
 * @format: add descr
 * Return: count
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
			/*we will add cases for any other specifiers we need*/
			default:
				/*Handle unsupported specifier or just ignore it*/
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
			/* add more cases for other specifiers as needed */
			default:
				/*Handle unsupported specifier or just ignore it*/
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
 * _putchar - writes the character c to stdout
 * @c: character
 * Return: On success 1.
 * On error, -1 is returned, and errno set.
*/
int _putchar(char c)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == FLUSH_BUFFER || i >= BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;

	return (1);
}
