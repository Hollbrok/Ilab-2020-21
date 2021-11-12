#pragma once

#include "PL_func.h"

bool DEBUG_REGIME = false;


void get_config(bool& debug_regime, bool& beauty_regime)
{
	FILE* config = fopen("PL_config.txt", "r");

	if (config == nullptr)//assert(config);
	{
		printf("No config.  DEBUG_REGIME set by default = false.\n"
			   "BEAUTY set by default = true.\n");

		debug_regime = false;
		beauty_regime = true;

		return;
	}

	char* buffer = make_buffer(config);

	if (strlen(buffer) < 10)
	{
		printf("No config.  DEBUG_REGIME set by default = false.\n"
			"BEAUTY set by default = true.\n");

		fclose(config);

		delete[] buffer;
		
		debug_regime = false;
		beauty_regime = true;

		return;
	}

	char* debug_str = strstr(buffer, "DEBUG");

	if (debug_str == nullptr)
	{
		printf("Debug regime didn't set. DEBUG_REGIME set by default = false\n");
		debug_regime = false;
	}
	else
	{
		int new_start = debug_str - buffer + strlen("DEBUG\0") + 1;

		while ((isspace(buffer[new_start])) || (buffer[new_start] == '='))
			new_start++;

		if (!strncmp(&buffer[new_start], "true", 4))
			debug_regime = true;
		else if (!strncmp(&buffer[new_start], "false", 5))
			debug_regime = false;
		else
		{
			printf("Debug regime didn't set. DEBUG_REGIME set by default = false\n");
			debug_regime = false;
		}
	}

	char* beauty_str = strstr(buffer, "BEAUTY");

	if (beauty_str == nullptr)
	{
		printf("Beauty regime didn't set. BEAUTY_REGIME set by default = true\n");
		beauty_regime = true;
	}
	else
	{
		int new_start = beauty_str - buffer + strlen("BEAUTY\0") + 1;

		while ((isspace(buffer[new_start])) || (buffer[new_start] == '='))
			new_start++;

		if (!strncmp(&buffer[new_start], "true", 4))
			beauty_regime = true;
		else if (!strncmp(&buffer[new_start], "false", 5))
			beauty_regime = false;
		else
		{
			printf("Beauty regime didn't set. BEAUTY_REGIME set by default = true\n");
			beauty_regime = true;
		}
	}



	fclose(config);

	delete[] buffer;

	return;
}

struct Objects* fill_structures(FILE* text)
{
	assert(text && "Nullptr file in fill_structures");

	int space_counter = 0;

	char* buffer = make_buffer(text);

	int i = 0;
	while (buffer[i] != '\0')
	{
		if (isspace(buffer[i]))
		{
			space_counter++;
			i++;
		}
		else i++;
	}


	struct Object* obj = new Object[strlen(buffer) - space_counter] ;	
	assert(obj && "Can't new[] memory for *obj");
	
	int obj_counter = 0;

	char* variables_names[NUMBER_OF_VARIABLES];
	
	for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
		variables_names[i] = new char[MAX_NAME_SIZE] {0};

	int number_of_lines = 0;

