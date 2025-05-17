#include "main.h"

/**
 * convert_unsigned_to_str - A function that converts an unsigned long integer
 * to its string representation.
 * @num: The unsigned long long integer value
 *
 * Return: The string representation of the unsigned long integer
 */
char *convert_u_long_to_str(unsigned long num, int neg)
{
	char res[21], *str;
	unsigned long i = 20, n, size;

	res[i] = '\0';
	if (num == 0)
		res[--i] = '0';
	else
	{
		while (num > 0 && i > 0)
		{
			res[--i] = (num % 10) + '0';
			num /= 10;
		}
		if (neg && i > 0)
			res[--i] = '-';
	}
	size = 20 - i;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	for (n = 0; n < size; n++)
		str[n] = res[i + n];
	str[size] = '\0';
	return (str);
}

/**
 * convert_long_to_str - A function that converts long integer
 * to its string representation.
 * @num: The given long integer to convert
 *
 * Return: The converted string representation of the integer.
 */
char *convert_long_to_str(long num)
{
	unsigned long num_abs;
	int neg = num < 0 ? 1 : 0;

	if (neg)
		num_abs = (unsigned long) (-(num + 1)) + 1;
	else
		num_abs = (unsigned long)num;

	return convert_u_long_to_str(num_abs, neg);
}
