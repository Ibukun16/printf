#ifndef PRINTF_HEADER
#define PRINTF_HEADER
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
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
#define ABS(a) ((a) > (0) ? (a) : (0- (a)))
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
 * struct fmt - Struct operator
 *
 * @fmt: The format.
 * @func: The function associated.
 */
struct fmt
{
	char fmt;
	int (*func)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct operator
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;


int _putchar(char c);
int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i, va_list list, char buf[], int flgs,
		int wdt, int prec, int siz);


/***************** FUNCTIONS ********************/


/*** Functions to print characters and strings ***/
int print_char(va_list types, char buf[], int flgs, int wdt, int prec, int siz);
int print_percent(va_list types, char buf[], int flgs, int wdt, int prec, int siz);
int print_string(va_list types, char buf[], int flgs, int wdt, int prec, int siz);

/*** Functions to print numbers ***/
int print_int(va_list types, char buf[], int flgs, int wdt, int prec, int siz);
int print_binary(va_list types, char buf[], int flgs, int wdt, int prec, int siz);
int print_unsigned(va_lists types, char buf[], int flgs, int wdt, int prec, int siz);
int print octal(va_list types, char buf[], int flgs, int wdt, int prec, int siz);
int print_hexal(va_list types, char buffer[], int flgs, int wdt, int prec, int siz);
int print_hex_upper(va_list types, char buf[], int flgs, int wdt, int prec, int siz);
int print_hexa(va_list types, char map_to[], char buf[], int flgs, char flg_ch, int prec, int siz);

/*** Function to print non printable characters ***/
int print_non_printable(va_list types, char buf[], int flgs, int wdt, int prec, int siz);

/*** Function to print memory address ***/
int print_pointer(va_list types, char buf[], int flgs, int wdt, int prec, int siz);

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
int write_numb(int is_positive, int idx, char buf[], int flgs, int wdt, int prec, int siz);
int write_num(int idx, char buf[], int flgs, int wdt, int prec, int len, char pad, char xtra_ch);
int prnt_pointer(char buf[], int idx, int len, int wdt, int flgs, char pad, char xtra_ch, int pad_start);
int write_unsgned(int is_negative, int idx, char buf[], int flgs, int wdt, int prec, int siz);


/*** UTILS ***/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_num(long int num, int siz);
long int convert_size_unsgned(unsigned long int num, int size);
#endif /** PRINTF_HEADER **/
