#include "main.h"

/**
 * set_percent_fmat - A function that set format for printing percent sign (%).
 * @args: The list of arguments to be printed.
 * @fmat_spec: The format specifier details.
 *
 * Return: void.
 */
void set_percent_fmat(va_list *args, fmat_spec_def *fmat_spec)
{
	(void)args;
	(void) fmat_spec;
	put_charto_buf('%');
}

/**
 * set_pointer_fmat - A function that set format for printing pointer address
 * @args: The list of arguments to be printed.
 * @fmat_spec: The format specifier details.
 *
 * Return: void.
 */
void set_pointer_fmat(va_list *args, fmat_spec_def *fmat_spec)
{
        int count, len, padding;
	void *ptr = va_arg(*args, void *);
	char *str;

	if (!ptr)
	{
		putstr_to_buf("(nil)");
		return;
	}

	str = ptr_to_str(ptr);
	if (!str)
	{
		putstr_to_buf("(bull)");
		return;
	}

	len = str_len(str);
	padding = MAX(len, fmat_spec->width) - len;
	if (!fmat_spec->left)
	{
		for (count = 0; count < padding; count++)
			put_charto_buf(' ');
	}

	putstr_to_buf(str);

	if (fmat_spec->left)
	{
		for (count = 0; count < padding; count++)
			put_charto_buf(' ');
	}
	free(str);
}

/**
 * set_char_fmat - a function that set the format for printing character
 * @args: The list of arguments to be printed.
 * @fmat_spec: The format specifier details.
 *
 * Return: void.
 */
void set_char_fmat(va_list *args, fmat_spec_def *fmat_spec)
{
	int count, len = 1, padding;
	char str = va_arg(*args, int);

	padding = MAX(len, fmat_spec->width) - len;
	if (!fmat_spec->left)
		for (count = 0; count < padding; count++)
			put_charto_buf(' ');
	put_charto_buf(str);

	if (fmat_spec->left)
		for (count = 0; count < padding; count++)
			put_charto_buf(' ');
}

/**
 * set_string_fmat - a function that set the format for printing character
 * @args: The list of arguments to be printed.
 * @fmat_spec: The format specifier details.
 *
 * Return: void.
 */
void set_string_fmat(va_list *args, fmat_spec_def *fmat_spec)
{
	int count, len, padding;
	char *str = va_arg(*args, char *);
	char null[] = "(null)";

	str = str ? str : null;
	len = fmat_spec->is_precision_set && fmat_spec->precision >= 0 ?
		fmat_spec->precision : str_len(str);
	padding = MAX(len, fmat_spec->width) - len;
	if (!fmat_spec->left)
		for (count = 0; count < padding; count++)
			put_charto_buf(' ');

	for (count = 0; count < len && str[count] != '\0'; count++)
		put_charto_buf(str[count]);

	if (fmat_spec->left)
		for (count = 0; count < padding; count++)
			put_charto_buf(' ');
}
