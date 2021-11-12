#include "dif.h"
#include "tree.h"

int main(int argc, int argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	FILE* text = fopen("text.txt", "r");
	//fopen_s(&text, "text.txt", "rb");

	assert(text && "Can't open text.txt file");


	Objects* objs = fill_structures(text);

	//Objects* obj = objs->obj;

	//print_objects(objs);

	tree dif_tree("main_differenciator");

	dif_tree.fill_tree(objs, true);

	//char* formula = dif_tree.get_formula(dif_tree.get_root());
	//delete[] formula;
	//printf("elements = %d\n", hm_elements(dif_tree.get_root()) );



	dif_tree.make_article();

	printf("Successfull complete\n");
	return 0;
}