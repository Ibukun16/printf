#include "main.h"

/**
 * convert_to_hexadecimal - A function that convertys a decimal number
 * that is less than 16 to hexadecimal form.
 * @c: The decimal number
 *
 * Return: The hexadecimal digit of the number, else NULL.
 */
char convert_to_hexadecimal(char c)
{
	if (c >= 0 && c <= 15)
		return ((c < 10) ? ('0' + c) : ('a' + (c - 10)));
	return ('\0');
}

/**
 * compare_numbers - A function that comapres 2 numbers.
 * @n1: The first number to compare
 * @n2: The second number to compare
 *
 * Return: 1 if n1 is greater than n2, -1 if n2 is greater than n1, else 0.
 */
char compare_numbers(char *n1, char *n2)
{
	int len1, len2;

	if (n1 == NULL || n2 == NULL)
		return (0);
	while (*n1 == '0' && *(n1 + 1) != '\0')
		n1++;

	while (*n2 == '0' && *(n2 + 1) != '\0')
		n2++;

	len1 = str_len(n1);
	len2 = str_len(n2);

	if (len1 != len2)
		return (len1 > len2 ? 1 : -1);

	while (*n1 && *n2)
	{
		if  (*n1 != *n2)
			return (*n1 > *n2 ? 1 : -1);
		n1++;
		n2++;
	}
	return (0);
}

/**
 * convert_str_to_int - A function that converts string to integer
 * @num: The number to convert
 *
 * Return: The converted number in decimal.
 */
int convert_str_to_int(char *num)
{
	int count, len, exp = 1, result = 0;
	int neg = 0;

	len = str_len(num);
	if (num[0] == '-')
	{
		neg = 1;
		num++;
		len--;
	}

	for (count = len - 1; count >= 0; count--)
	{
		if (is_digit(num[count]))
		{
			result += (num[count] - '0') * exp;
			exp *= 10;
		}
		else
			return (0);
	}
	if (neg)
		result *= -1;
	return (result);
}

/**
 * convert_bin_to_int - A function that convert a binary string to an integer
 * @arr: The binary array
 *
 * Return: The coverted binary arry in decimal
 */
int convert_bin_to_int(char *arr)
{
	int count, result = 0;

	for (count = 0; arr[count] != '\0'; count++)
	{
		if (arr[count] == '0' || arr[count] == '1')
			result = result * 2 + (arr[count] - '0');
		else
			return (-1);
	}
	return (result);
}

/**
 * convert_long_to_oct - A function that converts a long integer to its
 * octahedral value
 * @num: The number to convert to octahedral
 *
 * Return: The converted number else NULL.
 */
char *convert_long_to_oct(unsigned long num)
{
	int count, size = 0;
	unsigned long tmp = num;
	char *str;

	if (num == 0)
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}

	while (tmp > 0)
	{
		tmp /= 8;
		size++;
	}
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	for (count = size - 1; count >= 0; count--)
	{
		str[count] = (num % 8) + '0';
		num /= 8;
	}
	return (str);
}
