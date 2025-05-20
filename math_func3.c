#include "main.h"
/**
 * round_float_to_int - A function that round-up a decimal num to whole num
 * @num: The given number to round up
 * @free_mem: A flag that indicates if the memory containing the given num
 * should be freed.
 *
 * Return: The rounded integer, else NULL.
 */
char *round_float_to_int(char *num, bool free_mem)
{
	int decpos = index_of_char(num, '.'), len = str_len(num);
	int declen = len - (decpos + 1), decp_len;
	char *res = NULL, *dec_part = NULL, *int_part = NULL, *round = NULL;

	if (!num)
		return (NULL);
	if (decpos == -1)
	{
		res = strn_copy(res, num, 0);
		if (free_mem)
			free(num);
		return (res);
	}
	dec_part = strn_copy(dec_part, num + decpos + 1, 0);
	round = round_up(dec_part, 0, TRUE);
	decp_len = str_len(round);
	if (round[0] > '5' || (round[0] == '1' && decp_len > declen))
	{
		int_part = strn_copy(int_part, num, decpos);
		res = add_positive_nums(int_part, "1", TRUE);
	}
	free(round);
	if (free_mem)
		free(num);
	return (res);
}

/**
 * round_float - A function that round up a decimal number base on a given
 * precision.
 * @num: The number to round.
 * @prec: The given precision to round number.
 * @free_mem: A flag that indicates free memory
 *
 * Return: The rounded float, else NULL.
 */
char *round_float(char *num, unsigned int prec)
{
	unsigned int decpos = index_of_char(num, '.'), len = str_len(num), decp_len;
	unsigned int declen = len - (decpos + 1), size = decpos + prec + 1, i, j;
	char *res = NULL, *dec_part = NULL, *int_part = NULL, *round = NULL;

	if (prec == 0)
		return (round_float_to_int(num, TRUE));
	if (prec == declen)
		return (strn_copy(res, num, len));
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	if (declen < prec)
	{
		for (i = 0; i < size; i++)
			res[i] = num[i];
		mem_set(res + len, '0', prec - declen);
		res[size] = '\0';
	}
	else if (declen > prec)
	{
		dec_part = strn_copy(dec_part, num + decpos + 1, declen);
		round = round_up(dec_part, prec, TRUE);
		decp_len = str_len(round);
		int_part = strn_copy(int_part, num, decpos);
		if (decp_len > declen && round[0] == '1')
		{
			free(res);
			res = add_positive_nums(int_part, "1", TRUE);
		}
		else if (decp_len <= declen)
		{
			for (i = 0; i <= decpos; i++)
				res[i] = num[i];
			for (j = 0; j < prec; j++)
				res[i + j] = round[j];
			res[i + j] = '\0';
		}
	}
	free(round);
	return (res);
}

/**
 * strn_copy - A function that copies content of a buffer to another)
 * @dest: The destination to store the copied string.
 * @src: The storage location to copy the string from.
 * @n: The number of characters to copy from the source to destination
 *
 * Return: The copied string, else NULL.
 */
char *strn_copy(char *dest, char *src, int n)
{
	int count, len;

	if (!src)
		return (NULL);
	len = str_len(src);
	if (n <= 0 || n > len)
		n = len;
	if (!dest)
	{
		dest = malloc(sizeof(char) * (n + 1));
		if (!dest)
			return (NULL);
	}
	for (count = 0; count < n && src[count] != '\0'; count++)
		dest[count] = src[count];
	dest[count] = '\0';

	return (dest);
}

/**
 * round_up - Function that round up a string of values.
 * @num: The given number.
 * @prec: The precision of the reound up.
 * @free_mem: A flag that indicate if memory should be freed.
 *
 * Return: The rounded figure of the decimal value else NULL.
 */
char *round_up(char *num, unsigned int prec, bool free_mem)
{
	unsigned int len = str_len(num), i, limit = prec ? prec : 0, carry = 0;
	char *mem = NULL;
	int n;

	mem = malloc(sizeof(char) * (len + 2));
	strn_copy(mem + 1, num, len + 1), mem[0] = '0';
	for (i = len; i > limit; --i)
	{
		if (mem[i] > '5' || (mem[i] == '5' &&  (mem[i - 1] - '0') % 2))
		{
			if (mem[i - 1] < '9')
			{
				mem[i - 1]++;
				carry = 0;
			}
			else
			{
				mem[i - 1] = '0';
				carry = 1;
			}
		}
		mem[i] = '0';
	}
	if (carry == 1)
	{
		for (n = (int)limit - 1; n >= 0; n--)
		{
			if (mem[i] < '9')
			{
				mem[i]++;
				carry = 0;
				break;
			}
			mem[n] = '0';
		}
	}
	trim_start(mem, '0', TRUE);
	if (free_mem)
		free(num);
	return (mem);
}
