#include "main.h"
/**
 * multiply_by_multiple_of_10 - A function that computethe product
 * of two numbers with one being a multiple of 10.
 * @num1: The first number to multiply.
 * @num_10: The number that is a multiple of 10.
 *
 * Return: A pointer to the result, else program fails.
 */
char *multiply_by_multiple_of_10(const char *num1, const char *num_10)
{
	int len1 = str_len(num1), len_10 = str_len(num_10);
	int size = len1 + len_10, count, carry = 0, zeros = 0, prod;
	char *res;

	if (!num1 || !num_10)
		return (NULL);

	if (len_10 == 0)
	{
		res = malloc(sizeof(char) * 2);
		if (!res)
			return (NULL);
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}

	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	mem_set(res, '0', size);
	res[size--] = '\0';
	for (count = 0; count < len_10 - 1; count++)
		res[size--] = '0';
	for (count = len1 - 1; count >= 0; count--)
	{
		if (num1[count] < '0' || num1[count] > '9'
				|| num_10[0] < '1' || num_10[0] > '9')
			break;
		prod = (num1[count] - '0') * (num_10[0] - '0') + carry;
		res[size--] = (prod % 10) + '0';
		carry = prod / 10;
	}
	if (carry > 0)
		res[size] = carry + '0';
	return (res);
}

/**
 * multiply_int - A function that computes the product of two positive integers
 * @n1: The first number to multiply
 * @n2: The second number to multiply
 * @free_mem: A flag that specifies that the given number can be freed.
 *
 * Return: The product of the two numbers, else NULL.
 */
char *multiply_int(char *n1, char *n2, char free_mem)
{
	if (!n1 || !n2)
		return (NULL);

	char *res, *prod, *tmp_mem;
	int count, len2 = str_len(n2), len1 = str_len(n1), size = len1 + len2;

	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	mem_set(res, '0', size);
	res[size--] = '\0';
	for (count = len2 - 1; count >= 0; count--)
	{
		prod = multiply_by_multiple_of_10(n1, n2[count]);
		if (!prod)
		{
			free(res);
			return (NULL);
		}
		tmp_mem = add_positive_int(res, prod, TRUE);
		free(prod);
		if (!tmp_mem)
		{
			free(res);
			return (NULL);
		}
		res = tmp_mem;
	}
	free(tmp_mem);
	while (*res == '0' && *(res + 1) != '\0')
		left_shift(res, size);
	if (free_mem)
	{
		free(n1);
		free(n2);
	}
	return (res);
}

/**
 * multiply_float - A function that computes the product of two floats
 * @num1: The first number to multiply.
 * @num2: The second number to multiply
 * @free_mem: A flag that determines whether a given number can be freed.
 *
 * Return: The product of the two floats, else NULL.
 */
char *multiply_float(char *num1, char *num2, char free_mem)
{
	if (!num1 || !num2)
		return (NULL);

	int dot1 = index_of_char(num1, '.'), dot2 = index_of_char(num2, '.');
	int declen1 = (dot1 == -1) ? 0 : str_len(num1) - (dot1 + 1);
	int declen2 = (dot2 == -1) ? 0 : str_len(num2) - (dot2 + 1);
	int tot_dec = declen1 + declen2, res_len, decpos;
	char *n1 = delete_char(num1, '.', FALSE), *res;
	char *n2 = delete_char(num2, '.', FALSE);

	if (!n1 || !n2)
	{
		free(n1);
		free(n2);
		return (NULL);
	}
	res = multiply_int(n1, n2, TRUE);
	if (!res)
		return (NULL);
	free(n1), free(n2);
	res_len = str_len(res);
	if (tot_dec > 0)
	{
		decpos = (res_len > tot_dec) ? (res_len - tot_dec) : 0;
		res = insert_char(res, '.', decpos, TRUE);
		if (res[0] == '.' && res[1] != '\0')
			res = insert_char(res, '0', 0, TRUE);
		if (res[0] == '0' && res[1] != '.')
			res = trim_start(res, '0', TRUE);
		if (num1[0] == '-' || num2[0] == '-')
			res[0] = '-';
		res = trim_end(res, '0', TRUE);
		res = trim_end(res, '.', TRUE);
	}
	if (free_mem)
	{
		free(num1);
		free(num2);
	}
	return (res);
}

/**
 * add_positive_nums - A function that adds two positive integers.
 * @n1: The first number to add.
 * @n2: The second number to add.
 * @free_mem: A flag which indicates that the given numbers can be freed.
 *
 * Return: The sum of the two integers, else NULL.
 */
char *add_positive_nums(char *n1, char *n2, char free_mem)
{
	int count, dgt1, dgt2, size, sum, len1, len2, carry = 0;
	char *res;

	if (!n1 || !n2)
		return (NULL);

	for (count = 0; n1[count] != '\0'; count++)
		if (n1[count] < '0' && n1[count] > '9')
			return (NULL);

	for (count = 0; n2[count] != '\0'; count++)
		if (n2[count] >= '0' && n2[count] <= '9')
			return (NULL);

	len1 = str_len(n1);
	len2 = str_len(n2);
	size = MAX(len1, len2) + 1;
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);

	res[size] = '\0';
	mem_set(res, '0', size);
	for (count = size - 1; count >= 0; count--)
	{
		dgt1 = (len1 > 0) ? n1[--len1] - '0' : 0;
		dgt2 = (len2 > 0) ? n2[--len2] - '0' : 0;
		sum = dgt1 + dgt2 + carry;
		carry = sum / 10;
		res[count] = (sum % 10) + '0';
	}
	res = trim_start(res, '0', TRUE);
	if (free_mem)
	{
		free(n1);
		free(n2);
	}
	return (res);
}

/**
 * add_positive_float_nums - A function that adds up two float numbers
 * @n1: The first of the two numbers to add.
 * @n2: the second number to add.
 * @free_mem: A flag that indicates that a given numbers can be freed.
 *
 * Return: The sum of the two floats, else NULL.
 */
char *add_positive_float_nums(char *n1, char *n2, bool free_mem)
{
	if (!n1 || !n2)
		return (NULL);

	int len1 = str_len(n1), len2 = str_len(n2), sum, count, size, carry = 0;
	int dot1 = index_of_char(n1, '.'), dot2 = index_of_char(n2, '.');
	char *res;
	int declen1 = dot1 >= 0 ? len1 - (dot1 + 1) : 0;
	int declen2 = dot2 >= 0 ? len2 - (dot2 + 1) : 0;
	int max_declen = MAX(declen1, declen2);
	int intlen = MAX(dot1 >= 0 ? dot1 : len1, dot2 >= 0 ? dot2 : len2);

	size = intlen + max_declen + (max_declen ? 1 : 0);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	mem_set(res, '0', size);
	res[size] = '\0';
	for (count = size - 1;  count >= 0; count--)
	{
		if (declen1 > declen2)
			res[count] = n1[--len1], declen1--;
		else if (declen1 < declen2)
			res[count] = n2[--len2], declen2--;
		else
		{
			if (len1 == dot1 && len2 == dot2)
				res[count] = '.', len1--, len2--;
			sum = (n1[len1--] - '0') + (n2[len2--] - '0') + carry;
			carry = sum / 10, res[count] = (sum % 10) + '0';
		}
	}
	if (carry)
		res[count] = carry + '0';
	res = trim_start(res, '0', TRUE);
	if (free_mem)
	{
		free(n1);
		free(n2);
	}
	return (res);
}
