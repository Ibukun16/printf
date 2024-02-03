#include "main.h"
/**
 * _printf - A function that produces output based on a format.
 * @format: character string that specifies the format.
 *
 * Return: The character printed excluding the null byte
 * that ends the strings output.
 */
int _printf(const char *format, ...)
{
	unsigned int i, b;
	va_list varg;

	if (!format || !format[0])
		return (-1);
	va_start(varg, format);
	for (i = 0; format && format[i]; i++)
	{
		if (format[i] == '%')
		{
			if (format[i + 1] != '\0')
			{
				b += convert(format[i + 1], varg);
				i++;
			}
			else
			{
				va_end(varg);
				return (-1);
			}
		}
		else
			b += _putchar(format[i]);
	}
	va_end(varg);
	return (b);
}

/**
 * convert - A function that perform a specific command based
 * on the specifier.
 * @s: The specifier.
 * @varg: The argument listof the variable
 *
 * Return: Number of bytes.
 */
int convert(char s, va_list varg)
{
	int c = 0;

	if (s == 'c')
		c += _putchar(va_arg(varg, int));
	else if ((s == 's') ||
		 (s == 'S') ||
		 (s == 'r') ||
		 (s == 'R'))
		c += prnt_stg(varg, s);
	else if (s == '%')
		c += _putchar('%');
	else if (s == 'd' || s == 'i')
		c += int_prnt(varg);
	else if ((s == 'o') ||
		 (s == 'u') ||
		 (s == 'b') ||
		 (s == 'x') ||
		 (s == 'X'))
		c += bioc_unsg(varg, s);
	else
	{
		_putchar('%');
		_putchar(s);
		c += 2;
	}
	return (c);
}