	for (int i = 0; buffer[i] != '\0'; i++)
	{
		if (isspace(buffer[i]))
			continue;
		else if (buffer[i] == ';')
		{
			obj[obj_counter].type_of_object = END_OF_LINE;
			obj[obj_counter++].value = END_OF_LINE_VAL;
			number_of_lines++;
		}

		else if (buffer[i] == ')')
		{
			obj[obj_counter].type_of_object = BRACKET;
			obj[obj_counter++].value = R_BRACKET_VAL;
		}
		else if (buffer[i] == '(')
		{
			obj[obj_counter].type_of_object = BRACKET;
			obj[obj_counter++].value = L_BRACKET_VAL;
		}

		else if (buffer[i] == '}')
		{
			obj[obj_counter].type_of_object = BLOCK_BRACKET;
			obj[obj_counter++].value = R_BRACKET_BLOCK_VAL;
		}
		else if (buffer[i] == '{')
		{
			obj[obj_counter].type_of_object = BLOCK_BRACKET;
			obj[obj_counter++].value = L_BRACKET_BLOCK_VAL;
		}

		else if (buffer[i] == '+')
		{
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_PLUS_VAL;
		}
		else if (buffer[i] == '-')
		{
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_MIN_VAL;
		}
		else if (buffer[i] == '*')
		{
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_TIMES_VAL;
		}
		else if (buffer[i] == '/')
		{
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_DEL_VAL;
		}
		else if (buffer[i] == '^')
		{
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_POW_VAL;
		}
		else if (buffer[i] == '+')
		{
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_PLUS_VAL;
		}
		else if (buffer[i] == '=')
		{
			obj[obj_counter].type_of_object = OPERATOR;
			obj[obj_counter++].value = OP_EQUAL_VAL;
		}
		else if (buffer[i] == '<')
		{
			obj[obj_counter].type_of_object = LOGICAL_OPERATOR;
			obj[obj_counter++].value = OP_BELOW_VAL;
		}
		else if (buffer[i] == '>')
		{
			obj[obj_counter].type_of_object = LOGICAL_OPERATOR;
			obj[obj_counter++].value = OP_ABOVE_VAL;
		}
		else if (!strncmp(&buffer[i], "==", 2))
		{
			obj[obj_counter].type_of_object = LOGICAL_OPERATOR;
			obj[obj_counter++].value = OP_IS_EQUAL_VAL;

			i += 2 - 1;
		}
		else if (!strncmp(&buffer[i], "if", 2))
		{
			obj[obj_counter].type_of_object = LOGICAL_FUNCTION;
			obj[obj_counter++].value = IF_VAL;

			i += 2 - 1;
		}
		else if (!strncmp(&buffer[i], "main", 4))
		{
			obj[obj_counter].type_of_object = MAIN_FUNCTION;
			obj[obj_counter++].value = MAIN_VAL;

			i += 4 - 1;
		}
		else if (!strncmp(&buffer[i], "print", 5))
		{
			obj[obj_counter].type_of_object = ARITHMETIC_FUNCTION;
			obj[obj_counter++].value = PRINT_VAL;

			i += 5 - 1;
		}
		else if (!strncmp(&buffer[i], "while", 5))
		{
			obj[obj_counter].type_of_object = LOGICAL_FUNCTION;
			obj[obj_counter++].value = WHILE_VAL;

			i += 5 - 1;
		}
		else if (!strncmp(&buffer[i], "ln", 2))
		{
			obj[obj_counter].type_of_object = ARITHMETIC_FUNCTION;
			obj[obj_counter++].value = LN_VAL;

			i += 2 - 1;
		}
		else if (!strncmp(&buffer[i], "sin", 3))
		{
			obj[obj_counter].type_of_object = ARITHMETIC_FUNCTION;
			obj[obj_counter++].value = SIN_VAL;

			i += 3 - 1;
		}
		else if (!strncmp(&buffer[i], "cos", 3))
		{
			obj[obj_counter].type_of_object = ARITHMETIC_FUNCTION;
			obj[obj_counter++].value = COS_VAL;

			i += 3 - 1;
		}
		else if (!strncmp(&buffer[i], "tg", 2))
		{
			obj[obj_counter].type_of_object = ARITHMETIC_FUNCTION;
			obj[obj_counter++].value = TG_VAL;

			i += 2 - 1;
		}
		else if (!strncmp(&buffer[i], "ctg", 3))
		{
			obj[obj_counter].type_of_object = ARITHMETIC_FUNCTION;
			obj[obj_counter++].value = CTG_VAL;

			i += 3 - 1;
		}
		else if (!strncmp(&buffer[i], "sh", 2))
		{
			obj[obj_counter].type_of_object = ARITHMETIC_FUNCTION;
			obj[obj_counter++].value = SH_VAL;

			i += 2 - 1;
		}
		else if (!strncmp(&buffer[i], "ch", 2))
		{
			//printf("GOOD LN\n");
			obj[obj_counter].type_of_object = ARITHMETIC_FUNCTION;
			obj[obj_counter++].value = CH_VAL;

			i += 2 - 1;
		}
		else if (isalpha(buffer[i]))
		{
			obj[obj_counter].type_of_object = VARIABLE;
			
			char name[MAX_NAME_SIZE] = {};

			int j = 0;
			for (j; isalpha(buffer[i + j]); j++)
				name[j] = buffer[i + j];

			i += j - 1;

			obj[obj_counter].value = find_variable_name(name, variables_names);
			
			if (obj[obj_counter].value == -1)
			{
				obj[obj_counter].value = find_place(variables_names);
				for (size_t counter = 0; counter < strlen(name); counter++)
					(variables_names[obj[obj_counter].value])[counter] = name[counter];
			}
			obj_counter++;
		}
		else if (isdigit(buffer[i]))
		{
			obj[obj_counter].type_of_object = NUMBER;
			obj[obj_counter++].value = atoi(&buffer[i]);

			while (isdigit(buffer[i]))
			{
				i++;
			}
			i--;
		}
		else
		{
			printf("Error\n");
		}


	}

