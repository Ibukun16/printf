#include "main.h"

void print_buffer(char buffer[], int *buff_ind);
/**
 * _printf - A function that produces output based on a format.
 * @format: character string that specifies the format.
 *
 * Return: The character printed excluding the null byte
 * that ends the strings output.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, p_chars = 0;
	int flgs, wdt, prec, siz, buf_idx = 0
	va_list varg;
	char buff[array];

	if (!format || !format[0])
		return (-1);
	va_start(varg, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buff[buf_ixd++] = format[i];
			if (buf_idx == array)
				print_buffer(buff, &buff_idx);
			p_chars++;
		}
		else
		{
			print_buffer(buff, &buf_idx);
			flgs = get_flags(format, &i);
			wdt = get_width(format, &i, varg);
			siz = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, varg, buff, flgs,
					wdt, prec, siz);
			if (printed == -1)
				return (-1);
			p_chars += printed;
		}
	}
	print_buffer(buff, &buff_idx);
	va_end(varg);

	return (p_chars);
}
		
/**
 * print_buffer - Prints the contents of the buffer if it exists
 *
 * @buff: Array of chars
 * @buf_idx: Index at which to add next char, presenting the length.
 */
void print_buffer(char buff[], int *buf_idx)
{
	if (*buf_idx > 0)
		write(1, &buf[0], *buf_idx);

	*buf_idx = 0;
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

