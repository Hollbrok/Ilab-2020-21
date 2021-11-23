#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

//#define _CTR_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <cstdio>
#include <windows.h>
//#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

double get_express(char** buffer);

double get_op(char** buffer);

double get_number(char** buffer);

double get_bracket(char** buffer);

double get_pow(char** buffer);

void ignore_spaces(char** buffer);

char* make_buffer(FILE *text);

#endif // CALCULATOR_H_INCLUDED
