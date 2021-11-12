#include "dif.h"

//_CRT_SECURE_NO_WARNINGS

struct Objects* fill_structures(FILE* text)
{
	assert(text && "Nullptr file in fill_structures");

	int space_counter = 0;

	char* buffer = make_buffer(text); // !!! calloc memory by new char[..];

	//printf("buffer = [%s]\n", buffer);
	//printf("strlen = [%d]\n", strlen(buffer));
	//if(buffer[strlen(buffer)] == '\0')
		//printf("last is a zero\n");
	//else printf("last isNOT a  zero\n");

	int i = 0;
	while (buffer[i] != '\0')
	{
		//printf("[%c]", buffer[i]);
		if (isspace(buffer[i]))
		{
			//printf("[[%d]]\n", buffer[i]);
			space_counter++;
			i++;
		}
		else i++;
	}
	//printf("Number of spaces = %d\n", space_counter);
	//printf("Another symbols = %d\n", strlen(buffer) - space_counter);	// GOOD

	struct Object* obj = new Object[strlen(buffer) - space_counter] ;	//(Object*) calloc(number_of_objects, sizeof(Object));
	assert(obj && "Can't new[] memory for *obj");
	
	int obj_counter = 0;

	char* variables_names[NUMBER_OF_VARIABLES];
	
	for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
		variables_names[i] = new char[MAX_NAME_SIZE] {0};


	for (int i = 0; buffer[i] != '\0'; i++)
	{
		if (isspace(buffer[i]))
			continue;
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
		else if (!strncmp(&buffer[i], "ln", 2))
		{
			//printf("GOOD LN\n");
			obj[obj_counter].type_of_object = FUNCTION;
			obj[obj_counter++].value = LN_VAL;

			i += 2 - 1;
		}
		else if (!strncmp(&buffer[i], "sin", 3))
		{
			obj[obj_counter].type_of_object = FUNCTION;
			obj[obj_counter++].value = SIN_VAL;

			i += 3 - 1;
		}
		else if (!strncmp(&buffer[i], "cos", 3))
		{
			//printf("GOOD LN\n");
			obj[obj_counter].type_of_object = FUNCTION;
			obj[obj_counter++].value = COS_VAL;

			i += 3 - 1;
		}
		else if (!strncmp(&buffer[i], "tg", 2))
		{
			//printf("GOOD LN\n");
			obj[obj_counter].type_of_object = FUNCTION;
			obj[obj_counter++].value = TG_VAL;

			i += 2 - 1;
		}
		else if (!strncmp(&buffer[i], "ctg", 3))
		{
			//printf("GOOD LN\n");
			obj[obj_counter].type_of_object = FUNCTION;
			obj[obj_counter++].value = CTG_VAL;

			i += 3 - 1;
		}
		else if (!strncmp(&buffer[i], "sh", 2))
		{
			//printf("GOOD LN\n");
			obj[obj_counter].type_of_object = FUNCTION;
			obj[obj_counter++].value = SH_VAL;

			i += 2 - 1;
		}
		else if (!strncmp(&buffer[i], "ch", 2))
		{
			//printf("GOOD LN\n");
			obj[obj_counter].type_of_object = FUNCTION;
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
				//strncmp(variables_names[obj[obj_counter].value], name, strlen(name));
				for (int counter = 0; counter < strlen(name); counter++)
					(variables_names[obj[obj_counter].value])[counter] = name[counter];
			}
			obj_counter++;
		}
		else if (isdigit(buffer[i]))
		{
			//printf("DIGIT\n");
			obj[obj_counter].type_of_object = NUMBER;
			obj[obj_counter++].value = atoi(&buffer[i]);

			while (isdigit(buffer[i]))
			{
				//printf("number = %d\n", buffer[i]);
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

	//printf("obj_counter = %d\n", obj_counter);

	delete[] buffer;
	//delete[] obj;

	Objects* objs = new Objects[1];

	objs->obj = obj;
	objs->number_of_objects = obj_counter;
	
	for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
		objs->variables_names[i] = variables_names[i];
	//objs->variables_names = variables_names;

	return objs;
}

void print_objects(Objects* object)
{
	assert(object && "U passed nullptr object to print_objects()");
	printf("\n\n");

	for (int i = 0; i < object->number_of_objects; i++)
	{
		switch (object->obj[i].type_of_object)
		{
		case OPERATOR:
			printf("%d. type is OPERATOR, value is %d\n", i, object->obj[i].value);
			break;
		case NUMBER:
			printf("%d. type is NUMBER, value is %d\n", i, object->obj[i].value);
			break;
		case BRACKET:
			printf("%d. type is BRACKET, value is %d\n", i, object->obj[i].value);
			break;
		case VARIABLE:
			printf("%d. type is VARIABLE, value is %d\n", i, object->obj[i].value);
			break;
		case FUNCTION:
			printf("%d. type is FUNCTION, value is %d\n", i, object->obj[i].value);
			break;
		default:
			printf("UNINDENTIFIED TYPE\n");
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
	//bool is_find = false;

	for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
	{
		//printf("name = [%s], ");
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
	}

	for (int i = 0; i < NUMBER_OF_VARIABLES; i++)
	{
		
		delete[] objs->variables_names[i];
		objs->variables_names[i] = nullptr;
	}

	delete[] objs;
	objs = nullptr;
}