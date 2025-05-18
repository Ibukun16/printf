#include "main.h"

/**
 * _printf - A function that produces output according to a format
 * @format: Format specifier for the output to be printed.
 *
 * Return: the number of characters printed without the null byte.
 */
int _printf(const char *format, ...)
{
	int idx = 0, tmp, esc_processing = 0, err = 1, last_tkn;
	fmat_spec_def fmat_data;
	va_list args;

	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	va_start(args, format);
	to_buf(0, BUF_INIT);
	for (idx = 0; format[idx] != '\0'; idx++)
	{
		if (!esc_processing)
		{
			if (format[idx] == '%')
				esc_processing = 1;
			else
				put_charto_buf(format[idx]);
		}
		else
		{
			tmp = read_format(format + idx, args, &fmat_data, &last_tkn);
			esc_processing = 0;
			set_format_error(format, &idx, tmp, last_tkn, &err);
			if (is_specifier(fmat_data.specifier))
				set_format(&args, &fmat_data);
			idx += (is_specifier(fmat_data.specifier) ? tmp: 0);
		}
	}
	to_buf(0, BUF_FLUSH);
	va_end(args);
	return (err <= 0 ? err : to_buf('\0', BUF_COUNT));
}

/**
 * to_buf - A function that prints the contents of a buffer if it exists
 * @c: The string of characters to print from the buffer.
 * @flag: Flag that controls the action to be taken.
 * -1-> reset the static variables
 * 0-> write character to buffer
 * 1-> Don't write to buffer but empty buffer onto stdout
 * -2-> The number of character written to stdout)
 *
 * Return: 0 for success and -1 for error, set error no appropriately
 */
int to_buf(char c, char flag)
{
	static int idx;
	static char buffer[1024];
	static int char_count;
	static char out;

	if (flag == 0 && idx < (int)sizeof(buffer))
	{
		buffer[idx++] = c;
		char_count++;
	}

	if (flag == 1 || idx >= (int)sizeof(buffer))
	{
		if (idx > 0)
		{
			out = write(1, buffer, idx);
			fflush(stdout);
			idx = 0;
			mem_set(buffer, 0, sizeof(buffer));
		}
	}
	if (flag == -1)
	{
		idx = 0;
		char_count = 0;
		mem_set(buffer, 0, sizeof(buffer));
	}

	if (flag == -2)
		return (char_count);
	return (out);
}

/**
 * put_charto_buf - A function that writes character c to the buffer
 * @c: The character to print
 *
 * Return: 1 for success else -1 and set the errno
 */
int put_charto_buf(char c)
{
	return (to_buf(c, 0));
}

/**
 * putstr_to_buf - Function that write string to the buffer
 * @str: The string to write to stdout
 *
 * Return: 1 for success, else -1 for error and set thr errno
 */
int putstr_to_buf(char *str)
{
	int output, n = 0;

	if (!str)
		return (-1);
	while (str[n] != '\0')
	{
		output = put_charto_buf(*(str + n));
		if (output == -1)
			return (-1);
		n++;
	}
	return (output);
}

/**
 * set_format - A function that set the appropriate format against a given
 * parameter.
 * @args: The argument list
 * @format_det: Details about the format that was read.
 *
 * Return: void.
 */
void set_format(va_list *args, fmat_spec_def *format_det)
{
	int n;

	set_specifier specifier_type[] = {
		{'%', set_percent_fmat},
		{'p', set_pointer_fmat},
		{'c', set_char_fmat},
		{'s', set_string_fmat},
		{'d', set_dec_fmat},
		{'i', set_dec_fmat},
		{'X', set_hexadec_fmat},
		{'x', set_hexadec_fmat},
		{'o', set_octadec_fmat},
		{'u', set_unsigned_int_fmat},
		/* # begin custom specifiers */
		{'b', set_binary_fmat},
		{'R', set_rot13_fmat},
		{'r', set_revstr_fmat},
		{'S', set_hexacode_fmat},
		/* #end */
		{'F', set_double_fmat},
		{'f', set_double_fmat},
	};
	for (n = 0; n < 23 && specifier_type[n].specifier != '\0'; n++)
		if (format_det->specifier == specifier_type[n].specifier)
		{
			specifier_type[n].print(args, format_det);
			break;
		}
}
