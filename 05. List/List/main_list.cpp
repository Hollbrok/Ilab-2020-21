#include "list.h"

using namespace std;

int main()
{
    CONSTRUCT(list_1);
    list_1.set_element_from_end(10);
    list_1.set_element_to_start(5);
    //printf("end = [%lg]\n", (list_1.get_end())->get_data() );
    //printf("start = [%lg]\n", (list_1.get_start())->get_data() );
    //printf("next to start =[%lg]\n", list_1[list_1.get_end()] );

    list_1[list_1.get_end()] = 20;
    //printf("new end =[%lg]\n", list_1[list_1.get_end()] );

    list_1.set_element_prev_to_x(list_1.get_start(), 55);

    for(int i = 0; i < 20; i++)
        list_1.set_element_to_start(i);
    //printf("start = [%lg]\n", (list_1.get_start())->get_data() );

    // rename to dump
    list_1.print_list(true);

    return 0;
}
