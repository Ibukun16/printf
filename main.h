#ifndef PRINTF_FUNCTION_HEADER
#define PRINTF_FUNCTION_HEADER
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int _putchar(char c);
int _printf(const char *format, ...);
int prnt_stg(va_list varg, char c);
int int_prnt(va_list arg);
int bioc_unsg(va_list arg, char s);
int num_prnt(unsigned int num, int bs);
int print_s(char *s);
int hex_prnt(unsigned int n, char s);
int reverse(char *s);
int rot13(char *s);
int convert(char s, va_list varg);
#endif /** PRINTF_FUNCTION_HEADER **/
