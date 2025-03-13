#include "main.h"

/**
 * get_width - Function that calculate the width for printing
 * @fmt: The string format in which to print the arguments.
 * @list: The argument list variable
 * @ag: The argument list.
 *
 * Return: width.
 */
int get_width(const char *fmt, int *list, va_list varg)
{
	int cur;
	int wdt = 0;

	for (cur = *list + 1; fmt[cur] != '\0'; cur++)
	{
		if (is_digit(fmt[cur]))
		{
			wdt *= 10;
			wdt += fmt[cur] - '0';
		}
		else if (fmt[cur] == '*')
		{
			cur++;
			wdt = va_arg(varg, int);
			break;
		}
		else
			break;
	}
	*list = cur - 1;
	return (wdt);
}
