#include "main.h"

/*** HANDLE PRINT FUNCTION ***/
/**
 * print_handler - Function that prints argument based on type
 * @fmt: string format to print the arguments
 * @ags: List of arguments
 * @idx: Index to the print paramater
 * @buf: The buffer that handles the arrayy.
 * @flgs:Active flags specifier
 * @wdt: The width identifier
 * @prec: The precision specifier
 * @siz: The size specifier
 *
 * Return: 1 or 2;
 */
int print_handler(const char *fmt, int *idx, va_list ags, char buf[],
		int flgs, int wdt, int prec, int siz)
{
	int n, len = 0, chars_prt = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsgned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_upper_hex}, {'p', pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', rot13_string}, {'\0', NULL}
	};
	for (n = 0; fmt_types[n].fmt != '\0'; n++)
		if (fmt[*idx] == fmt_types[n].fmt)
			return (fmt_types[n].func(ags, buf, flgs, wdt, prec, siz));

	if (fmt_types[n].fmt == '\0')
	{
		if (fmt[*idx] == '\0')
			return (-1);
		len += write(1, "%%", 1);
		if (fmt[*idx - 1] == ' ')
			len += write(1, " ", 1);
		else if (wdt)
		{
			--(*idx);
			while (fmt[*idx] != ' ' && fmt[*idx] != '%')
				--(*idx);
			if (fmt[*idx] == ' ')
				--(*idx);
			return (1);
		}
		len += write(1, &fmt[*idx], 1);
		return (len);
	}
	return (chars_prt);
}
