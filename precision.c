#include "main.h"

/**
 * get_precision - A function that calculates the specified precision
 * @fmt: string format in which to print the arguments
 * @list: List of arguments to be printed
 * @ag: The arguments
 *
 * Return: Precision
 */
int get_precision(const char *fmt, int *ag, va_list list)
{
	int ag_cur = *ag + 1;
	int prec = -1;


	if (fmt[ag_cur] != '.')
		return (prec);

	prec = 0;
	for (ag_cur += 1; fmt[ag_cur] != '\0'; ag_cur++)
	{
		if (is_digit(fmt[ag_cur]))
		{
			prec *= 10;
			prec += fmt[ag_cur] - '0';
		}
		else if (fmt[ag_cur] == '*')
		{
			ag_cur++;
			prec = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*ag = ag_cur - 1;
	return (prec);
}
