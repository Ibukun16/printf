#include "main.h"

/**
 * set_dec_fmat - a function that set the format for printing signed int.
 * @list: The list of arguments to be printed.
 * @fmat_spec: The format specifier details.
 *
 * Return: void.
 */
void set_dec_fmat(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, padding = 0, zeros = 0, len;
	long num;
	char *str, sign;

	if (fmat_spec->is_long)
		num = va_arg(*list, long);
	else if (fmat_spec->is_short)
		num = (short)va_arg(*list, long);
	else
		num = va_arg(*list, int);
	str = convert_long_to_str(num);
	if (!str)
		return;
	sign = (num >= 0 && (fmat_spec->pos_sign || fmat_spec->space)) ? 1 : 0;
	if (fmat_spec->is_precision_set && !fmat_spec->precision && !num)
		print_ntimes(' ', fmat_spec->width);
	else
	{
		len = str_len(str) + (sign ? 1 : 0);
		if (fmat_spec->is_precision_set)
			zeros = MAX(fmat_spec->precision +
				(sign || num < 0 ? 1 : 0), len) - len;
		else
			zeros = (fmat_spec->pad == '0') ?
				MAX(fmat_spec->width, len) - len : 0;
		if (fmat_spec->is_width_set)
			padding = MAX(fmat_spec->width, len) - len - zeros;
		if (!fmat_spec->left)
			for (count = 0;  count < padding; count++)
				put_charto_buf(' ');
		if (num < 0 || sign)
			put_charto_buf(
				num < 0 ? '-' : (fmat_spec->space &&
					!fmat_spec->pos_sign ? ' ' : '+'));
		put_numto_buf(zeros, num, str);
		if (fmat_spec->left)
			for (count = 0; count < padding; count++)
				put_charto_buf(' ');
	}
	free(str);
}

/**
 * set_hexadec_fmat - A function that set the format of haxadecimal
 * of an unsigned integer for printing.
 * @list: The argument list
 * @fmat_spec: The format specifier details.
 *
 * Return: void.
 */
void set_hexadec_fmat(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, padding, zeros, width_max, len, p_max;
	unsigned long num;
	char *s;

	if (fmat_spec->is_short)
		num = (va_arg(*list, unsigned long) << 2 * 8) >> 2 * 8;
	else if (fmat_spec->is_long)
		num = va_arg(*list, unsigned long);
	else
		num = va_arg(*list, unsigned int);
	s = unsigned_long_to_hex(num, fmat_spec->specifier == 'X');
	if (!s)
		return;
	if (fmat_spec->is_precision_set && !fmat_spec->precision && !num)
		print_ntimes(' ', fmat_spec->width);
	else
	{
		len = str_len(s) + (num ? fmat_spec->alt * 2 : 0);
		width_max = MAX(fmat_spec->width, len);
		p_max = MAX(fmat_spec->precision, len);
		zeros = (p_max - len) * !fmat_spec->left;
		padding = width_max - (NO_NEG(zeros) + len);
		for (count = 0; !fmat_spec->left && count < padding; count++)
			put_charto_buf(fmat_spec->pad);
		if (fmat_spec->alt && num)
			putstr_to_buf(fmat_spec->specifier == 'X' ? "0X" : "0x");
		for (count = 0; count < zeros; count++)
			put_charto_buf('0');
		for (count = 0; s[count] != '\0'; count++)
			put_charto_buf(s[count]);
		for (count = 0; fmat_spec->left && count < padding; count++)
			put_charto_buf(' ');
	}
	free(s);
}

/**
 * set_octadec_fmat - A function that set the format for
 * octadecimal of signed
 * integer to print.
 * @list: the argument list
 * @fmat_spec: The format specifier details.
 *
 * Return: void.
 */
void set_octadec_fmat(va_list *list, fmat_spec_def *fmat_spec)
{
	unsigned long num;
	char *s;
	 int count = 0, zeros = 0, len = 0, padding = 0;
	 int num_len = 0, width_max = 0, p_max = 0;

	if (fmat_spec->is_long)
		num = va_arg(*list, unsigned long);
	else if (fmat_spec->is_short)
		num = (va_arg(*list, unsigned long) << 2 * 8) >> 2 * 8;
	else
		num = va_arg(*list, unsigned int);
	s = convert_long_to_oct(num);
	if (!s)
		return;
	num_len = str_len(s);
	if (fmat_spec->is_precision_set && !fmat_spec->precision && !num)
		print_ntimes(' ', fmat_spec->width);
	else
	{
		len = NO_LESS(str_len(s), 1);
		width_max = MAX(fmat_spec->width, len);
		p_max = MAX(fmat_spec->precision, len);
		zeros = (p_max - num_len) * !fmat_spec->left;
		padding = width_max - (NO_NEG(zeros) + len);
		for (count = 0; !fmat_spec->left && count < padding; count++)
			put_charto_buf(fmat_spec->pad);
		if (fmat_spec->alt && zeros == 0 && num)
			put_charto_buf('0');
		for (count = 0; count < zeros; count++)
			put_charto_buf('0');
		for (count = 0; s[count] != '\0'; count++)
			put_charto_buf(s[count]);
		for (count = 0; fmat_spec->left && count < padding; count++)
			put_charto_buf(' ');
	}
	free(s);
}


/**
 * set_unsigned_int_fmat - A function that set the format for
 * printing unsigned integer.
 * @list: The argument list
 * @fmat_spec: The format specifier details.
 *
 * Return: void.
 */
void set_unsigned_int_fmat(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, padding = 0, zeros = 0, len;
	unsigned long num, width_max, p_max;
	char *s;

	if (fmat_spec->is_long)
		num = va_arg(*list, unsigned long);
	else if (fmat_spec->is_short)
		num = (short)va_arg(*list, unsigned int) << 2 * 8) >> 2 * 8;
	else
		num = va_arg(*list, unsigned int);
	s = convert_u_long_to_str(num, 0);
	if (!s)
		return;
	if (FMT_PREC_EMPTY(fmat_spec) && num == 0)
		print_ntimes(' ', fmat_spec->width);
	else
	{
		len = str_len(s);
		width_max = MAX(fmat_spec->width, len);
		p_max = MAX(fmat_spec->precision, len);
		zeros = (p_max - len) * !fmat_spec->left;
		len = width_max - (NO_NEG(zeros) + len);
		for (count = 0; !fmat_spec->left && count < padding; count++)
			put_charto_buf(fmat_spec->pad);
		for (count = 0; count < zeros; count++)
			put_charto_buf('0');
		for (count = 0; s[count] != '\0'; count++)
			put_charto_buf(s[count]);
		for (count = 0; fmat_spec->left && count < padding; count++)
			put_charto_buf(' ');
	}
	free(s);
}

