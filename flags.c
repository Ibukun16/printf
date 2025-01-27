#include "main.h"

/**
 * get_flags - Calculate active flags
 * @fmt: Formatted string in which to print the arguments
 * @f: The format parameter
 * Return: flags
 */
int get_flags(const char *fmt, int *f)
{
	/* - + 0 # '' */
	/* 1 2 4 8 16 */
	int i, f_cur, flags = 0;
	const char ch_flgs[] = {'-', '+', '0', '#', ' ', '\0'};
	const int arr_flgs[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (f_cur = *f + 1; fmt[f_cur] != '\0'; f_cur++)
	{
		for (i = 0; ch_flgs[i] != '\0'; i++)
		{
			if (fmt[f_cur] == ch_flgs[i])
			{
				flags |= arr_flgs[i];
				break;
			}
		}
		if (ch_flgs[i] == '\0')
			break;
	}
	*f = f_cur - 1;
	return (flags);
}
