
#include "tree.h"
#include "PL_func.h"


int main()
{
	bool debug_state = false;
	bool beauty_state = true;
	get_config(debug_state, beauty_state);

	printf("Hello in my PL!\n");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	FILE* text = fopen("text.txt", "r");
	assert(text && "Can't open text.txt file");
	
	Objects* objs = fill_structures(text);
	fclose(text);


	tree PL_tree("PL_TREE");

	PL_tree.fill_tree(objs, debug_state, beauty_state);

	PL_tree.create_asm_text_file(debug_state);

	printf("DONE!\n");
	
	if (debug_state)
	{
		print_objects(objs);
		system("Pause");
	}

	return 0;
}