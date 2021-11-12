#ifndef SORTLINE_H_INCLUDED
#define SORTLINE_H_INCLUDED

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>

const int LIM_SIZE = 500;
const int BRED_SIZE = 1000; //кол-во четверостиший.
const int TRUE = 1;
const int FALSE = 0;

struct line_t //структура строки( содержит саму строку и ее длину).
{
    wchar_t *line;
    long length;
};


//-----------------------------------------------------------------------------
//! @brief Line Processing
//! @param [in] onegin - source file for processing
//! @param [in] res    - the file where the processing result will be written
//! @param [in] mode   - mode of how to process the data
//! @param [in] isbred - mode for delusional generation
//! @author Hollbrok
//! @version 1.3.0
//! @brief
//-----------------------------------------------------------------------------

void LineProcessing(FILE *onegin, FILE *res, char *mode, char* isbred);

//-----------------------------------------------------------------------------
//! @brief Full Sorting strings
//! @param [in] lines - pointer to an array of string structures
//! @param [in] n     - number of string structures
//! @param [in] mode  - mode of how to process the data
//! @author Hollbrok
//! @version 2.2.1
//! @brief
//-----------------------------------------------------------------------------

void Sorting(line_t *lines, long n, char *mode);

//-----------------------------------------------------------------------------
//! @brief Sorting lines
//! @param [in] lines - pointer to an array of string structures
//! @param [in] n     - number of the lines
//! @param [in] mode  - mode of how to process the data
//! @author Hollbrok
//! @version 0.1.1
//! @param
//-----------------------------------------------------------------------------

void Insertion(line_t *lines, long n, char *mode);

//-----------------------------------------------------------------------------
//! @brief Swaps two string structures
//! @param [in] lines - pointer to an array of string structures
//! @param [in] l     - first line number
//! @param [in] r     - second line number
//! @author Hollbrok
//! @version 0.2.7
//! @param
//-----------------------------------------------------------------------------

void Switcher(line_t *lines, long l, long r);//меняет строки местами.

//-----------------------------------------------------------------------------
//! @brief Generates random text based on rhymes
//! @param [in] lines    - pointer to an array of string structures
//! @param [in] bred_ind - id whether it is necessary to make a delusional generator
//! @param [in] n        - number of string structures
//! @author Hollbrok
//! @version 4.1.1
//! @param
//-----------------------------------------------------------------------------

void Bred_Gen(line_t *lines, char *bred_ind, long n);//бредогенератор.

//-----------------------------------------------------------------------------
//! @brief Decrease comparator
//! @param [in] lines - pointer to an array of string structures
//! @param [in] a     - first line number to swap
//! @param [in] b     - second line number to swap
//! @author Hollbrok
//! @version 2.2.8
//! @param
//-----------------------------------------------------------------------------

int strcomp_decrease(line_t *lines, long a, long b);//по убыванию.

//-----------------------------------------------------------------------------
//! @brief From the end decrease comparator
//! @param [in] lines - pointer to an array of string structures
//! @param [in] a     - first line number to swap
//! @param [in] b     - second line number to swap
//! @author Hollbrok
//! @version 2.2.8
//! @param
//-----------------------------------------------------------------------------

int strcomp_decrease_end(line_t *lines, long a, long b);//по убыванию c конца строки.

//-----------------------------------------------------------------------------
//! @brief Increase comparator
//! @param [in] lines - pointer to an array of string structures
//! @param [in] a     - first line number to swap
//! @param [in] b     - second line number to swap
//! @author Hollbrok
//! @version 2.2.8
//! @param
//-----------------------------------------------------------------------------

int strcomp_increase(line_t *lines, long a, long b);//по возрастанию.

//-----------------------------------------------------------------------------
//! @brief From the end increase comparator
//! @param [in] lines - pointer to an array of string structures
//! @param [in] a     - first line number to swap
//! @param [in] b     - second line number to swap
//! @author Hollbrok
//! @version 2.2.8
//! @param
//-----------------------------------------------------------------------------

int strcomp_increase_end(line_t *lines, long a, long b);//по возрастанию с конца строки.



#endif // SORTLINE_H_INCLUDED
