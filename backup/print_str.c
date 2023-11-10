#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

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
 * main - printstr entry point
 * Return: always 0
 */
int main(void)
{
	int num, num1;

	num = print_str("Let's try to printf a simple sentence.\n");
	num1 = printf("Let's try to printf a simple sentence.\n");
	printf("return value _printf: %d\n return value printf: %d\n\n", num, num1);

	num = print_str("String:[%s]\n", "I am a string !");
	num1 = printf("String:[%s]\n", "I am a string !");
	printf("return value _printf: %d\n return value printf: %d\n\n", num, num1);

	return (0);
}
