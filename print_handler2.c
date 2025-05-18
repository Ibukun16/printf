#include "main.h"

/**
 * set_binary_fmat - A function that set format of an unsigned binary
 * integer to print.
 * @list: The argument list
 * @fmat_spec: The format specifier details
 *
 * Return: void.
 */
void set_binary_fmat(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, len = 0, padding;
	unsigned int num = va_arg(*list, unsigned int);
	char str[33];

	if (num == 0)
		str[len++] = '0';
	else
	{
		while (num > 0 && len < 32)
		{
			str[len++] = (num % 2) + '0';
			num /= 2;
		}
	}
	str[len] = '\0';
	rev_string(str);

	padding = MAX(len, fmat_spec->width) - len;

	if (!fmat_spec->left)
		for (count = 0; count < padding; count++)
			put_charto_buf(fmat_spec->pad);

	for (count = 0; count < len; count++)
		put_charto_buf(str[count]);

	if (fmat_spec->left)
		for (count = 0; count < padding; count++)
			put_charto_buf(' ');
}

/**
 * set_hexacode_fmat - A function that set the format for string and
 * hexadecimal code for non-printable characters.
 * @list: The argument list
 * @fmat_spec: The format specifier details
 *
 * Return: void.
 */
void set_hexacode_fmat(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, vis_len = 0, padding;
	char *str = va_arg(*list, char *);

	if (!str)
	{
		putstr_to_buf("(null)");
		return;
	}
	
	for (count = 0; str[count] != '\0'; count++)
		vis_len += (str[count] < 32 || str[count] >= 127) ? 4 : 1;
	padding = MAX(vis_len, fmat_spec->width) - vis_len;

	if (!fmat_spec->left)
		for (count = 0; count < padding; count++)
			put_charto_buf(fmat_spec->pad);
	for (count = 0; str[count] != '\0'; count++)
	{
		if (str[count] < 32 || str[count] >= 127)
		{
			put_charto_buf('\\');
			put_charto_buf('x');
			put_charto_buf(TO_UPPER(convert_to_hexadecimal(str[count] / 16)));
			put_charto_buf(TO_UPPER(convert_to_hexadecimal(str[count] % 16)));
		}
		else
			put_charto_buf(str[count]);
	}
	if (fmat_spec->left)
		for (count = 0; count < padding; count++)
			put_charto_buf(fmat_spec->pad);
}


/**
 * set_rot13_fmat - A function that set the format to print rot13 string
 * @list: The argument list
 * @fmat_spec: The format specifier information
 *
 * Return: void.
 */
void set_rot13_fmat(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, len, padding;
	char *s = va_arg(*list, char *);

	if (!s)
		s = "(null)";

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

/**
 * set_revstr_fmat - A function that set the format to print reversed string
 * @list: pointer to the argument list
 * @fmat_spec: The format specifier information.
 *
 * Return: void.
 */
void set_revstr_fmat(va_list *list, fmat_spec_def *fmat_spec)
{
	int count, len, padding;
	char *s = va_arg(*list, char *);

	if (!s)
		return;
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
