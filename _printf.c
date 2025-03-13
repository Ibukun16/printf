#include "main.h"

/**
 * _printf - A function that produces output according to a format
 * @format: Format specifier for the output to be printed.
 *
 * Return: the number of characters printed without the null byte.
 */
int _printf(const char *format, ...)
{
	int idx;
	char c, *str;
	va_list args;

	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	va_start(args, format);
	while (format[idx] != '\0')
	{
		if (format[idx] == '%' && (format[idx + 1] == 'c' ||
					format[idx + 1] == 's' || format[idx + 1] == '%'))
			idx++;
		if (format[idx] == 'c')
		{
			c = va_arg(args, int);
			put_charto_buf(c);
		}
		else if (format[idx] == 's')
		{
			str = va_arg(args, char *);
			if (str)
				putstr_to_buf(str);
			else
				putstr_to_buf("(null)");
		}
		else if (format[idx] == '%')
			put_charto_buf('%');
		else
			put_charto_buf(format[idx]);
		idx++;
	}
	print_buf(0, 1);
	va_end(args);
	return (print_buf('\0', -2));
}

/**
 * print_buf - A function that prints the contents of a buffer if it exists
 * @c: The string of characters to print from the buffer.
 * @flag: Flag that controls the action to be taken.
 * -1-> reset the static variables
 * 0-> write character to buffer
 * 1-> Don't write to buffer but empty buffer onto stdout
 * -2-> The number of character written to stdout)
 *
 * Return: The correct output as indicated by the flag else 0 for
 * success and -1 for error.
 */
int print_buf(char c, char flag)
{
	static int idx;
	static char buffer[1024];

	if (flag == 0 && idx < sizeof(buffer))
	{
		buffer[idx++] = c;
	}

	if (flag == 1 || idx >= sizeof(buffer))
	{
		ssize_t bytes_written = write(1, buffer, idx);

		if (bytes_written == -1)
			return (-1);
		idx = 0;
	}

	if (flag == -1)
	{
		idx = 0;
		mem_set(buffer, 0, sizeof(buffer));
	}

	if (flag == -2)
	{
		return (idx);
	}
	return (0);
}

/**
 * put_charto_buf - A function that writes character c to the buffer
 * @c: The character to print
 *
 * Return: 1 for success else -1 and set the errno
 */
int put_charto_buf(char c)
{
	return (print_buf(c, 0));
}

/**
 * putstr_to_buf - Function that write string to the buffer
 * @str: The string to write to stdout
 *
 * Return: 1 for success, else -1 for error and set thr errno
 */
int putstr_to_buf(char *str)
{
	int n, output;

	if (!str)
		return (-1);
	while (*str)
	{
		output = put_charto_buf(*str);
		if (output == -1)
			return (-1);
		str++;
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
	int count;

	set_specifier specifier_type[] = {
		{'%', set_percent_fmat},
		{'p', set_p_fmat},
		{'c', set_c_fmat},
		{'s', set_s_fmat},
		{'d', set_d_fmat},
		{'i', set_i_fmat},
		{'X', set_bigX_fmat},
		{'x', set_smallx_fmat},
		{'o', set_o_fmat},
		{'u', set_u_fmat},
		/* # begin custom specifiers */
		{'b', set_b_fmat},
		{'R', set_R_fmat},
		{'r', set_r_fmat},
		{'S', set_S_fmat},
		/* #end */
		{'F', set_bigF_fmat},
		{'f', set_smallf_fmat},
	};
	for (count = 0; count < 23 && specifier_type[count].spec != '\0'; count++)
		if (fmat_spec->spec == specifier_type[count].spec)
		{
			specifier_type[count].print_args(args, fmat_spec);
			break;
		}
}
