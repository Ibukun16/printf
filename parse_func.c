#include "main.h"

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
	int count = 0, err = 0, order = 0;

	init_format_data(fmat_spec);
	for (; str && *(str + count) != '\0' && !fmat_spec->specifier && err == 0)
	{
		if (is_specifier(*(str + count)) && order < 5)
		{
			fmat_spec->specifier = *(str + count), count++, order = 5;
			break;
		}
		else
		{
			err = -1;
		}
	}
	*last_tokn = order;
	return (count - 1);
}
