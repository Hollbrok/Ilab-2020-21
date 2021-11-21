#include "calculator.h"

char* make_buffer(FILE* text)
{

    fseek(text, 0, SEEK_END);
    int file_length = ftell(text);
    fseek(text, 0, SEEK_SET);

    file_length++;

    char* buffer = (char*) calloc(file_length, sizeof(char));
    assert(buffer);


    fread(buffer, sizeof(char), file_length, text);

    buffer[file_length] = '\0';

    return buffer;
}


double get_express(char** buffer)
{
    printf("[%s]\n", *buffer);
    double result = 0;
    int sign      = 1;

    if ( ((**buffer) == '-') || ((**buffer) == '+'))
    {
        while( ((**buffer) == '-') || ((**buffer) == '+'))
        {
            if ((**buffer) == '-')
                sign *= (-1);
            else
                sign *= (+1);

            ignore_spaces(buffer);
            (*buffer)++;
        }

        result  += (sign) * get_op(buffer);
        sign = 1;
    }
    else
        result += get_op(buffer);

    do
    {
        ignore_spaces(buffer);
        if(**buffer == ')')
            break;

        if ( ((**buffer) == '-') || ((**buffer) == '+'))
        {
            while( ((**buffer) == '-') || ((**buffer) == '+'))
            {
                if ((**buffer) == '-')
                    sign *= (-1);
                else
                    sign *= (+1);

                ignore_spaces(buffer);
                (*buffer)++;
            }

            double test = get_op(buffer);
            result  += (sign) * test;
            sign = 1;
        }

        else if(**buffer)
            (*buffer)++;


    } while( ((**buffer == '+') || (**buffer == '-')));

    return result;
}

double get_op(char** buffer) // "*"     "/"
{
    ignore_spaces(buffer);

    double result = get_pow(buffer);

    ignore_spaces(buffer);

    while ( (((**buffer) == '/') || ((**buffer) == '*')) && (**buffer))
    {
        if ( (**buffer) == '/')
        {
            ignore_spaces(buffer);
            (*buffer)++;
            double number = get_pow(buffer);
            result /= number;
        }
        else if ( (**buffer) == '*')
        {
            ignore_spaces(buffer);
            (*buffer)++;
            double number = get_pow(buffer);
            result *= number;
        }

        ignore_spaces(buffer);
    }

    return result;
}

void ignore_spaces(char** buffer)
{
    while (isspace(**buffer))
        (*buffer)++;
}

double get_number(char** buffer)
{
    ignore_spaces(buffer);
    double number = atof(*buffer);

    while (isdigit(**buffer) || (**buffer == ','))
        (*buffer)++;

    ignore_spaces(buffer);

    return number;
}

double get_bracket(char** buffer)
{
    ignore_spaces(buffer);
    double test = 0;

    if ((**buffer) == '(')
    {
        (*buffer)++;
        test = get_express(buffer);

        if ((**buffer) != ')') 
        {
            printf("**buffer = [%c]\n", **buffer);
            printf("ERROR\n");
        }
        (*buffer)++;
    }
    else
        test = get_number(buffer);

    return test;
}

double get_pow(char** buffer)
{
    ignore_spaces(buffer);
    double test = 0;

    test = get_bracket(buffer);
    ignore_spaces(buffer);

    if(**buffer == '^')
    {
        (*buffer)++;
        test = pow(test, get_express(buffer));
    }

    return test;
}
