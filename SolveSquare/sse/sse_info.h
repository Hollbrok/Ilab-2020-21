#ifndef SSE_INFO_H_INCLUDED
#define SSE_INFO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <float.h>

constexpr double epsilon    = 1e-8;
constexpr double absEpsilon = 1e-12;

namespace roots_ns
{
    enum
    {
        ZERO    = 0,
        ONE     = 1,
        TWO     = 2,
        INF     = -1,
        ERROR   = -2
    };
}

typedef int nOroots_t;

auto solve_square(double *x1, double *x2) -> nOroots_t;

auto get_roots(double a, double b, double c, double *x1, double *x2) -> nOroots_t;

auto lin_solve(double a, double b, double *x1, double *x2) -> nOroots_t;

auto print_result(int roots, double *x1, double *x2) -> void;

auto is_equal(double a, double b) -> bool;



#endif // SSE_INFO_H_INCLUDED
