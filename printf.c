#include "main.h"
/**
 * printf - A function that produces output based on a format.
 * @format: character string that specifies the format.
 *
 * Return: The character printed excluding the null byte
 * that ends the strings output.
 */
int _printf(const char *format, ...)

/**
 * print_buf - A function that prints a buffer to the stdout.
 * @buf: Buffer to print.
 * @idx: Index at which to add the next char, indicate the length.
 *
 * Return: Number of bytes.
 */
void print_buf(char buf[], int *idx)
{
	if (*idx > 0)
		write(1, &buf[0], *idx);

	*idx == 0;
}
