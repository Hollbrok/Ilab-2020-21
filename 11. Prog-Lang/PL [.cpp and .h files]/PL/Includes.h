#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>
#include <stddef.h>
#include <string> 


constexpr int NUMBER_OF_VARIABLES = 10;
constexpr int MAX_NAME_SIZE = 10;

constexpr int MAX_FORMULA_SIZE = 300;
constexpr int MAX_ASMFILE_SIZE = 10000;

using TYPE = int;
using VALUE = int;

class tree_elements;
class tree;

struct Objects {

	struct Object* obj = nullptr;

	char* variables_names[NUMBER_OF_VARIABLES] = {};

	size_t number_of_objects = 0;
	size_t number_of_lines = 0;
	size_t number_of_statements = 0;

};

struct Object
{
	TYPE type_of_object;

	VALUE value;
};


enum TYPES
{
	OPERATOR	= 1, // enum
	NUMBER		= 2, // the number itself
	BRACKET		= 3, // enum
	VARIABLE	= 4, // number in massive of variables

	ARITHMETIC_FUNCTION	= 5, // enum
	USER_FUNCTION		= 6, 
	LOGICAL_FUNCTION	= 7, // enum
	LOGICAL_OPERATOR	= 8, // enum
	
	MAIN_FUNCTION       = 99,

	BINDER		= 9,		 // just number but with special meaning
	END_OF_LINE = 10,		 // enum


	BLOCK_BRACKET = 13, //!!! MAYBE I NEED TO DO 13 instead of 3, но придется возможно усложнить get_bracket или написать get_block
};

enum MAIN_VALUES
{
	MAIN_VAL = 99,
};

enum BRACKET_VALUES // [0 - 3]
{
	L_BRACKET_VAL = 0,
	R_BRACKET_VAL = 1,

	L_BRACKET_BLOCK_VAL = 2,
	R_BRACKET_BLOCK_VAL = 3,
};

enum OPERATORS_VALUES // [4 - 9]
{
	OP_PLUS_VAL		= 4,
	OP_MIN_VAL		= 5,
	OP_TIMES_VAL	= 6,
	OP_DEL_VAL		= 7,
	OP_POW_VAL		= 8,
	OP_EQUAL_VAL	= 9,


};

enum LOGIC_VALUES //  [30 - 39]
{
	OP_IS_EQUAL_VAL = 30, // ==
	OP_BELOW_VAL	= 31, // <
	OP_ABOVE_VAL	= 32, // >
};

enum LOGIC_FUNCTION_VALUES // [50-99]
{
	IF_VAL		= 50,
	WHILE_VAL	= 51,
	FOR_VAL		= 52,


};

enum ARITH_FUTIONS_VALUES // [10-19]
{
	SIN_VAL			= 10,
	COS_VAL			= 11,
	LN_VAL			= 12,
	TG_VAL			= 13,
	CTG_VAL			= 14,
	SH_VAL			= 15,
	CH_VAL			= 16,
	PRINT_VAL		= 17,
};

enum NUMBER_CONSTANTS // [20-29]
{
	EXP_VAL = 20,
	PI_VAL	= 21,
};

enum SPECIAL_VALUES // [100 .. ]
{
	END_OF_LINE_VAL = 100,
};



/* Debug memory allocation support */
#ifndef NDEBUG 
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h> 

#define SetDbgMemHooks()                                           \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))      

static class __Dummy
{
public:
	/* Class constructor */
	__Dummy(VOID)
	{
		SetDbgMemHooks();
	} /* End of '__Dummy' constructor */
} __ooppss;
#endif /* _DEBUG */ 

#ifndef NDEBUG
#  ifdef _CRTDBG_MAP_ALLOC 
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#  endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */


#define NDEBUG
#ifndef NDEBUG
#define VERIFICATION                                                           \
{                                                                              \
  if (verification()) {                                                        \
    fprintf(stderr, "LINE: %d\nFILE:%s\nFUNC:%s"__LINE__, __FILE__, __func__); \
    assert(0);                                                                 \
  }                                                                            \
}                                                                               
#else
#define VERIFICATION ;
#endif /* _DEBUG */