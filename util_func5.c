#include "main.h"

/**
 * ptr_to_str - A function that converts pointer to str
 * @ptr: The pointer to convert
 *
 * Return: The converted string representation of the pointer
 */
char *ptr_to_str(void *ptr)
{
	char *res, *hex_part, *prefix = "0x";
	int dgt, n = 0, size;
	uintptr_t tmp;

	if (!ptr)
	{
		res = malloc(sizeof("(nil)"));
		if (!res)
			return (NULL);
		return (strn_copy(res, "(nil)", 0));
	}
	tmp = (uintptr_t)ptr;
	size = sizeof(uintptr_t) * 2;
	hex_part = malloc(sizeof(char) * (size + 1));
	if (!hex_part)
		return (NULL);
	mem_set(hex_part, size, '0');
	do {
		dgt = tmp % 16;
		hex_part[n] = dgt < 10 ? dgt + '0' : dgt - 10 + 'a';
		tmp /= 16;
	} while (tmp > 0);
	hex_part[n] = '\0';
	rev_string(hex_part);
	res = malloc(sizeof(char) * (str_len(prefix) + str_len(hex_part) + 1));
	if (!res)
	{
		free(hex_part);
		return (NULL);
	}
	strn_copy(res, prefix, 0);
	str_cat(res, hex_part, TRUE);
	return (res);
}

/**
 * is_invalid - A function that checks if a given float is invalid
 * @flot_data: The structure of the float data to check
 *
 * Return: NULL if it is invalid, otherwise inf or nan
 */
char *is_invalid(float_typ *flot_data)
{
	int exp_bits = 0, mant_bits = 0;
	int lsb_on = 0, msb_on = 0, n;
	int mant_len = str_len(flot_data->mantissa);
	int exp_len = str_len(flot_data->exp);

	if (!flot_data || !flot_data->mantissa || !flot_data->exp)
		return (NULL);
	for (n = 0; flot_data->exp[n] != '\0'; n++)
	{
		if (flot_data->exp[n] == '1')
			exp_bits++;
	}
	if (exp_bits != exp_len)
		return (NULL);
	msb_on = flot_data->mantissa[0] == '1';
	lsb_on = flot_data->mantissa[mant_len - 1] == '1';
	for (n = 0; flot_data->mantissa[n] != '\0'; n++)
		if (flot_data->mantissa[n] == '1')
			mant_bits++;

	if (mant_bits == 0)
		return (strn_copy(NULL, "inf", 0));

	if ((mant_bits == 1 && lsb_on) ||
		(mant_bits == 2 && lsb_on && msb_on) ||
		(mant_bits == mant_len))
		return (strn_copy(NULL, "nan", 0));
	return (NULL);
}
