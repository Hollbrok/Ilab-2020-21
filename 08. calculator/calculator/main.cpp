#include "calculator.h"


int main()
{
    FILE* text = fopen("calc.txt", "rb");
    FILE* res  = fopen("result.txt", "wb");
    assert(text);
    assert(res);

    char* buffer       = make_buffer(text);
    double calc_result = get_express(&buffer);
    printf("        Result is [%.3lg]", calc_result);
    fprintf(res, "[%.3lg]", calc_result);

    fclose(res);
    fclose(text);
    return 0;
}
