#include "main.h"
/**
 * print_handler - A function that prints an argument based on type.
 * @format: The format in which to print the string argument.
 * @args: The list of arguments to be printed.
 * @idx: The index of the string.
 * @buf: Array of buffer that handles print.
 *
 * Return: 1 for successful execution, else 2.
 */
int print_handler(const char *format, int *idx, va_list args, char buf[])
{

