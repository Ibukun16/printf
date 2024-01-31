#ifndef PRINTF_FUNCTION_HEADER
#define PRINTF_FUNCTION_HEADER
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define SIZE_BUF 1024

/** FLAGS **/
#define NEG_FLG 1
#define POS_FLG 2
#define ZERO_FLG 4
#define HASH_FLG 8
#define SPACE_FLG 16

/** SIZES **/
#define LONG_SZ 2
#define SHORT_SZ 1


#endif /** PRINTF_FUNCTION_HEADER **/
