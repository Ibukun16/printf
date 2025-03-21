#include "main.h"

/**
 * init_format_data - A function that initializes the format struct data
 * @specifier: The format data to initialize.
 *
 * Return: void.
 */
void init_format_data(fmat_spec_def *specifier)
{
	if (specifier)
	{
		specifier->precision = 1;
		specifier->width = 0;
		specifier->specifier = FALSE;
		specifier->is_long_double = FALSE;
		specifier->is_long_long = FALSE;
		specifier->is_long = FALSE;
		specifier->is_short = FALSE;
		specifier->is_char = FALSE;
		specifier->is_precision_set = FALSE;
		specifier->is_width_set = FALSE;
		specifier->alt = FALSE;
		specifier->space = FALSE;
		specifier->left = FALSE;
		specifier->show_sign = FALSE;
		specifier->group = FALSE;
		specifier->pad = ' ';
	}
}

/**
 * create_new_format - A function that creates a new format struct and
 * initializes it.
 *
 * Return: A pointer to the newly created format struct or NULL
 */
fmat_spec_def *create_new_format()
{
	fmat_spec_def *data;

	data = malloc(sizeof(fmat_spec_def));
	if (data)
		init_format_data(data);
	return (data);
}

/**
 * create_new_float - A function that creates new float structure.
 * @exp_size: The number of bit in the exponent.
 * @mantissa_size: The number of bits in the mantissa
 *
 * Return: The pointer to the newly created struct, else NULL.
 */
float_typ *create_new_float(u_short_typ exp_size, u_short_typ mantissa_size)
{
	float_typ *float_data;

	float_data = malloc(sizeof(float_typ));
	if (float_data == NULL)
		return (NULL);
	float_data->exp = malloc(sizeof(char) * (exp_size + 1));
	if (float_data->exp == NULL)
		free(float_data);
	float_data->mantissa = malloc(sizeof(char) * (mantissa_size + 1));
	if (float_data->mantissa == NULL)
	{
		free(float_data->exp);
		free(float_data);
	}
	return (float_data);
}

/**
 * free_float_data - A function that freed the memory allocated to
 * a given pointer.
 * @float_data: Pointer to the memory space to free.
 */
void free_float_data(float_typ *float_data)
{
	if (float_data != NULL)
	{
		if (float_data->exp)
			free(float_data->exp);
		if (float_data->mantissa)
			free(float_data->mantissa);
		free(float_data);
	}
}
