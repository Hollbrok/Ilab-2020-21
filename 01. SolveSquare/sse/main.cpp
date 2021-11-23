#include "sse_info.h"


int main()
{
    setlocale(LC_ALL, "Russian");

    printf("Welcome in SSE! ");

    double x1 = 0;
    double x2 = 0;
    int roots = solve_square(&x1, &x2);
    //printf("got roots\n");
    print_result(roots, &x1, &x2);
    printf("See you soon..\n");
    system("PAUSE");
    return 0;
}

