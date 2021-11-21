#include "Sortline.h"

void LineProcessing(FILE *onegin, FILE *res, char *mode, char *isbred)
{
    assert(onegin != NULL);
    assert(res    != NULL);
    assert(mode   != NULL);
    assert(isbred != NULL);

    fseek(onegin, 0, SEEK_END);
    long file_length = ftell(onegin);

    wchar_t *stream = (wchar_t *) calloc(file_length, sizeof(wchar_t));             	// массив хранения символов файла
    assert(stream);

    fseek(onegin, 0, SEEK_SET);

    int file_lines = 0;                                                     		//кол-во строк в файле
    file_length = 0;                                                        		//размер файла

    while((stream[file_length] = fgetwc(onegin)) && !feof(onegin))
    {
        if(stream[file_length] == '\n')                                     		// если "\n", то + 1 к кол-ву строк
            file_lines++;

        file_length++;                                                      		//шаг итерации(+ 1 к номеру проверяемого символа)
    }
    free(stream + file_length);                                                 	//освобождаем остатки памяти

    struct line_t *lines = (line_t*)calloc(file_lines, sizeof(line_t));         	// инициализируем структуры по кол-ву строк, рассчитанных выше
    assert(lines);

    long k = 0;                                                                  	// счётчик символов(пробелы, табуляции, \n)
    long i = 0;                                                                  	// счётчик структур
    while(TRUE)                                                                 	// читаем строки из массива stream в структуры
    {
        while(TRUE)
        {
            if(k >= file_length)
                break;
            if((stream[k] == ' ') || (stream[k] == '\t') || (stream[k] == '\n') || (stream[k] == '.') || (stream[k] == 'I') || (stream[k] == 'L') || (stream[k] == 'X') || (stream[k] == 'V') || (stream[k] == ','))//если один из первых символов(пробел, табуляция, \n), то +1 к счетчику этих символов
                k++;
            else
                break;
        }

        if(k >= file_length)
            break;

        lines[i].line = &stream[k];
        //OemToChar(lines[i].line, lines[i].line);
        lines[i].length = k;
        while(stream[k] != '\n')//пока не конец строки
        {
            if(k >= file_length)
                break;
            k++;
        }
        k++;

        lines[i].length = k - lines[i].length;      //отнять кол-во символов вначале(пробел \t \n).
        i++;
    }

    Sorting(lines, i, mode);                        //сортировка строк

    Bred_Gen(lines, isbred, i);                     //бредогенератор

    for(long t = 0; t < i; ++t)                      //печать в файл
        for(long j = 0; j < lines[t].length; j++)
        {
            //OemToChar(&lines[t].line[j], &lines[t].line[j]);
            fprintf(res, "%lc", lines[t].line[j]);   //печать каждого символа отсортировынных строк в файл(res)
        }

    free(stream);                                   //освобождение выделенной памяти

}

//-----------------------------------------------------------------------------

void Sorting(line_t *lines, long n, char *mode)
{
    Insertion(lines, n, mode);
}

//-----------------------------------------------------------------------------
void Insertion(line_t *lines, long n, char *mode)
{
    assert(lines);
    assert(mode);

    int (*str_comp)(line_t*, long, long);

    if(!strcmp(mode, "decrease_end"))
        str_comp = strcomp_decrease_end;
    else if(!strcmp(mode, "increase_end"))
        str_comp = strcomp_increase_end;
    else if(!strcmp(mode, "decrease"))
        str_comp = strcomp_decrease;
    else if(!strcmp(mode, "increase"))
        str_comp = strcomp_increase;
    else exit(1);

    for(long i = 0; i < n - 1; i++)
        for(long j = i + 1; j < n; j++)
			if(str_comp(lines, i, j) > 0)
                Switcher(lines, i, j);                              //если нужное условие str_comp
}

//-----------------------------------------------------------------------------

int strcomp_decrease(line_t *lines, long a, long b)
{
    assert(lines);

    long i = 0;
    long j = 0;

    while(!iswalpha(lines[a].line[i]) || lines[a].line[i] == '\'' )//  Макрос isalpha() возвращает ненулевое значение, если его аргумент является буквой алфавита (верхнего или нижнего регистра). В противном случае возвращается 0.
        i++;                                                      //  все цифры и апострофы пропускаем
    while(!iswalpha(lines[b].line[j]) || lines[a].line[i] == '\'' )//  аналогично
        j++;

    while(i < lines[a].length && j < lines[b].length)            //  Пока индексы номера символа меньше длины строки
    {
        if(lines[a].line[i] == lines[b].line[j])                 // Пока символы равны увеличиваем индесы на 1
        {
            i++;
            j++;
        }
        else                                                      // Как только они не равны
            return -(lines[a].line[i] - lines[b].line[j]);        // делаем возращение для компаратора.
    }
    return -(lines[a].line[i] - lines[b].line[j]);                // Если достигнут конец строки, то делаем аналогично.
}

//-----------------------------------------------------------------------------

