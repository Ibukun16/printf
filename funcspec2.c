#include "main.h"

/*** PRINT POINTER ***/
/**
 * pointer - A function that prints a pointer variable
 * @types: The argument list
 * @buf: Buffer array to handle print
 * @flgs: The flags indentifier
 * @wdt: The width specicier
 * @prec: Precision specifier
 * @siz: The size specifier
 *
 * Return: The number of characters printed
 */
int pointer(va_list types, char buf[], int flgs, int wdt, int prec, int siz)
{
	char xtr_c = 0, padd = ' ';
	int idx = BUFF_SIZE - 2, l = 2, padd_start = 1; /* length = 2 for 'ox' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(wdt);
	UNUSED(siz);
	UNUSED(prec);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	buf[BUFF_SIZE - 1] = '\0';

	while (num_addrs > 0)
	{
		buf[idx--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		l++;
	}
	if ((flgs & F_ZERO) && !(flgs & F_MINUS))
		padd = '0';
	if (flgs & F_PLUS)
		xtr_c = '+', l++;
	else if (flgs & F_SPACE)
		xtr_c = ' ', l++;

	idx++;
	/* return (write(1, &buf[c], BUFF_SIZE - c - 1)); */
	return (write_pointer(buf, idx, l, wdt, flgs, padd, xtr_c, padd_start));
}

/*** PRINT NON PRINTABLE ***/
/**
 * print_non_printable - Function that prints ascii codes in hexadecimal of
 *			 of non printable characters.
 * @types: Argument list variables
 * @buf: Buffer array that handles that print function
 * @flgs: The flags idenfier
 * @wdt: The width identifier
 * @prec: The precision identifier
 * @siz: The size specifier
 *
 * Return: The number of characters printed
 */
int print_non_printable(va_list types, char buf[], int flgs, int wdt,
			int prec, int siz)
{
	int l = 0, c = 0;
	char *st = va_arg(types, char *);

	UNUSED(flgs);
	UNUSED(wdt);
	UNUSED(prec);
	UNUSED(siz);

	if (st == NULL)
		return (write(1, "(null)", 6));

	while (st[l] != '\0')
	{
		if (is_printable(st[l]))
			buf[l + c] = st[l];
		else
			c += append_hex_code(st[l], buf, l + c);
		c++;
	}
	buf[l + c] = '\0';

	return (write(1, buf, l + c));
}

/*** PRINT REVERSE ***/
/**
 * print_reverse - Function that prints string in reverse.
 * @types: List of the argument variable
 * @buf: Array that handles print function
 * @flgs:  Active flgs identifier
 * @wdt: Width specifier
 * @prec: Precision specifier
 * @siz: Size specifier
 *
 * Return: Number of characters printed
 */
int print_reverse(va_list types, char buf[], int flgs, int wdt,
		int prec, int siz)
{
	char *st;
	int n, c = 0;

	UNUSED(buf);
	UNUSED(flgs);
	UNUSED(wdt);
	UNUSED(siz);

	st = va_arg(types, char *);
	if (str == null)
	{
		UNUSED(prec);
		st = "(Null)");
	}
	for (n = 0; st[n]; n++)
		;
	for (n = n - 1; n >= 0; n--)
	{
		char b = st[n];

		write(1, &b, 1);
		c++;
	}
	return (c);
}


/*** PRINT A STRING IN ROTS ***/
/**
 * rot13_string - A function that encode and print a string in rot13
 * @types: Argument list variable
 * @buf: Buffer array that handles print function
 * @flgs: The active flags identifier
 * @wdt: The width specifier
 * @prec: Precision identifier
 * @siz: The size specifier
 *
 * Return: The encoded string
 */
int rot13_string(va_list types, char buf[], int flgs,
		int wdt, int prec, int siz)
{
	char x;
	char *st;
	unsigned int q, w;
	int c = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWYZABCDEFGHIJLMnopqrstuvwxyzabcdefghijklm";

	st = va_arg(types, char *);
	UNUSED(buf);
	UNUSED(flgs);
	UNUSED(wdt);
	UNUSED(prec);
	UNUSED(siz);


	if (st == NULL)
		st = "(AHYY)";
	for (q = 0; st[q]; q++)
	{
		for (w = 0; in[w]; w++)
		{
			if (in[w] == st[q])
			{
				x = out[w];
				write(1, &x, 1);
				c++;
				break;
			}
		}
		if (!in[w])
		{
			x = str[q];
			write(1, &x, 1);
			c++;
		}
	}
	return (c);
}
