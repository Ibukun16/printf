#include "main.h"

/**
 * get_size - Function that calculate the size of the argument
 * @fmt: Formatted string in which to print the argument
 * @list: List of argument to be printed
 *
 * Return: size.
 */
int get_size(const char *fmt, int *list)
{
	int cur = *list + 1;
	int size = 0;

	if (fmt[cur] == 'l')
		size = S_LONG;
	else if (fmt[cur] == 's')
		size = S_SHORT;

	if (size == 0)
		*list = cur - 1;
	else
		*list = cur;

	return (size);
}
