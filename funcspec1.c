#include "main.h"

/*** PRINT UNSIGNED INT ***/

/**
 * print_unsigned - A function that prints unsigned integer
 * @types: Argument variable list
 * @buf: Buffer array that handles print
 * @flgs: The flags identifier
 * @wdt: The width identifier
 * @prec: The precision identifier
 * @siz: The size identifier
 *
 * Return: The number of unsigned characters
 */
int print_unsigned(va_list types, char buf[], int flgs, int wdt,
		int prec, int siz)
{
	int c = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgned(num, siz)

	if (num == 0)
		buf[c--] = '0';

	buf[BUFF_SIZE - 1] = '\0
		';
	while (num > 0)
	{
		buf[c--] = (num % 10) + '0';
		num /= 10;
	}
	c++;

	return (write_unsgned(0, c, buf, flgs, wdt, prec, siz));
}

/*** PRINT UNSIGNED OCTADECIMAL NUMBER ***/
/**
 * print_octal - A function that prints unsigned octdecimal number
 * @types: The variable argument list
 * @buf: The buffer array to handle the print
 * @flgs: The flags identifier
 * @wdt: The width specifier
 * @prec: The precision identifier
 * @siz: The size specifier
 *
 * Return: The number of characters printed
 */
int print_octal(va_list types, char buf[], int flgs, int wdt,
		int prec, int siz)
{
	int c = BUFF_SIZE - 2;
	unsigned long int n = va_arg(types, unsigned long int);
	unsigned long int init = n;

	UNUSED(wdt);

	n = convert_size_unsgned(n, siz);

	if (n == 0)
		buf[c--] = '0';
	buf[BUFF_SIZE - 1] = '\0';
	while (n > 0)
	{
		buf[c--] = (n % 8) + '0';
		n /= 8;
	}
	if (flgs & F_HASH && init != 0)
		buf[c--] = '0';
	c++;

	return (write_unsgned(0, c, buf, flgs, wdt, prec, siz));
}
/*** PRINT LOWER OR UPPER HEXADECIMAL NUMBER ***/
/**
 * print_hex - A function that prints hexadecimal number in lower or
 *		upper letters.
 * @types: The variables argument list
 * @buf: The buffer array that handles the print function
 * @flgs: The flags identifier.
 * @flg_ch: The identifier for the flag characters.
 * @map: Map the buf to the value
 * @wdt: The Identifier for the width.
 * @prec: The precision identifier.
 * @siz: The identifier of the size.
 *
 * Return: The number of characters printed.
 */
int print_hex(val_list types, char map[], char buf[], int flgs,
		char flg_ch, int wdt, int prec, int siz)
{
	int c = BUFF_SIZE - 2;
	unsigned long int n = va_arg(types, unsigned long int);
	unsigned long int init = n;

	UNUSED(wdt);

	n = convert_size_unsgned(n, siz);
	if (n == 0)
		buf[c--] = '0';
	buf[BUFF_SIZE - 1] = '\0';
	while (n > 0)
	{
		buf[c--] = map[n % 16];
		n /= 16;
	}

	if (flgs & F_HASH && init_n != 0)
	{
		buf[c--] = flg_ch;
		buf[c--] = '0';
	}
	c++;

	return (write_unsgned(0, c, buf, flgs, wdt, prec, siz));
}

/*** PRINT UNSIGNED HEXADECIMAL NUMBER ***/
/**
 * print_hexadecimal - A function that prints hexadecimal numbers
 * @types: The variables argument list
 * @buf: The buffer array that handles the print function
 * @flgs: The identifier of active flags
 * @wdt: The width identifier
 * @prec: The precision identifier
 * @siz: The size identifier
 *
 * Return: The number of characters printed.
 */
int print_hexadecimal(va_list types, char buf[], int flgs, int wdt,
		int prec, int siz)
{
	return (print_hex(types, "0123456789abcdef", buf, flgs, 'x',
		wdt, prec, siz));
}

/*** PRINT UNSIGNED UPPER HEXADECIMAL NUMBER ***/
/**
 * print_upper_hex - A function that prints unsigned hexadecimal number.
 * @types: The variable argument list.
 * @buf: Buffer array that handle the print.
 * @flgs: The flags identifier.
 * @wdt: The width identifier.
 * @prec: The precision identifier
 * @siz: The identifier for the size of the arguments
 *
 * Return: The number of characters printed
 */
int print_upper_hex(va_list types, char buf[], int flgs, int wdt, prec, siz)
{
	return (print_hex(types, "0123456789ABCDEF", buf, flgs, 'X',
		wdt, prec, siz));
}
