#include "main.h"

/**
 * set_float_parts - A function that set the float type field to the
 * appropriate parts of a given float
 * @num: The given float
 * @exp_size: The size of the exponential part
 * @mant_size: The size of the mantissa part
 * @float_t: The float type structure
 */
void set_float_parts(double num, u_char_typ exp_size, u_char_typ mant_size,
		float_typ *float_t)
{
	int n;
	char *str;
	un u;
	u_char_typ size = exp_size + mant_size + 1;

	if (float_t == NULL || float_t->exp == NULL || float_t->mantissa == NULL)
		return;
	u.duo = num;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return;

	for (n = 0; n < size; n++)
		str[n] = (u.bits >> (63 - n) & 1) + '0';
	str[size] = '\0';

	rev_string(str);
	float_t->float_sign = *str;
	for (n = 0; n < exp_size; n++)
		float_t->exp[n] = str[n + 1];
	float_t->exp[n] = '\0';

	for (n = 0; n < mant_size; n++)
		float_t->mantissa[n] = str[n + exp_size + 1];
	float_t->mantissa[n] = '\0';
	free(str);
}

/**
* mantissa_to_dec_frac - A function that converts mantissa of a float
* to fraction
* @mantis: The given mantissa to convert
* @frac_len: The maximum length of the decimal fraction
*
* Return: The converted fraction
*/
char *mantissa_to_dec_frac(char *mantis, unsigned short frac_len)
{
	char *res, *pwr, *str;
	int n, len = str_len(mantis);

	res = malloc(sizeof(char) * (frac_len + 3));
	if (!res)
		return (NULL);
	mem_set(res, '0', frac_len + 2);
	res[1] = '.';
	res[frac_len + 2] = '\0';

	for (n = 0; n < len; n++)
	{
		if (mantis[n] == '1')
		{
			pwr = compute_npower_of_two(-(n + 1));
			if (!pwr)
			{
				free(res);
				return (NULL);
			}
			str = add_positive_float_nums(pwr, res, TRUE);
			if (!str)
			{
				free(res);
				return (NULL);
			}
			free(res);
			res = str;
		}
	}
	return (res);
}

/**
 * float_to_str - A function that converts an IEEE 754 float number to
 * its string val
 * @float_dat: The information about the float
 * @free_flt: A flag that determines if the numbers are to be freed
 *
 * Return: The string representation of the float, else NULL
 */
char *float_to_str(float_typ *float_dat, bool free_flt)
{
	u_char_typ exp_size = str_len(float_dat->exp);
	short bias = pos_num_powerof_two(exp_size) / 2 - 1;
	short exponent = convert_bin_to_int(float_dat->exp) - bias;
	char *pwr = compute_npower_of_two(exponent);
	unsigned short frac_len = 22;
	char *fraction = mantissa_to_dec_frac(float_dat->mantissa, frac_len);
	char *prod = NULL, *float_num = NULL, *pw_fr = NULL;

	if (!pwr || !fraction)
		goto cleanup;

	fraction[0] = '1';
	if (exponent >= 0)
	{
		pw_fr = malloc(sizeof(char) * 3);
		if (!pw_fr)
			goto cleanup;
		pw_fr[0] = '.';
		pw_fr[1] = '0';
		pw_fr[2] = '\0';
		str_cat(pwr, pw_fr, TRUE);
	}
	prod = multiply_float(fraction, pwr, TRUE);
	if (!prod)
		goto cleanup;
	float_num = str_cat(float_dat->float_sign == '1' ? "-" : "", prod, FALSE);
	free(prod);
	if (free_flt)
		free_float_data(float_dat);
	return (float_num);

cleanup:
	free(pwr);
	free(fraction);
	free(pw_fr);
	if (free_flt)
		free_float_data(float_dat);
	return (NULL);
}

