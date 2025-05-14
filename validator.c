#include "main.h"

/**
 * is_digit - A function that checks if a given character is a digit
 * @c: The given character
 *
 * Return: 1 for true else 0 for false
 */
char is_digit(char c)
{
	return (c >= '0' && c <= '9' ? TRUE : FALSE);
}

/**
 * is_non_custom_specifier - A function that checks if a given character is
 * non-custom specifier
 * @c: The character to check
 *
 * Return: 1 for true else 0 for false
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
 * @c: The given character
 *
 * Return: 1 for true else 0 for false
 */
char is_specifier(char c)
{
	if (is_non_custom_specifier(c))
		return (TRUE);
	{
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
}

/**
 * is_flag - A function that determines if a given character is a flag
 * @c: The character to check
 *
 * Return: 1 for true else 0 for false
 */
char is_flag(char c)
{
	switch (c)
	{
	case '-':
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
 * is_length - A function that detremine if a given character indicate length
 * @c: The character to check
 *
 * Return: 1 for true else 0 for fasle
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
