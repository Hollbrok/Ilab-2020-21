#include "Sortline.h"
#include <stdio.h>
#include <wchar.h>

int main()//int main(int argc, char *argv[]) для запуска через консоль
{

    //FILE *onegin = fopen(argv[1], "r"); //чтобы через консоль указать какой файл открыть
    //FILE *res = fopen(argv[2], "w");    //чтобы через консоль указать в какой файл записать

    //setlocale(LC_ALL, "");

    FILE *onegin = _wfopen(L"source.txt", L"r");
    FILE *res    = _wfopen(L"res.txt"   , L"w");

    assert(res != NULL);
    assert(onegin != NULL);

    LineProcessing(onegin, res, "increase", "yes"); //yes - делать результат бредогенерации, другое - не делать
    //LineProcessing(onegin, res, argv[3], argv[4]);    //для того, чтобы через консоль выбрать как сортировать

    fclose(onegin);
    fclose(res);

    printf("ONEGIN COMPLITE");
    //Sort_test(); // нужно будет добавить проверку

    return 0;
}
