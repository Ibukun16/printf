#include "main.h"

/**
 * set_binary_format - A function that set format of an unsigned binary
 * integer to print.
 * @list: The argument list
 * @fmat_spec: The format specifier details
 *
 * Return: void.
 */
void set_binary_format(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, len = 0, padding, size = 32;
	unsigned int num = va_arg(*list, unsigned int), temp;
	char *str;

	str = malloc(sizeof(char) * (size + 1));
	if (str)
	{
		mem_set(str, size, '\0');
		temp = num;
		padding = MAX(len, fmat_spec->width) - len
		for (count = 0; count < size && temp > 0; count++, len++)
		{
			str[count] = (temp % 2) + '0';
			temp /= 2;
		}
		if (!fmat_spec->left)
			for (count = 0; count < padding; count++)
				put_charto_buf(fmat_spec->pad);
		for (count = size - 1; count >= 0 && str[count]; count--)
			put_charto_buf(str[count]);

		if (num == 0)
			put_charto_buf('0');

		if (fmat_spec->left)
			for (count = 0; count < padding; count++)
				put_charto_buf(' ');
	}
}

/**
 * set_hexacode_format - A function that set the format for string and
 * hexadecimal code for non-printable characters.
 * @list: The argument list
 * @fmat_spec: The format specifier details
 *
 * Return: void.
 */
void set_hexacode_format(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, len, padding;
	char *str = va_arg(*list, char *);

	if (str)
	{
		len = str_len(str);
		padding = MAX(len, fmat_spec->width) - len;

		if (!fmat_spec->left)
			for (count = 0; count < padding; count++)
				put_charto_buf(fmat_spec->pad);
		for (count = 0; str[count] != '\0'; count++)
		{
			if (str[count] < 32 || str[count] >= 127)
			{
				put_charto_buf('\\');
				put_charto_buf('x');
				put_charto_buf(TO_UPPER(hex_digit(str[count] / 16)));
				put_charto_buf(TO_UPPER(hex_digit(str[count] % 16)));
			}
			else
				put_charto_buf(str[count]);
		}
		if (fmat_spec->left)
			for (count = 0; count < padding; count++)
				put_charto_buf(fmat_spec->pad);
	}
	else
		putstr_to_buf("(null)");
}

/**
 * set_rot13_format - A function that set the format to print rot13 string
 * @list: The argument list
 * @fmat_spec: The format specifier information
 *
 * Return: void.
 */
void set_rot13_format(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, len, padding;
	char *s = va_arg(*list, char *);

	if (s)
	{
		len = str_len(s);
		padding = MAX(len, fmat_spec->width) - len;
		if (!fmat_spec->left)
			for (count = 0; count < padding; count++)
				put_charto_buf(fmat_spec->pad);

		for (count = 0; s[count] != '\0'; count++)
		{
			if (s[count] >= 'a' && s[count] <= 'z')
				put_charto_buf((s[count] - 84) % 26 + 97);
			else if (s[count] >= 'A' && s[count] <= 'Z')
				put_charto_buf((s[count] - 52) % 26 + 65);
			else
				put_charto_buf(s[count]);
		}

		if (fmat_spec->left)
			for (count = 0; count < padding; count++)
				put_charto_buf(fmat_spec->pad);
	}
}

/**
 * set_revstr_format - A function that set the format to print reversed string
 * @list: pointer to the argument list
 * @fmat_spec: The format specifier information.
 *
 * Return: void.
 */
void set_revstr_format(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, len;
	char *s = va_arg(*list, char *);

	if (s)
	{
		len = str_len(s);
		padding = MAX(len, fmat_spec->width) - len;
		if (!fmat_spec->left)
			for (count = 0; count < padding; count++)
				put_charto_buf(fmat_spec->pad);

		for (count = len - 1; count >= 0; count--)
			put_charto_buf(s[count]);

		if (fmat_spec->left)
			for (count = 0; count < padding; count++)
				put_charto_buf(fmat_spec->pad);
	}
}
