#include "main.h"

/**
 * append_char - A function that add multiples of a given character
 * to the end of a string
 * @str: The given string
 * @ch: The caharacter to add at the end of the string
 * @n: The number of times the character is to be added
 * @free_str: Determines if the given string should be freed
 *
 * Return: A new copy of the string, else NULL
 */
char *append_char(char *str, char ch, int n, bool free_str)
{
	int count, size;
	char *new_str;

	if (!str || n < 0)
		return (NULL);
	size = str ? str_len(str) : 0;
	new_str = malloc(sizeof(char) * (size + n + 1));
	if (!new_str)
		return (NULL);
	for (count = 0;  count < (size + n); count++)
		new_str[count] = count < size ? str[count] : ch;
	new_str[count] = '\0';
	if (free_str)
		free(str);
	return (new_str);
}

/**
 * delete_char - A function that removes copies of a given character
 * from a string
 * @str: The given string
 * @ch: The character to remove from the string
 * @free_str: Determines if the given string is to be freed
 *
 * Return: The new copy of the string, else NULL
 */
char *delete_char(char *str, char ch, bool free_str)
{
	char *new_str;
	int len = str_len(str), ch_count = count_char(str, ch), n, m;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (len - ch_count + 1));
	if (!new_str)
		return (NULL);
	for (n = 0, m = 0; str[n] != '\0'; n++)
		if (str[n] != ch)
			new_str[m++] = str[n];
	new_str[m] = '\0';
	if (free_str)
		free(str);
	return (new_str);
}

/**
 * insert_char - A function that inserts a given character into a string
 * @src: The source string
 * @pos: The position to insert the character
 * @ch: The given character to insert
 * @free_str: Determines if the given string is to be freed
 *
 * Return: A copy of the string with the inserted character in place else NULL
 */
char *insert_char(char *src, int pos, char ch, bool free_str)
{
	char *new_str;
	int n, m, len = str_len(src);
	
	if (!src || pos < 0)
		return (NULL);
	if (pos > len)
		return (NULL);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	for (n = 0, m = 0; n < len; n++)
	{
		if (n == pos)
			new_str[m++] = ch;
		new_str[m] = src[n];
		m++;
	}
	if (pos == len)
		new_str[m++] = ch;
	new_str[m] = '\0';
	if (free_str)
		free(src);
	return (new_str);
}

/**
 * count_char - A function that count the number of copies of a character
 * in a string
 * @src: The source string
 * @ch: The given character to look for
 *
 * Return: The number of times the character is found
 */
int count_char(char *src, char ch)
{
	int count = 0, n;

	for (n = 0; src && src[n] != '\0'; n++)
		count += src[n] == ch ? 1 : 0;
	return (count);
}

/**
 * str_cat - A function that concatenate two strings
 * @main: The first string
 * @sec: The second string to add to main
 * @free_str: Determines if the second string is to be freed
 *
 * Return: A pointer to the concatenated string
 */
char *str_cat(char *main, char *sec, bool free_input)
{
	int len1 = 0;
	int len2 = 0;
	int count;
	char *new_str;

	if (main != NULL)
		len1 = str_len(main);
	if (sec != NULL)
		len2 = str_len(sec);

	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_str)
		return (NULL);
	if (main != NULL)
		for (count = 0; main[count] != '\0'; count++)
			new_str[count] = main[count];
	if (sec != NULL)
		for (count = 0; sec[count] != '\0'; count++)
			new_str[len1 + count] = sec[count];
	new_str[len1 + len2] = '\0';
	if (free_input)
	{
		free(main);
		free(sec);
	}
	return (new_str);
}
