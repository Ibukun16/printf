#ifndef _PRINTF_HEADER_
#define _PRINTF_HEADER_
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
 * @set_precision: Specifies the presence of a value for precision
 * @set_width: Specifies the presence of a value for width
 * @set_flag: Specifies the presence of the '#' flag
 * @space: Specifies the presence of the ' ' (invisible plus sign) flag
 * @left: Specifies the presence of the '-' (left-align) flag
 * @pos_sign: Specifies the presence of the '+' flag
 * @grp: The current locale's digit separator for integers
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
	char set_precision;
	char set_width;
	char set_flag;
	char space;
	char left;
	char pos_sign;
	char grp;
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
struct float_info
{
	char float_sign;
	char *exp;
	char *mantissa;
};
typedef struct float_info float_typ;

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
char is_letter(char c);
void print_nchars(int n, ...);
void print_ntimes(char c, int n);
void put_numto_buf(int zeros, long num, char *str);
void set_format_error(const char *format, int *index, int len,mint last_tokn, int *error);
/*** Functions to print numbers ***/
void set_dec_fmat(va_list *list, fmat_spec_def *fmat_spec);
int print_binary(va_list types, char buf[], int flgs, int wdt, int prec, int siz);
int print_unsgned(va_list types, char buf[], int flgs, int wdt, int prec, int siz);
int print_octal(va_list types, char buf[], int flgs, int wdt, int prec, int siz);
int print_hexadecimal(va_list types, char buffer[], int flgs, int wdt, int prec, int siz);
int print_upper_hex(va_list types, char buf[], int flgs, int wdt, int prec, int siz);
int print_hex(va_list types, char map[], char buf[], int flgs,
		char flg_ch, int wdt, int prec, int siz);

/*** Function to print non printable characters ***/
int print_non_printable(va_list types, char buf[], int flgs, int wdt, int prec, int siz);

/*** Function to print memory address ***/
int pointer(va_list types, char buf[], int flgs, int wdt, int prec, int siz);

/*** Function to handle other specifiers ***/
int get_flags(const char *fmt, int *f);
int get_width(const char *fmt, int *w, va_list lists);
int get_precision(const char *fmt, int *p, va_list list);
int get_size(const char *fmt, int *s);

/*** Function to print string in reverse ***/
int print_reverse(va_list types, char buf[], int flgs, int wdt, int prec, int siz);

/*** Function that print a string in rot 13 ***/
int rot13_string(va_list types, char buf[], int flgs, int wdt, int prec, int siz);

/*** width handler ***/
int handle_write_char(char c, char buf[], int flgs, int wdt, int prec, int siz);
int write_numb(int neg, int idx, char buf[], int flgs, int wdt, int prec, int siz);
int write_num(int idx, char buf[], int flgs, int wdt, int prec, int len, char pad, char xtra_ch);
int prnt_pointer(char buf[], int idx, int len, int wdt, int flgs, char pad, char xtra_ch, int pad_start);
int write_unsgned(int neg, int idx, char buf[], int flgs, int wdt, int prec, int siz);


/*** UTIL FUNCTIONS ***/

void rev_string(char *str);
int index_of(char *str, char c);
void left_shift(char *str, int n);
char mem_set(char *str, char c, unsigned int n);

long int convert_size_num(long int num, int siz);
long int convert_size_unsgned(unsigned long int num, int siz);

/*** PARSER FUNCTION FOR PRINTF ***/
int read_format(const char *str, va_list list, fmat_spec_def *fmat_spec, int *last_tokn);

/*** FORMAT DATA FUNCTION ***/
float_typ *create_new_float(u_short_typ exp_size, u_short_typ mantissa_size);
void free_float_data(float_typ *float_data);
void init_format_data(fmat_spec_def *specifier);
fmat_spec_def *create_new_format();


#endif /** _PRINTF_HEADER_ **/
