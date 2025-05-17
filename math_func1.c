#include "main.h"
/**
 * divide_by_10exp_n - A function that divides a number by 10 exp n.
 * @num: The number to divide
 * @n: The power of 10
 * @free_num: A flag that specifies if a number can be freed
 *
 * Return: The quotient of the division by the power of 10.
 */
char *divide_by_10exp_n(char *num, unsigned short n, bool free_num)
{
	int len, dotpos, dest, src, n_pos, lead_zeros, size;
	char *res;

	if (n == 0)
		return (num);
	len = str_len(num), dotpos = index_of_char(num, '.');
	n_pos = (dotpos < 0) ? (len - n) : (dotpos - n);
	lead_zeros = (n_pos < 0) ? -n_pos : 0;
	size = len + (n_pos < 0 ? (lead_zeros + (dotpos < 0 ? 1 : 0)) :
			(n_pos == 0 ? (dotpos < 0 ? 2 : 0) : (dotpos < 0 ? 1 : 0)));
	src = len - 1, dest = size - 1;
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	if (n_pos <= 0)
	{
		res[0] = '0';
		res[1] = '.';
		mem_set(res + 2, '0', lead_zeros);
		while (src >= 0 && dest >= lead_zeros + 2)
		{
			if (num[src] == '.')
				src--;
			res[dest--] = num[src--];
		}
	}
	else
		while (src >= 0 && dest >= 0)
		{
			if (dest == n_pos)
				res[dest--] = '.';
			if (num[src] == '.')
				src--;
			res[dest--] = num[src--];
		}
	res[size] = '\0';
	if (free_num)
		free(num);
	return (res);
}

/**
 * compute_npower_of_two - Function that compute 2 raise to a given power
 * @n: The given exponential of 2
 *
 * Return: The value of 2 to power of n.
 */
char *compute_npower_of_two(short n)
{
	char *res, *base, *mem;
	short count;

	res = malloc(sizeof(char) * 2);
	if (!res)
		return (NULL);
	res[0] = '1';
	res[1] = '\0';
	if (n > 0)
	{
		for (count = 0; count < n; count++)
		{
			base = malloc(sizeof(char) * 2);
			if (!base)
			{
				free(res);
				return (NULL);
			}
			base[0] = '2';
			base[1] = '\0';
			mem = multiply_int(base, res, TRUE);
		}
		free(res);
		res = mem;
	}
	else if (n < 0)
	{
		base = compute_npower_of_five(-1 * n);
		mem = divide_by_10exp_n(base, -1 * n, TRUE);
		free(base);
		free(res);
		res = mem;
	}
	return (res);
}


/**
 * compute_npower_of_five - A function that compute 5 raise to power of n
 * @n: The given exponential of 5
 *
 * Return: The value of 5 to power of n.
 */
char *compute_npower_of_five(unsigned short n)
{
	char *res, *base, *tmp;
	unsigned short count;

	res = malloc(sizeof(char) * 2);
	if (!res)
		return (NULL);
	res[0] = '1';
	res[1] = '\0';
	if (n == 0)
		return (res);
	for (count = 0; count < n; count++)
	{
		base = malloc(sizeof(char) * 2);
		if (!base)
		{
			free(res);
			return (NULL);
		}
		base[0] = '5';
		base[1] = '\0';
		tmp = multiply_int(base, res, TRUE);
		if (!tmp)
		{
			free(res);
			free(base);
			return (NULL);
		}
		free(res);
		res = tmp;
		free(base);
	}
	return (res);
}

/**
 * pos_num_powerof_two -  Function that compute 2 raise to power of +ve no.
 * @n: The given positive number
 *
 * Return: The value of 2 raise to power of positive number.
 */
unsigned int pos_num_powerof_two(unsigned int n)
{
	return (1U << n);
}

/**
 * unsigned_long_to_hex - A function that converts an unsigned long integer
 * to its string representation.
 * @num: The given unsigned long integer
 * @upper: A flag that signifies that the hexadecimal should be in uppercase.
 *
 * Return: The string representation of the converted unsigned long integer
 */
char *unsigned_long_to_hex(unsigned long num, char upper)
{
	int count = 0;
	char *str;
	char size = sizeof(unsigned long) * 2 + 1;
	unsigned long mem = num;

	str = malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	mem_set(str, 0, size);
	if (num == 0)
	{
		str[count++] = '0';
		str[count] = '\0';
		return (str);
	}

	for (count = 0; count < size - 1 && mem > 0; count++)
	{
		str[count] = (mem % 16) < 10 ? (mem % 16) + '0' :
			((mem % 16) - 10 + (upper ? 'A' : 'a'));
		mem /= 16;
	}
	rev_string(str);
	str = trim_start(str, '0', TRUE);
	return (str);
}
