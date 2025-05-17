#include "main.h"

/**
 * print_ntimes - A function that prints a character n number of times
 * @c: The character to print.
 * @n: The number of times to print character c.
 *
 * Return void.
 */
void print_ntimes(char c, int n)
{
	int count;

	for (count = 0; count < n; count++)
		put_charto_buf(c);
}

/**
 * print_nchars - A function that prints multiple characters.
 * @n: The number of characters to print
 *
 * Return: void.
 */
void print_nchars(int n, ...)
{
	int count;
	va_list list;

	if (n <= 0)
		return;
	va_start(list, n);
	for (count = 0; count < n; count++)
		put_charto_buf(va_arg(list, int));
	va_end(list);
}

/**
 * is_letter - A function that checks if a given character is a character
 * @c: The character to check
 *
 * Return: 1 if c is a letter else 0.
 */
char is_letter(char c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? TRUE : FALSE);
}

/**
 * set_error - A function that set the format error after reading format
 * specifier.
 * @format: The format.
 * @index: The current position of the string format
 * @len: The length of the format specifier minus 1.
 * @last_tokn: The last token from the format specifier
 * @error: The error flag.
 *
 * Return: void.
 */
void set_format_error(const char *format, int *index, int len,
		int last_tokn, int *error)
{
	char next_c;
	int count;

	if (*index + len + 1 >= 0 && format[*index + len] != '\0')
	{
		next_c = format[*index + len + 1];
		if (last_tokn == 1 && next_c == '\0')
			*error = -1;
		else if ((last_tokn == 2 || last_tokn == 3) && next_c == '\0')
		{
			*error = -1;
			*index += len - 1;
		}
		else if (last_tokn == 4 && next_c == '\0')
			*error = -1;
		else
			*error = 1;

		if (next_c != '\0' && last_tokn != 5)
		{
			put_charto_buf('%');
			for (count = 0; count < len; count++)
			{
				if (!is_length(format[*index + count]))
					put_charto_buf(format[*index + count]);
			}
			*index += len;
		}
	}
	else
		*error = -2;
}

/**
 * put_numto_buf - A function that prints number into the buffer
 * @zeros: The number of zeros to print
 * @num: The number to print to buffer
 * @str: The string representation of the number
 *
 * Return: void.
 */
void put_numto_buf(int zeros, long num, char *str)
{
	int count;

	for (count = 0; count < zeros; count++)
		put_charto_buf('0');
	for (count = num < 0 ? 1 : 0; str[count] != '\0'; count++)
		put_charto_buf(str[count]);
}
