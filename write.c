#include "main.h"

/**** HANDLE WRITE FUNCTIONS ****/
/**
 * handle_write_char - Function that prints a string
 * @ch: The character type
 * @buf: Buffer array that handle print
 * @flgs: The flags identifier
 * @wdt: The width specifier
 * @prec: The precision specifier
 * @siz: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char ch, char buf[], int flgs, int wdt,
		int prec, int siz)
{
	/* characters are stotred at the left while padding is at the right */
	int n = 0;
	char padd = ' ';

	UNUSED(prec);
	UNUSED(siz);

	if (flgs & F_ZERO)
		padd = '0';

	buf[n++] = ch;
	buf[n] = '\0';

	if (wdt > 1)
	{
		buf[BUFF_SIZE - 1] = '\0';
		for (n = 0; n < wdt - 1; n++)
			buf[BUFF_SIZE - n - 2] = padd;

		if (flgs & F_MINUS)
			return (write(1, &buf[0], 1) +
					write(1, &buf[BUFF_SIZE - n - 1], wdt - 1));
		else
			return (write(1, &buf[BUFF_SIZE - n - 1], wdt - 1) +
					write(1, &buf[0], 1));
	}
	return (write(1, &buf[0], 1));
}

/**** WRITE NUMBER ****/
/**
 * write_numb - Function that print a string
 * @neg: list of arguments
 * @idx: index to the character
 * @flgs: flags identifier
 * @wdt: width specifier
 * @buf: buffer identifier
 * @prec: the precision specifier
 * @siz: size specifier
 *
 ** Return: Number of characters printed.
 */
int write_numb(int neg, int idx, char buf[], int flgs,
		int wdt, int prec, int siz)
{
	int len = BUFF_SIZE - idx - 1;
	char padd = ' ', xtra_ch = 0;

	UNUSED(siz);

	if ((flgs & F_ZERO) && !(flgs & F_MINUS))
		padd = '0';
	if (neg)
		xtra_ch = '-';
	else if (flgs & F_PLUS)
		xtra_ch = '+';
	else if (flgs & F_SPACE)
		xtra_ch = ' ';

	return (write_num(idx, buf, flgs, wdt, prec, len, padd, xtra_ch));
}

/**
 * write_num - Function that write a number using a buffer
 * @idx: Index at which the number starts on the buffer
 * @buf: The buffer
 * @flgs: The flag identifier
 * @wdt: The width specifier
 * @prec: The precision specifier
 * @len: The length specifier
 * @padd: The padding specifier
 * @xtra_ch: The extra character to include
 *
 * Return: The number of printed characters.
 */
int write_num(int idx, char buf[], int flgs, int wdt, int prec, int len,
		char padd, char xtra_ch)
{
	int n, padd_start = 1;

	if (prec == 0 && idx == BUFF_SIZE - 2 && buf[idx] == '0' && wdt == 0)
		return (0); /* printf(".0d", 0) no char is printed */
	if (prec == 0 && idx == BUFF_SIZE - 2 && buf[idx] == '0')
		buf[idx] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < len)
		padd = ' ';
	while (prec > len)
		buf[--idx] = '0', len++;
	if (xtra_ch != 0)
		len++;
	if (wdt > len)
	{
		for (n = 1; n < wdt - len + 1; n++)
			buf[n] = padd;
		buf[n] = '\0';
		if (flgs & F_MINUS && padd == ' ') /* Assign extra char to left of buf */
		{
			if (xtra_ch)
				buf[--idx] = xtra_ch;
			return (write(1, &buf[idx], len) + write(1, &buf[1], n - 1));
		}
		else if (!(flgs & F_MINUS) && padd == ' ') /* extra char to left of buff */
		{
			if (xtra_ch)
				buf[--padd_start] = xtra_ch;
			return (write(1, &buf[padd_start], n - padd_start) +
				write(1, &buf[idx], len - (1 - padd_start)));
		}
	}
	if (xtra_ch)
		buf[--idx] = xtra_ch;
	return (write(1, &buf[idx], len));
}

/**
 * write_unsigned - Function that writes unsigned number
 * @neg: Number indicating if the sum is neg
 * @idx: Index at which the number starts in the buffer
 * @buf: Array of chars
 * @flgs: The flags identifier
 * @wdt: The wdt specifier
 * @prec: The precision specifier
 * @siz: The size specifier
 *
 * Return: Number of written characters
 */
int write_unsgned(int neg, int idx, char buf[], int flgs,
		int wdt, int prec, int siz)
{
	/* The number is stored at the tight of the buffer and starts at position i */
	int len = BUFF_SIZE - idx - 1, i = 0;
	char padd = ' ';

	UNUSED(neg);
	UNUSED(siz);

	if (prec == 0 && idx == BUFF_SIZE - 2 && buf[idx] == '0')
		return (0); /* printf(".0d", 0) no character is printed */

	if (prec > 0 && prec < len)
		padd = ' ';

	while (prec > len)
	{
		buf[--idx] = '0';
		len++;
	}
	if ((flgs & F_ZERO) && !(flgs & F_MINUS))
		padd = '0';

	if (wdt > len)
	{
		for (i = 0; i < wdt - len; i++)
			buf[i] = padd;
		buf[i] = '\0';

		if (flgs & F_MINUS) /* Assign xtra char to left of buf [buf>padd] */
			return (write(1, &buf[idx], len) + write(1, &buf[0], i));
		else
			return (write(1, &buf[0], i) + write(1, &buf[idx], len));
		/* Assign xtra char to left of padding [padd>buf] */
	}
	return (write(1, &buf[idx], len));
}

/**
 * prnt_pointer - Write a memory address
 * @buf: Array of chars
 * @idx: Index at which the number starts in the buffer
 * @len: Length of the parameter
 * @wdt: Width specifier
 * @flgs: The flags identifier
 * @padd: Char that represent the extra char
 * @xtra_ch: Char that represent extra  character
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int prnt_pointer(char buf[], int idx, int len, int wdt, int flgs,
		 char padd, char xtra_ch, int padd_start)
{
	int n;

	if (wdt > len)
	{
		for (n = 3; n < wdt - len + 3; n++)
			buf[n] = padd;
		buf[n] = '\0';
		if (flgs & F_MINUS && padd == ' ')
		{
			buf[--idx] = 'x';
			buf[--idx] = '0';
			if (xtra_ch)
				buf[--idx] = xtra_ch;
			return (write(1, &buf[idx], len) + write(1, &buf[3], n - 3));
		}
		else if (!(flgs & F_MINUS) && padd == ' ')
		{
			buf[--idx] = 'x';
			buf[--idx] = '0';
			if (xtra_ch)
				buf[--idx] = xtra_ch;
			return (write(1, &buf[3], n - 3) + write(1, &buf[idx], len));
		}
		else if (!(flgs & F_MINUS) && padd == '0')
		{
			if (xtra_ch)
				buf[--padd_start] = xtra_ch;
			buf[1] = '0';
			buf[2] = 'x';
			return (write(1, &buf[padd_start], n - padd_start) +
				write(1, &buf[idx], len - (1 - padd_start) - 2));
		}
	}
	buf[--idx] = 'x';
	buf[--idx] = '0';
	if (xtra_ch)
		buf[--idx] = xtra_ch;
	return (write(1, &buf[idx], BUFF_SIZE - idx - 1));
}
