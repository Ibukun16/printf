#include "main.h"

/**
 * prnt_stg - A function that prints a string
 * @varg: Argument variable list
 * @s: The specifier
 *
 * Return: The number of characters
 */
int prnt_stg(va_list varg, char s)
{
	int c = 0;
	char *f = va_arg(varg, char *);

	if (!f)
		f = "(null)";
	if (s == 's')
	{
		while (*f)
		{
			c += _putchar(*f);
			f++;
		}
	}
	else if (s == 'S')
		c += print_s(f);
	else if (s == 'r')
		c += reverse(f);
	else if (s == 'R')
		c += rot13(f);

	return (c);
}

/**
 * int_prnt - A function that prints integer
 * @arg: The variable argument list
 *
 * Return: The number of characters printed
 */
int int_prnt(va_list arg)
{
	int c = 0;
	int f1 = va_arg(arg, int);

	if (f1 < 0)
	{
		_putchar('-');
		c++;
		f1 *= -1;
	}

	c += num_prnt(f1, 10);
	return (c);
}

/**
 * bioc_unsg - A function that prints binary, octadecimal and unsigned integer
 * @arg: The variables argument list
 * @s: The specifier
 *
 * Return: The number of characters printed.
 */
int bioc_unsg(va_list arg, char s)
{
	int c = 0;
	unsigned int i = va_arg(arg, unsigned int);

	if (s == 'b')
		c += num_prnt(i, 2);
	else if (s == 'u')
		c += num_prnt(i, 10);
	else if (s == 'o')
		c += num_prnt(i, 8);
	else if (s == 'x' || s == 'X')
		c += hex_prnt(i, s);
	return (c);
}

/**
 * num_prnt - A function that prints a number
 * @num : The number to print
 * @bs: The base to print the number
 *
 * Return: The number of characters printed
 */
int num_prnt(unsigned int num, int bs)
{
	int b, c = 0;

	b = num / bs;
	if (b > 0)
		c += num_prnt(b, bs);
	c += _putchar((num % bs) + '0');
	return (c);
}

/**
 * print_s - A function that print string and non printable in haxadecimal.
 * @s: The string to be printed
 *
 * Return: The number of characters printed
 */
int print_s(char *s)
{
	int c = 0, asci;

	while (*s)
	{
		if (*s < 32 || *s >= 127)
		{
			c += _putchar('\\');
			c += _putchar('x');

			asci = (int)*s;
			c += _putchar((asci / 16) + '0');

			if (asci % 16 > 9)
				c += _putchar(((asci % 16) - 10) + 'A');
			else
				c += _putchar((asci % 16) + '0');
		}
		else
			c += _putchar(*s);
		s++;
	}
	return (c);
}
