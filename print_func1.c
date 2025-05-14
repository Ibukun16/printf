#include "main.h"

/**
 * is_digit - A function that checks if a given character is a number digit
 * @c: The given character
 *
 * Return: 1 for digit and 0 for non-digit.
 */
int is_digit(char c)
{
	return (c >= '0' && c <= '9' ? TRUE : FALSE);
}

/**
 * is_non_custom_specifier - A function that checks if a given character is
 * a non-custom specifier.
 * @c: The given character to check.
 *
 * Return: 1 for non-custom specifier else 0.
 */
char is_non_custom_specifier(char c)
{
	switch (c)
	{
		case '%':
		case 'c':
		case 'd':
		case 'E':
		case 'e':
		case 'F':
		case 'f':
		case 'i':
		case 'n':
		case 'o':
		case 'p':
		case 's':
		case 'u':
		case 'X':
		case 'x':
			return (TRUE);
		default:
			return (FALSE);
	}
}

/**
 * is_specifier - A function that checks if a given character is a specifier
 * @c: The character to check
 *
 * Return: 1 for specifier else 0.
 */
char is_specifier(char c)
{
	if (is_non_custom_specifier(c))
		return (TRUE);
	switch (c)
	{
		case 'b':
		case 'R':
		case 'r':
		case 'S':
			return (TRUE);
		default:
			return (FALSE);
	}
}

/**
 * is_flag - A function that checks if a given character is a flag
 * @c: The given character to check.
 *
 * Return: 1 if character is flag else 0.
 */
char is_flag(char c)
{
	switch (c)
	{
		case '_':
		case '+':
		case '\'':
		case ' ':
		case '#':
		case '0':
			return (TRUE);
		default:
			return (FALSE);
	}
}

/**
 * is_length - A function that checks if a given character is a length
 * specifier.
 * @c: The given character to check.
 *
 * Return: 1 for length character else 0.
 */
char is_length(char c)
{
	switch (c)
	{
		case 'h':
		case 'l':
			return (TRUE);
		default:
			return (FALSE);
	}
}
