#ifndef _PRINTF_HEADER_
#define _PRINTF_HEADER_
#include <inttypes.h>
#include <ctype.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef T
#define T 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL ((void *)0)
#endif

#define MAX_WIDTH "2147483647"
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) > (0) ? (a) : (0 - (a)))
#define NO_NEG(a) ((a) < (0) ? (0) : ((a)))
#define NO_LESS(a, b) ((a) < (b) ? (b) : ((a)))
#define TO_UPPER(c) ((c) >= 'a' && (c) <= 'z' ? (c) - 32 : (c))
#define TO_LOWER(c) ((c) >= 'A' && (c) <= 'Z' ? (c) + 32 : (c))
#define FMT_PREC_EMPTY(fmt_inf) (fmt_inf->is_precision_set && !fmt_inf->prec)
#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/**** FLAGS ****/
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/**** SIZES ****/
#define S_LONG 2
#define S_SHORT 1

/**
 * struct format_spec - Specifier of the struct elements.
 * @precision: The specified format precision
 * @width: The length of the formatted elements
 * @specifier: The character specifier
 * @is_char: Specifies the presence of the 'hh' length modifier
 * @is_short: Specifies the presence of the 'h' length modifier
 * @is_long_double: Specifies the presence of the 'L' length modifier
 * @is_long: Specifies the presence of the 'l' length modifier
 * @is_long_long: Specifies the presence of the 'll' length modifier
 * @is_precision_set: Specifies the presence of a value for precision
 * @is_width_set: Specifies the presence of a value for width
 * @alt: Specifies the presence of the '#' flag
 * @space: Specifies the presence of the ' ' (invisible plus sign) flag
 * @left: Specifies the presence of the '-' (left-align) flag
 * @pos_sign: Specifies the presence of the '+' flag
 * @group: The current locale's digit separator for integers
 * @pad: The character to use for padding the output
 */
struct format_spec
{
	int precision;
	int width;
	char specifier;
	char is_char;
	char is_short;
	char is_long_double;
	char is_long;
	char is_long_long;
	char is_precision_set;
	char is_width_set;
	char alt;
	char space;
	char left;
	char pos_sign;
	char group;
	char pad;
};
typedef struct format_spec fmat_spec_def;


/**
 * struct print_specifier - Struct operator of a function that prints
 * an argument.
 *
 * @specifier: The format specifier
 * @func: Pointer to the function that does the printing.
 */
struct print_specifier
{
	char specifier;
	void (*func)(va_list *args, fmat_spec_def *fmat_spec);
};


/**
 * union - A function that allows multiple members to occupy same memory location
 * @duo: The representation for double
 * @bits: The representation for size
 * @un: The union name
 */
union
        {
                double duo;
                uint64_t bits;
        } un;


/**
 * typedef struct formatt format_type - Struct operator
 *
 * @format: The format.
 * @format_type: The function associated.
 */
typedef struct print_specifier set_specifier;
typedef unsigned char u_char_typ;
typedef unsigned short u_short_typ;


/**
 * struct float_info - Struct function that represents the IEE754 spec of a float
 * @float_sign: The sign representing the float
 * @exp: The exponential of the float
 * @mantissa: The mantissa of the float
 */
struct float_data
{
	char float_sign;
	char *exp;
	char *mantissa;
};
typedef struct float_data float_typ;


int _printf(const char *format, ...);
int print_buf(char c, char flag);
int put_charto_buf(char c);
int putstr_to_buf(char *str);
void set_format(va_list *args, fmat_spec_def *format_det);



/***************** FUNCTIONS ********************/

/*** Functions to print characters and strings ***/
void set_percent_fmat(va_list *args, fmat_spec_def *fmat_spec);
void set_pointer_fmat(va_list *args, fmat_spec_def *fmat_spec);
void set_char_fmat(va_list *args, fmat_spec_def *fmat_spec);
void set_string_fmat(va_list *args, fmat_spec_def *fmat_spec);

/*** Functions to print unsigned integers, decimal and hexadecimal ***/
void set_dec_fmat(va_list *list, fmat_spec_def *fmat_spec);
void set_hexadec_format(va_list *list, fmat_spec_def *fmat_spec);
void set_octadec_format(va_list *list, fmat_spec_def *fmat_spec);
void set_unsigned_int_format(va_list list, fmat_spec_def *fmat_spec);

