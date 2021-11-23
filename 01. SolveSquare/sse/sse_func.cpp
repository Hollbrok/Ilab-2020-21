#include "sse_info.h"

auto solve_square(double *x1, double *x2) -> nOroots_t
{
    printf("Please enter the coeffs of ax^2+bx+c=0\n");

    double a = 0;
    double b = 0;
    double c = 0;

    while (scanf("%lf %lf %lf", &a, &b, &c) != 3)
    {
        printf("Please, enter a numbers, not a letters or anything else :\n");
        fflush (stdin);
    }

    int roots = get_roots(a, b, c, x1, x2);

    return roots;
}

auto get_roots(double a, double b, double c, double *x1, double *x2) -> nOroots_t
{
    using namespace roots_ns;
    if (is_equal(a, 0))
        return lin_solve(b, c, x1, x2);
    else
    {
        double discr = b*b - 4*a*c;

        if ((discr < 0))
        {
            *x1 = 0;
            *x2 = 0;
            return ZERO;
        }
        else if (is_equal(discr, 0))
        {
            if (is_equal(-b/2/a, 0))
            {
                 *x1 = fabs(-b/2/a);
                 *x2 = fabs(-b/2/a);
            }
            else
            {
                *x1 = -b/2/a;
                *x2 = -b/2/a;
            }
            return ONE;
        }
        else if ((!is_equal(discr, 0)))
        {
            *x1 = (-b - sqrt(discr))/2/a;
            *x2 = (-b + sqrt(discr))/2/a;
            return TWO;
        }
    }

    return ERROR;
}

auto lin_solve(double a, double b, double *x1, double *x2) -> nOroots_t
{
    using namespace roots_ns;

    if (is_equal(a, 0))
    {
            if (is_equal(b, 0))
            {
                *x1 = 0;
                *x2 = 0;
                return INF;
            }
            else
            {
                *x1 = 0;
                *x2 = 0;
                return ZERO;
            }
    }
    else
    {
        if (is_equal(-b/a, 0))
        {
            *x1 = fabs(-b/a);
            *x2 = fabs(-b/a);
        }
        else
        {
            *x1 = -b/a;
            *x2 = -b/a;
        }

        return ONE;
    }
}

auto print_result(int roots, double *x1, double *x2) -> void
{
    using namespace roots_ns;
    if (roots == ZERO)
        printf("No roots, exit..\n");
    else if (roots == ONE)
        printf("There is only 1 roots : %lg\n", *x1);
    else if (roots == TWO)
        printf("There are two roots: x1 = [%lg], x2 = [%lg]\n", *x1, *x2);
    else if (roots == INF)
        printf("This equation has infinite number of roots\n");
}

auto is_equal(double a, double b) -> bool
{
    // ѕровер€ем числа на их близость - это нужно в случа€х, когда сравниваемые числа €вл€ютс€ нулевыми или около нул€
	double diff = fabs(a - b);
	if (diff <= absEpsilon)
		return true;

	// ¬ противном случае, возвращаемс€ к алгоритму  нута
	return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
