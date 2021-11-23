#pragma once

#include "Includes.h"
#include "dif_config.h"


struct Objects* fill_structures(FILE* text);

void print_objects(Objects* object);

long size_of_file(FILE* user_code);

char* make_buffer(FILE* file);

int  find_variable_name(char name[MAX_NAME_SIZE], char* variables_names[NUMBER_OF_VARIABLES]);

int find_place(char* variables_names[NUMBER_OF_VARIABLES]);

void Objs_destructor(struct Objects* objs);