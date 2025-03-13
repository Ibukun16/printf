#include "main.h"

/*** PRINT CHAR ***/

/**
 * print_char - A function that prints char
 * @types: type of the arguments
 * @buf: Buffer to handle print
 * @flgs: Determine the active flags
 * @wdt: The width of the of the buf
 * @prec: The precision in specification
 * @siz: Size of the array
 *
 * Return: The number of individual characters printed.
 */
int print_char(va_list types, char buf[], int flgs, int wdt, int prec, int siz)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buf, flgs, wdt, prec, siz));
}


/*** PRINT A STRING ***/

/**
 * print_string - A function that prints string
 * @types: type of the arguments
 * @buf: Buffer to handle print
 * @flgs: Determine the active flags
 * @wdt: The width of the of the buf
 * @prec: The precision in specification
 * @siz: Size of the array
 *
 * Return: The number of charcarters from the string printed.
 */
int print_string(va_list types, char buf[], int flgs, int wdt,
		 int prec, int siz)
{
	int l = 0, n;
	char *st = va_arg(types, char *);

	UNUSED(buf);
	UNUSED(flgs);
	UNUSED(wdt);
	UNUSED(prec);
	UNUSED(siz);
	if (!st)
	{
		st = "(null)";
		if (prec >= 6)
			st = "      ";
	}
	while (st[l] != '\0')
		l++;
	if (prec >= 0 && prec < l)
		l = prec;
	if (wdt > l)
	{
		if (flgs & F_MINUS)
		{
			write(1, &st[0], l);
			for (n = wdt - l; n > 0; n--)
				write(1, " ", 1);
			return (wdt);
		}
		else
		{
			for (n = wdt - l; n > 0; n--)
				write(1, " ", 1);
			write(1, &st[0], l);
			return (wdt);
		}
	}
	return (write(1, st, l));
}

/*** PRINT PERCENT SIGN (MODULUS) ***/

/**
 * print_percent - A function that prints modulus sign
 * @types: The argument variable list
 * @buf: Buffer to handle print
 * @flgs: Determine the active flags
 * @wdt: The width of the of the buf
 * @prec: The precision in specification
 * @siz: Size of the array
 *
 * Return: The number of charcarters from the string printed.
 */
int print_percent(va_list types, char buf[], int flgs, int wdt,
		int prec, int siz)
{
	UNUSED(types);
	UNUSED(buf);
	UNUSED(flgs);
	UNUSED(wdt);
	UNUSED(siz);
	UNUSED(prec);
	return (write(1, "%%", 1));
}

/*** PRINT INT ***/

/**
 * print_int - A function that prints integer
 * @types: type of the arguments
 * @buf: Buffer to handle print
 * @flgs: Determine the active flags
 * @wdt: The width of the of the buf
 * @prec: The precision in specification
 * @siz: Size of the array
 *
 * Return: The number of characters from the string printed.
 */
int print_int(va_list types, char buf[], int flgs, int wdt, int prec, int siz)
{
	int n = BUFF_SIZE - 2;
	int neg = 0;
	long int list = va_arg(types, long int);
	unsigned long int num;

	list = convert_size_num(list, siz);

	if (list == 0)
		buf[n--] = '0';

	buf[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)list;

	if (list < 0)
	{
		num =  (unsigned long int)(-list);
		neg = 1;
	}

	while (num > 0)
	{
		buf[n--] = (num % 10) + '0';
		num /= 10;
	}

	n++;
	return (write_numb(neg, n, buf, flgs, wdt, prec, siz));
}


/*** PRINT BINARY ***/

/**
 * print_binary - A function that prints an unsigned integer
 * @types: type of the arguments
 * @buf: Buffer to handle print
 * @flgs: Determine the active flags
 * @wdt: The width of the of the buf
 * @prec: The precision in specification
 * @siz: Size of the array
 *
 * Return: The number of charcarters from the string printed.
 */
int print_binary(va_list types, char buf[], int flgs, int wdt,
		int prec, int siz)
{
	unsigned int n, m, e, sum;
	unsigned int a[32];
	int c;

	UNUSED(buf);
	UNUSED(flgs);
	UNUSED(wdt);
	UNUSED(prec);
	UNUSED(siz);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (e = 1; e < 32; e++)
	{
		m /= 2;
		a[e] = (n / m) % 2;
	}
	for (e  = 0, sum = 0, c = 0; e < 32; e++)
	{
		sum += a[e];
		if (sum || e == 31)
		{
			char s = '0' + a[e];

			write(1, &s, 1);
			c++;
		}

	}
	return (c);
}