int strcomp_increase(line_t *lines, long a, long b)                   //все аналогично Strcomp_decrease, но return противоположный.
{
    assert(lines);

    long i = 0;
    long j = 0;

    while(!iswalpha(lines[a].line[i]) || lines[a].line[i] == '\'')
        i++;
    while(!iswalpha(lines[b].line[j]) || lines[a].line[i] == '\'')
        j++;

    while(i < lines[a].length && j < lines[b].length)
    {
        if(lines[a].line[i] == lines[b].line[j])
        {
            i++;
            j++;
        }
        else
            return (lines[a].line[i] - lines[b].line[j]);
    }
    return (lines[a].line[i] - lines[b].line[j]);
}

//-----------------------------------------------------------------------------

void Switcher(line_t *lines, long l, long r)                          //меняем строки местами.
{
    assert(lines);

    wchar_t *strtmp = lines[l].line;                                 //временная строка
    lines[l].line = lines[r].line;                                   //меняем строки
    lines[r].line = strtmp;                                          //местами

    long tmp = lines[l].length;        //временная переменная длины
    lines[l].length = lines[r].length;//меняем длины
    lines[r].length = tmp;            //местами
}

//-----------------------------------------------------------------------------

int strcomp_increase_end(line_t *lines, long a, long b)
{
    assert(lines);

    long i = lines[a].length;
    long j = lines[b].length;

    while(!iswalpha(lines[a].line[i]) || lines[a].line[i] == '\'' )
        i--;
    while(!iswalpha(lines[b].line[j]) || lines[a].line[i] == '\'' )
        j--;

    while(i > 0 && j > 0)
    {
        if(lines[a].line[i] == lines[b].line[j])
        {
            i--;
            j--;
        }
        else
            return (lines[a].line[i] - lines[b].line[j]);
    }
    return (lines[a].line[i] - lines[b].line[j]);

}

//-----------------------------------------------------------------------------

int strcomp_decrease_end(line_t *lines, long a, long b)
{
    assert(lines);

    long i = lines[a].length;
    long j = lines[b].length;

    while(!iswalpha(lines[a].line[i]) || lines[a].line[i] == '\'')  //  Макрос isalpha() возвращает ненулевое значение, если его аргумент является буквой алфавита (верхнего или нижнего регистра). В противном случае возвращается 0.
        i--;                                                        //  все цифры и апострофы пропускаем
    while(!iswalpha(lines[b].line[j]) || lines[a].line[i] == '\'')  //  аналогично
        j--;

    while(i > 0 && j > 0)                                           //  Пока индексы номера символа меньше длины строки
    {
        if(lines[a].line[i] == lines[b].line[j])                    // Пока символы равны увеличиваем индесы на 1
        {
            i--;
            j--;
        }
        else                                                        // Как только они не равны
            return -(lines[a].line[i] - lines[b].line[j]);          // делаем возращение для компаратора.
    }
    return -(lines[a].line[i] - lines[b].line[j]);                  // Если достигнут конец строки, то делаем аналогично.
}
//-----------------------------------------------------------------------------

void Bred_Gen(line_t *lines, char *isbred, long n)   //бредогенератор.
{
    assert(lines);
    assert(isbred);



    if(!strcmp(isbred, "yes"))                      //проверка нужна ли бредогенерация.
    {
        FILE *res = fopen("res_bred.txt", "w");     //куда выводить результат бредогенерации.
        assert(res != NULL);

        int rand1 = 0;
        int rand2 = 0;

        srand(time(NULL));                          //рандом от времени.

        for(size_t j = 0; j < BRED_SIZE; j++)
        {
            if(rand() % 2 == 1)                     //rand() % 2 -- рандомное число : 0 или 1. Если один, то мы печатаем четверостишие с рифмами через одну.
            {
                rand1 = rand() % (n - 1);           //берем рандомную строчку и печатаем ее в файл.
                for(size_t i = 0; i < lines[rand1].length; i++)
                    fprintf(res, "%lc", lines[rand1].line[i]);

                rand2 = rand() % (n - 1);           //берем другую рандомную строчку и печатаем ее в файл.
                for(size_t i = 0; i < lines[rand2].length; i++)
                    fprintf(res, "%lc", lines[rand2].line[i]);

                rand1++;
                rand2++;

                for(size_t i = 0; i < lines[rand1].length; i++) //теперь заполняем в четверостишие 3 и 4 строчку.
                    fprintf(res, "%lc", lines[rand1].line[i]);
                for(size_t i = 0; i < lines[rand2].length; i++)
                    fprintf(res, "%lc", lines[rand2].line[i]);

                fprintf (res, "\n");
            }

            else                                                //если выпало число 0, то в четверостишие будут рифмы подряд.
            {
                rand1 = rand() % (n - 1);
                for(size_t i = 0; i < lines[rand1].length; i++)
                    fprintf(res, "%lc", lines[rand1].line[i]);

                rand1++;

                for(size_t i = 0; i < lines[rand1].length; i++)
                    fprintf(res, "%lc", lines[rand1].line[i]);

                rand2 = rand() % (n - 1);
                for(size_t i = 0; i < lines[rand2].length; i++)
                    fprintf(res, "%lc", lines[rand2].line[i]);

                rand2++;

                for(size_t i = 0; i < lines[rand2].length; i++)
                    fprintf(res, "%lc", lines[rand2].line[i]);

                fprintf(res, "\n");
            }
        }

        fclose(res);
    }
}

//-----------------------------------------------------------------------------

