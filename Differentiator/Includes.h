#pragma once


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
#include <string> 
#include <stdlib.h>


constexpr int NUMBER_OF_VARIABLES = 10;
constexpr int MAX_NAME_SIZE = 10;

constexpr int MAX_FORMULA_SIZE = 300;

using TYPE = int;
using VALUE = int;

class tree_elements;
class tree;

struct Objects {

	struct Object* obj = nullptr;

	char* variables_names[NUMBER_OF_VARIABLES] = {};

	size_t number_of_objects = 0;

};

struct Object
{
	TYPE type_of_object;

	VALUE value;
};


enum TYPES
{
	OPERATOR	= 1,
	NUMBER		= 2,
	BRACKET		= 3,
	VARIABLE	= 4,
	FUNCTION	= 5,
};

enum BRACKET_VALUES
{
	L_BRACKET_VAL = 1,
	R_BRACKET_VAL = 2,
};

enum OPERATORS_VALUES
{
	OP_PLUS_VAL		= 3,
	OP_MIN_VAL		= 4,
	OP_TIMES_VAL	= 5,
	OP_DEL_VAL		= 6,
	OP_POW_VAL		= 7,
};

enum FACTIONS_VALUES
{
	SIN_VAL			= 10,
	COS_VAL			= 11,
	LN_VAL			= 12,
	TG_VAL			= 13,
	CTG_VAL			= 14,
	SH_VAL			= 15,
	CH_VAL			= 16,
};

enum NUMBER_CONSTANTS
{
	EXP_VAL = 20,
	PI_VAL	= 21,
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