#include "main.h"

/**
 * set_double_format - A function that set the format for decimal of a double
 * for printing.
 * @list: The list of the argument.
 * @fmat_spec: The format specifier details
 *
 * Return: void.
 */
void set_double_fmat(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, len, padding, zeros, width_max;
	double num = va_arg(*list, double);
	char *s, signd = (num >= 0 && fmat_spec->pos_sign) || num < 0;
	u_short_typ size_exp = fmat_spec->is_long_double ? 15 : 11;
	u_short_typ size_mant = fmat_spec->is_long_double ? 64 : 52;
	float_typ *floatt;

	floatt = create_new_float(size_exp, size_mant);
	if (!floatt)
		return;
	set_float_parts(num, size_exp, size_mant, floatt);
	s = is_invalid(floatt);
	if (s == NULL)
	{
		s = float_to_str(floatt, FALSE);
		s = round_float(s, fmat_spec->is_precision_set ?
				fmat_spec->precision : 6);
		len = str_len(s) + (signd ? 1 : 0);
		width_max = MAX(fmat_spec->width, len);
		zeros = (!fmat_spec->left && fmat_spec->pad == '0') ? width_max - len : 0;
		padding = width_max - (zeros + len);
		for (count = 0; !fmat_spec->left && count < padding; count++)
			put_charto_buf(' ');
		if (signd)
			put_charto_buf(num < 0 ? '-' : '+');
		for (count = 0; !fmat_spec->left && count < zeros; count++)
			put_charto_buf('0');
		for (count = signd ? 1 : 0; s[count] != '\0'; count++)
			put_charto_buf(s[count]);
		for (count = 0; fmat_spec->left && count < padding; count++)
			put_charto_buf(' ');
	}
	else
		for (count = 0; count < str_len(s); count++)
			put_charto_buf(fmat_spec->specifier == 'f' ?
					TO_LOWER(s[count]) : TO_UPPER(s[count]));
	if (s)
		free(s);
	free_float_data(floatt);
}
