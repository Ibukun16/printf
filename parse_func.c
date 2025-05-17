#include "main.h"

/**
 * set_number - A function that retrieves a number from a given string
 * @str: The given string
 * @num: Pointer to the number
 *
 * Return: The number of positions that were moved
 */
int set_number(const char *str, int *num)
{
	char dgt[11] = {0};
	int n, m = 0;

	for (n = 0; str[n] != '\0'; n++)
	{
		if (m < 10 && is_digit(str[n]))
		{
			dgt[m] = str[n];
			m++;
		}
		else
			break;
	}
	*num = compare_numbers(dgt, MAX_WIDTH) <= 0 ? convert_str_to_int(dgt) : 0;
	return (n);
}

/**
 * set_length - Functio that set the length of a format specifier struct
 * @ch_cur: The current character
 * @fmat_spec: Pointer to the destination fmat_spec_def struct
 * @pos: The pointer to the current position in the format string
 */
void set_length(char ch_cur, int *pos, fmat_spec_def *fmat_spec)
{
	fmat_spec->is_long = ch_cur == 'l' ? TRUE : fmat_spec->is_long;
	fmat_spec->is_short = ch_cur == 'h' ? TRUE : fmat_spec->is_short;
	(*pos)++;
}

/**
 * set_flags - A function that sets the flags for a format specifier struct
 * @str: The character string that set the flag for set_flags
 * @fmat_spec: The pointer to the destination fmat_spec_def structure
 *
 * Return: The number of flags read.
 */
int set_flags(const char *str, fmat_spec_def *fmat_spec)
{
	int n = 0;

	while (str[n] != '\0' && is_flag(str[n]))
	{
		fmat_spec->space = str[n] == ' ' ? TRUE : fmat_spec->space;
		fmat_spec->left = str[n] == '-' || fmat_spec->left ? TRUE : FALSE;
		fmat_spec->pos_sign = str[n] == '+' || fmat_spec->pos_sign ? TRUE : FALSE;
		fmat_spec->group = str[n] == '\'' || fmat_spec->group ? TRUE : FALSE;
		fmat_spec->alt = str[n] == '#' || fmat_spec->alt ? TRUE : FALSE;
		fmat_spec->pad = str[n] == '0' ? '0' : fmat_spec->pad;
		n++;
	}
	return (n);
}

/**
 * set_precision - A function that reads a format spec data into a given struct
 * @str: The string containing the format token
 * @list: The arguments list
 * @fmat_spec: Pointer to the destination fmat_spec_def struct
 * @n: The pointer to the position in the format string
 * @err: Pointer to the error variable
 */
void set_precision(const char *str, va_list list, fmat_spec_def *fmat_spec,
		int *n, int *err)
{
	fmat_spec->is_precision_set = TRUE;
	if (str[*n] == '*')
	{
		fmat_spec->precision = va_arg(list, int);
		(*n)++;
	}
	else if (is_digit(str[*n]))
		*n += set_number(str + *n, &(fmat_spec->precision));
	else if (is_specifier(str[*n]))
		fmat_spec->precision = 0;
	else
		*err = -1;
}

/**
 * read_format - A function that read the format data into the given struct.
 * @str: The string containing the format tokens.
 * @list: The argument list.
 * @fmat_spec: Pointer to the destination fmat_spec_def struct
 * @last_tokn: Pointer to the last token in the format specifier
 *
 * Return: The number of positions to skip after the format character (%),
 * this is negative when there's an error.
 */
int read_format(const char *str, va_list list, fmat_spec_def *fmat_spec,
		int *last_tokn)
{
	int count = 0, order = 0, error = 0;

	if (!str || !fmat_spec || !last_tokn)
		return (-1);
	init_format_data(fmat_spec);
	while (str[count] != '\0' && !fmat_spec->specifier && !error)
	{
		if (is_flag(*(str + count)) && order < 1)
			count += set_flags(str + count, fmat_spec), order = 1;
		else if ((is_digit(*(str + count)) || *(str + count) == '*') && order < 2)
		{
			if (*(str + count) == '*')
				fmat_spec->width = va_arg(list, int), count++;
			else
				count += set_number(str +count, &fmat_spec->width);
			fmat_spec->is_width_set = TRUE, order = 2;
		}
		else if (*(str + count) == '.' && order < 3)
		{
			count++;
			set_precision(str, list, fmat_spec, &count, &error), order = 3;
		}
		else if (is_length(*(str + count)) && order < 4)
			set_length(*(str + count), &count, fmat_spec), order = 4;
		else if (is_specifier(*(str + count)) && order < 5)
		{
			fmat_spec->specifier = *(str +count), count++, order = 5;
			break;
		}
		else
			error = 1;
	}
	*last_tokn = order;
	return (count - 1);
}
