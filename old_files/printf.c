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
	int i, p_chars = 0, buf_idx = 0;
	int flgs, wdt, prec, siz;
	va_list varg;
	char buff[BUFF_SIZE];

	if (!format || !format[0])
		return (-1);

	va_start(varg, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buff[buf_idx++] = format[i];
			if (buf_idx == BUFF_SIZE)
				print_buffer(buff, &buf_idx);
			p_chars++;
		}
		else
		{
			print_buffer(buff, &buf_idx);
			flgs = get_flags(format, &i);
			wdt = get_width(format, &i, varg);
			prec = get_precision(format, &i, varg);
			siz = get_size(format, &i);
			++i;
			p_chars = print_handler(format, &i, varg, buff, flgs,
					wdt, prec, siz);

			if (p_chars == -1)
				return (-1);
		}
	}
	print_buffer(buff, &buf_idx);
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
		write(1, &buff[0], *buf_idx);

	*buf_idx = 0;
}
