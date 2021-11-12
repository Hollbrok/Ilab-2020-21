# Anti-Khiryanov language
 В данном проекте был написал __си__ подобный язык, а сам __Anti-Khiryanov__ язык не реализован, но будет позже!
 
# Что поддерживает язык (что будет добавленно)

- [X] Объявление переменных с инициализацией (__WARNING!!__ сразу инициализируйте переменную)
- [ ] Объявление переменных без инициализации.
- [X] Арифметический операции с числами и переменными;
- [X] Распечатка значений переменных (при помощи функции __print(variable)__ )
- [X] Нелинейность программы ( __while()__, __if()__ )
- [ ] if-else
- [ ] Вызов функций
- [ ] Локальность переменных

# Доп фичи

Если вы не хотите ставить __стейтмент__ в блок, если он один, то язык поддерживает следующий синтаксис:
```C++
...
    x = 1;
    y = 0;
    
    if (x == 1)
        y = 2;
...
```



# Особенности __Anti-Khiryanov language__, которые нужно будет добавить
- [ ] Запрещена рекурсия (будет выводиться: Anti-recursion control find recursion. Khityanov log out!!)
 
# TODO LIST:
- [ ] __if-else__
- [ ] Перевод в ассемблерный код if( 5 < x), т.е. если в __if,while__ есть логический оператор
- [ ] Вызов функций
- [ ] Локальность переменных
- [ ] Выражения на этапе заполнения сразу переводить в конечный результат (2+5*1 ==> 7)
- [ ]  придумать как будет генериться код для вызова функций и т.п.
- [ ] придумать смысл языка (допустим все переменные глобальные)
- [X] Добавить PL_config, чтобы можно там было параметры задавать:
	- [X] Debug regime: true or false
	- [X] Beauty regime: which type of tree do you want: beauty or informationa;
- [X] Как-то заполнять дерево при нескольких строках (пример в examples)
- [X] Придумать признак конца строки (пока что это ';')
- [X] Сделать обработку блоков "{" "}"
- [X] Добавить обработку логических выражений:
    - [X] __if__
    - [X] __while__
    - [X] __for__
- [X] Написать факториал на языке