#include "main.h"

/**
 * is_printable - Function that determines a printable char
 * @ch: The character to evaluate.
 *
 * Return: 1 if ch is printable and 0 for otherwise
 */
int is_printable(char ch)
{
	return (ch >= 32 && ch <= 126);
}

/**
 * append_hex_code - Function that add ascii code in hexadecimal to buffer
 * @buf: Array of chars.
 * @n: Index to the position to append
 * @ascii: ASCII CODE
 *
 * Return: Always 3
 */
int append_hex_code(char ascii, char buf[], int n)
{
	char map[] = "0123456789ABCDEF";
	/* Note that ascii format code is always 2 digits long */

	unsigned char value = (unsigned char)ascii;

	buf[n++] = '\\';
	buf[n++] = 'x';

	buf[n++] = map[value / 16];
	buf[n] = map[value % 16];

	return (n);
}

/**
 * is_digit - Function that determines if a char is a digit
 * @ch: The character to evaluate.
 *
 * Return: 1 if ch is a digit else 0
 */
int is_digit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

/**
 * convert_size_num - Function that cast a number to the specified size
 * @num: The number to cast
 * @size: The value that indicate the cast type.
 *
 * Return: The cast value
 */
long int convert_size_num(long int num, int size)
{
	if (size == S_LONG)
		return (num);

	if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsigned - A function that cast a number to the specified size
 * @num: The number to cast
 * @size: The number indicating the cast type
 *
 * Return: the cast value
 */
long int convert_size_unsgned(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);

	if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
