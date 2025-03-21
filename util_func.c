#include "main.h"

/**
 * str_len - A function that determines the length of a given string.
 * @str: The given string.
 *
 * Return: The length of the string.
 */
int str_len(char *str)
{
	int count;

	for (count = 0; str[count] != '\0'; count++)
		;
	return (count);
}

/**
 * mem_set - A function that fill a string memory with a given character
 * starting from position 0.
 * @str: The string containing the section to be filled
 * @n: The length of the section to be filled
 * @c: The character to fill the section with
 *
 * Return: void.
 */
char mem_set(char *str, char c, unsigned int n)
{
	unsigned int count;

	for (count = 0; str && count < n; count++)
		*(str + count) = c;
	return (str);
}

/**
 * shift_left -  A function that moves a string by n bytes to the left.
 * @str: The string to shift
 * @n: The number of bytes to shift the string.
 *
 * Return: void.
 */
void shift_left(char *str, int n)
{
	int i;

	for (i = 1; i <= n; i++)
		str[i - 1] = str[i] != '\0' && str[i - 1] != '\0' ? str[i] : '\0';

}

/**
 * index_of - A function that returns the index of a character in a string.
 * @str: The string containing the characters.
 * @c: The character to find.
 *
 * Return: The index to the character, if found else -1.
 */
int index_of(char *str, char c)
{
	int i;

	for (i = 0; *(str + i) != '\0' && *(str + i) != c; i++)
		;
	return (*(str + i) == c ? i : -1);
}

/**
 * rev_string - A function that reverses a given string.
 * @str: The string to reverse.
 *
 * Return: The void.
 */
void rev_string(char *str)
{
	int c, len = 0;
	char tmp;

	while (str[len] != '\0')
		len++;

	for (c = 0; c < len / 2; c++)
	{
		tmp = str[len - c - 1];
		str[len - c] = str[c];
		str[c] = tmp;
	}
}

