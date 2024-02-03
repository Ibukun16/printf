#include "main.h"
/**
 * hex_prnt - A function that prints hexadecimal
 * @n: The number to print
 * @s: The specifier before the number.
 *
 * Return: The number of characters printed
 */
int hex_prnt(unsigned int n, char s)
{
	int c = 0;
	unsigned int i = n % 16;

	if (n / 16 > 0)
		c += hex_prnt(n / 16, c);
	if (i > 9)
	{
		if (s == 'x')
			c += _putchar((i - 10) + 'a');
		else
			c += _putchar((i - 10) + 'A');
	}
	else
		c += _putchar((n % 16) + '0');
	return (c);
}

/**
 * reverse - A function that prints string in reverse
 * @s: The string to print
 *
 * Return: The number of characters printed
 */
int reverse(char *s)
{
	int l = 0, c = 0;

	while (s[l])
		l++;
	for (; l >= 1; l--)
		c += _putchar(s[l - 1]);

	return (c);
}

/**
 * rot13 - A function that encode a string using rot13
 * @s: The string to be encoded
 *
 * Return: The encoded string
 */
int rot13(char *s)
{
	int i = 0, c = 0;

	while (s[i])
	{
		while (
				(s[i] >= 'a' && s[i] <= 'z') ||
				(s[i] >= 'A' && s[i] <= 'Z')
		      )
		{
			if (
					(s[i] >= 'n' && s[i] <= 'z') ||
					(s[i] >= 'N' && s[i] <= 'Z')
			   )
				c += _putchar(s[i] - 13);
			else
				c += _putchar(s[i] + 13);
			i++;
		}
		if (s[i])
		{
			c += _putchar(s[i]);
			i++;
		}
	}
	return (c);
}