	obj_counter;


	delete[] buffer;

	Objects* objs = new Objects[1];

	objs->obj = obj;
	objs->number_of_objects = obj_counter;
	
	for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
		objs->variables_names[i] = variables_names[i];

	objs->number_of_lines = number_of_lines;
	return objs;
}

void print_objects(Objects* object)
{
	assert(object && "U passed nullptr object to print_objects()");
	printf("\n\n");

	for (size_t i = 0; i < object->number_of_objects; i++)
	{
		switch (object->obj[i].type_of_object)
		{
		case MAIN_FUNCTION:
			printf("%d. type is MAIN_FUNCTION, value is %d\n", i, object->obj[i].value);
			break;
		case OPERATOR:
			printf("%d. type is OPERATOR, value is %d\n", i, object->obj[i].value);
			break;
		case NUMBER:
			printf("%d. type is NUMBER, value is %d\n", i, object->obj[i].value);
			break;
		case BRACKET:
			if(object->obj[i].value == R_BRACKET_VAL)
				printf("%d. type is R_BRACKET, value is %d\n\n", i, object->obj[i].value);
			else 
				printf("\n%d. type is L_BRACKET, value is %d\n", i, object->obj[i].value);
			break;
		case BLOCK_BRACKET:
			if (object->obj[i].value == R_BRACKET_BLOCK_VAL)
				printf("%d. type is R_BLOCK_BRACKET, value is %d\n\n", i, object->obj[i].value);
			else
				printf("\n%d. type is L_BLOCK_BRACKET, value is %d\n", i, object->obj[i].value);
			break;
		case VARIABLE:
			printf("%d. type is VARIABLE, value is %d\n", i, object->obj[i].value);
			break;
		case ARITHMETIC_FUNCTION:
			printf("%d. type is ARITHMETIC_FUNCTION, value is %d\n", i, object->obj[i].value);
			break;
		case END_OF_LINE:
			printf("%d. type is END OF LINE, value is %d\n", i, object->obj[i].value);
			break;
		case LOGICAL_FUNCTION:
			printf("%d. type is LOGICAL FUNCTION, value is %d\n", i, object->obj[i].value);
			break;
		case BINDER:
			printf("%d. type is BINDER, value is %d\n", i, object->obj[i].value);
			break;
		default:
			printf("UNINDENTIFIED TYPE in print_objects. i = %d. TYPE = %d Line: %d\n", i, object->obj[i].type_of_object, __LINE__);
			break;
		}
	}

	return;
}

long size_of_file(FILE* user_code)
{
	assert(user_code);

	fseek(user_code, 0, SEEK_END);
	long file_length = ftell(user_code);
	fseek(user_code, 0, SEEK_SET);

	return file_length;
}

char* make_buffer(FILE* file)
{
	//FILE* database = nullptr;// fopen("database.txt", "rb")
	//fopen_s(&database, name_file, "rb");
	
	assert(file && "file in nullptr in make_buffer");

	long file_length = size_of_file(file);

	char* buffer = new char[file_length + 1] {0};
	assert(buffer && "Can't calloc memory for buffer");

	fread(buffer, sizeof(char), file_length, file);

	//buffer[file_length - 1] = '\0';
	return buffer;
}

int  find_variable_name(char name[MAX_NAME_SIZE], char* variables_names[NUMBER_OF_VARIABLES])
{

	for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
	{
		if (!strcmp(name, variables_names[i]))
			return i;
	}
	return -1;
}

int find_place(char* variables_names[NUMBER_OF_VARIABLES])
{
	for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
	{
		//printf("[%s]\n", variables_names[i]);
		if (strlen(variables_names[i]) == 0)
			return i;
	}
	return -1;
}

void Objs_destructor(struct Objects* objs)
{
	if (objs)
	{
		delete[] objs->obj;
		objs->obj = nullptr;


		for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
		{

			if (objs->variables_names[i])
			{
				delete[] objs->variables_names[i];
				objs->variables_names[i] = nullptr;
			}
		}

		delete[] objs;
		objs = nullptr;
	}
	else
	{
		printf("Objs didn't created");
		return;
	}
}