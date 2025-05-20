#include "main.h"

/**
 * sub_str - A function that copies a section of a string
 * @str: The given main string
 * @n: The starting position of the copy
 * @free_str: Flag that determines if the main string is to be freed
 *
 * Return: The copied substring, else NULL
 */
char *sub_str(char *str, int n, bool free_str)
{
	char *copied;
	int len = str_len(str);
	int start = (n < 0) ? len + n : n;
	int size = len - start, m;

	if (!str)
		return (NULL);
	if (start < 0 || start > len)
		return (NULL);
	copied = malloc(sizeof(char) * (size + 1));
	if (!copied)
		return (NULL);
	for (m = 0; m < size; m++)
		copied[m] = str[n + m];
	copied[m] = '\0';
	if (free_str)
		free(str);
	return (copied);
}

/**
 * trim_start - A function that trim off a given character from the beginning
 * of a string
 * @str: The given string to trim character from
 * @ch: The character to trim off from the beginning of a string
 * @free_str: Flag that determines if the main string is to be freed
 *
 * Return: A trimmed string, else NULL;
 */
char *trim_start(char *str, char ch, bool free_str)
{
	int len;
	char *new_str, *start = str;

	 if (!str)
		 return (NULL);
	while (*start == ch)
		start++;
	if (start == str && !free_str)
		return (str);

	len = str_len(start);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	strn_copy(new_str, start, 0);
	if (free_str)
		free(str);
	return (new_str);
}

/**
 * trim_end - A function that trim off a given character from the end
 * of a string
 * @str: The given string to trim character from
 * @ch: The character to trim off from the end of the string
 * @free_str: Flag that determines if the main string is to be freed
 *
 * Return: A trimmed string, else NULL;
 */
char *trim_end(char *str, char ch, bool free_str)
{
	char *new_str, *copy = str;
	int n = 0, m;

	if (!str)
		return (NULL);
	while (*copy != ch && *copy != '\0')
	{
		n++;
		copy++;
	}

	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (NULL);
	for (m = 0; m < n; m++)
		new_str[m] = str[m];
	new_str[m] = '\0';
	if (free_str)
		free(str);
	return (new_str);
}
