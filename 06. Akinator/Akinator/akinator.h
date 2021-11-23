#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED


#define PLAY(arg)                       \
    if(!strcmp(#arg, "console"))        \
        bin_tree.play();                \
    else if(!strcmp(#arg, "graphic"))   \
        bin_tree.graphic_play();        \
    else if(!strcmp(#arg, "REG1"))      \
        bin_tree.play();                \
    else if(!strcmp(#arg, "REG2"))      \
        bin_tree.graphic_play();        \
    else                                \
    {                                   \
        printf("No such regime\n");     \
        return 1;                       \
    }

#include <SFML/Graphics.hpp>
#include "tree.h"

void graphic_play();

constexpr bool IsRussianChar1251(const char c);


#endif // AKINATOR_H_INCLUDED