/*** Helper functions for print ***/
char is_specifier(char c);
int is_digit(char c);
char is_flag(char c);
char is_letter(char c);
char is_length(char c);
char is_specifier(char c);
void print_nchars(int n, ...);
void print_ntimes(char c, int n);
char is_non_custom_specifier(char c);
void put_numto_buf(int zeros, long num, char *str);
void set_format_error(const char *format, int *index, int len,
		int last_tokn, int *error);

/*** Functions to print character and string ***/
void set_char_fmat(va_list *args, fmat_spec_def *fmat_spec);
void set_string_fmat(va_list *args, fmat_spec_def *fmat_spec);
void set_pointer_fmat(va_list *args, fmat_spec_def *fmat_spec);
void set_percent_fmat(va_list *args, fmat_spec_def *fmat_spec);

/*** Functions to print numbers ***/
void set_dec_fmat(va_list *list, fmat_spec_def *fmat_spec);
void set_rot13_format(va_list *list, fmat_spec_def *fmat_spec);
void set_revstr_format(va_list *list, fmat_spec_def *fmat_spec);
void set_binary_format(va_list *list, fmat_spec_def *fmat_spec);
void set_octadec_format(va_list *list, fmat_spec_def *fmat_spec);
void set_hexadec_format(va_list *list, fmat_spec_def *fmat_spec);
void set_hexacode_format(va_list *list, fmat_spec_def *fmat_spec);
void set_unsigned_int_format(va_list *list, fmat_spec_def *fmat_spec);


/*** Function to handle other specifiers ***/
int get_flags(const char *fmt, int *f);
int get_width(const char *fmt, int *w, va_list lists);
int get_precision(const char *fmt, int *p, va_list list);
int get_size(const char *fmt, int *s);

/*** Util Functions ***/
int str_len(char *str);
void rev_string(char *str);
char *ptr_to_str(void *ptr);
void shift_left(char *str, int n);
int count_char(char *scr, char ch);
char *convert_long_to_str(long num);
int index_of_char(char *str, char c);
char *is_invalid(float_typ *flot_data);
char *sub_str(char *str, int n, bool free);
char *convert_long_long_to_str(long long num);
char *convert_u_long_to_str(unsigned long num);
char *convert_u_long_to_str(unsigned long num);
char *str_cat(char *main, char *sec, bool free);
char mem_set(char *str, char c, unsigned int n);
char *delete_char(char *str, char ch, bool free);
char *trim_end(char *str, char ch, bool free_str);
char *trim_start(char *str, char ch, bool free_str);
char *append_char(char *str, char ch, int n, bool free);
char *insert_char(char *src, int pos, char ch, bool free);
char *convert_unsigned_to_str(unsigned long long num, int neg);

long int convert_size_num(long int num, int siz);
long int convert_size_unsgned(unsigned long int num, int siz);

/*** Mathematical Functions ***/
int convert_str_to_int(char *num);
int convert_bin_to_str(char *arr);
char convert_to_hexadecimal(char c);
char *compute_npower_of_two(short n);
char compare_numbers(char *n1, char *n2);
char *convert_long_to_oct(unsigned long num);
char *strn_copy(char *dest, char *src, int n);
char *compute_npower_of_five(unsigned short n);
char *round_float(char *num, unsigned int prec);
unsigned int pos_num_powerof_two(unsigned int n);
char *round_float_to_int(char *num, bool free_mem);
char *multiply_int(char *n1, char *n2, char free_mem);
char *unsigned_long_to_hex(unsigned long num, char upper);
char *add_positive_nums(char *n1, char *n2, char free_mem);
char *multiply_float(char *num1, char *num2, char free_mem);
char *round_up(char *num, unsigned int prec, bool free_mem);
char *add_positive_float_nums(char *n1, char *n2, int free_mem);
char *divide_by_10exp_n(char *num, unsigned short n, char free_num);
char *multiply_by_multiple_of_10(const char *num1, const char *num_10);

/*** Parser function for printf ***/
int set_number(const char *str, int *num);
int set_flags(const char *str, fmat_spec_def *fmat_spec);
void set_length(char ch_cur, int *pos, fmat_spec_def *fmat_spec);
void set_precision(const char *str, va_list list, fmat_spec_def *fmat_spec,
                int *n, int *err)
int read_format(const char *str, va_list list, fmat_spec_def *fmat_spec,
		int *last_tokn);

/*** Format data function ***/
float_typ *create_new_float(u_short_typ size_exp, u_short_typ size_mant);
float_typ *create_new_float(u_short_typ exp_size, u_short_typ mantissa_size)
void free_float_data(float_typ *float_data);
void init_format_data(fmat_spec_def *specifier);
fmat_spec_def *create_new_format();

#endif /** _PRINTF_HEADER_ **/
