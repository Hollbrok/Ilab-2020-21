#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "akinator_config.h"

#define POISON nullptr

using data_type = char*;
const int MAX_QUESTION_SIZE = 30;


/* Debug memory allocation support */
#ifndef NDEBUG 
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h> 

#define SetDbgMemHooks()                                           \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))      

static class __Dummy
{
public:
	/* Class constructor */
	__Dummy(VOID)
	{
		SetDbgMemHooks();
	} /* End of '__Dummy' constructor */
} __ooppss;
#endif /* _DEBUG */ 

#ifndef NDEBUG
#  ifdef _CRTDBG_MAP_ALLOC 
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#  endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */


#define NDEBUG
#ifndef NDEBUG
#define VERIFICATION                                                           \
{                                                                              \
  if (verification()) {                                                        \
    fprintf(stderr, "LINE: %d\nFILE:%s\nFUNC:%s"__LINE__, __FILE__, __func__); \
    assert(0);                                                                 \
  }                                                                            \
}                                                                               
#else
#define VERIFICATION ;
#endif /* _DEBUG */


class tree_element
{
private:

	tree_element* prev_ = nullptr;

	tree_element* left_  = nullptr;
	tree_element* right_ = nullptr;

public:

    data_type 	  data_ = 0;
	size_t		length_ = 0;

	data_type user_data_ = 0;
	size_t	user_length_ = 0;

// * Constr and Deconstr
   
	tree_element(data_type data = 0, tree_element* prev = nullptr,
                tree_element* left = nullptr, tree_element* right = nullptr);
	
	~tree_element();

	void free_all();

// *


//! SETTERS

	void set_data(data_type new_data) {data_ = new_data;};
	void set_user_data(data_type new_data) { user_data_ = new_data; };
	
	void set_left(tree_element* new_left) {left_ = new_left;};
	void set_right(tree_element* new_right) {right_ = new_right;};

	void set_prev(tree_element* new_prev) {prev_ = new_prev;};


//! CONST GETTERS

	const data_type&	get_data()  const {assert(this && "You passed nullptr to get_data()"); return data_;};

	const tree_element* get_left()  const {assert(this && "nullptr tree_element in get_next()"); return left_;};
	const tree_element* get_right() const {assert(this && "nullptr tree_element in get_next()"); return right_;};
	const tree_element* get_prev()  const {assert(this && "nullptr tree_element in get_prev()"); return prev_;};

//! NON_CONST GETTERS

 	data_type non_const_get_data() {assert(this && "You passed nullptr to get_data()"); return data_;};

    tree_element* get_left()  {assert(this && "nullptr tree_element in get_next()"); return left_;};
	tree_element* get_right() {assert(this && "nullptr tree_element in get_next()"); return right_;};
	tree_element* get_prev()  {assert(this && "nullptr tree_element in get_prev()"); return prev_;};

//! OTHER
	
	void build_prev_connections(tree_element* root);

    void print_elem(FILE* database);

    bool get_user_answer();

	bool* get_attributes_massive(char* word, int &cur_size, bool* attributes);

	void get_attributes(char* word);

	bool find_word(char* word);

	void compare_attributes(bool* attr1, int size1, bool* attr2, int size2, char* obj1, char* obj2);

	char* get_question_from_massive(bool* attributes, int size);
};

class tree:tree_element
{
private:

	size_t cur_size_ 	= 0;
	size_t error_state_ = 0;
	const char* name_ 	= nullptr;

	tree_element* root_  = nullptr;

	char* buffer_ = nullptr;

public:

// * Constr and Deconstr

	tree(const char* name);
	~tree();

// *

// * ADDERS

	tree_element* add_to_right(tree_element* x, data_type number);
	tree_element* add_to_left(tree_element* x, data_type number);


//! GETTERS

	tree_element* get_root() {return root_;};

//! FILL TREE FUNCTIONS

	void fill_tree(const char* name_file);

	void update_database(const char* name_file);

	tree_element* fill_root();

// * PLAY

    void play_1();
	void play_2();
	void play_3();
	void play_4();


    void play();

	void graphic_play();



//! GRAPHVIZ DUMP

	void print_tree_info()
		const;

	void graphviz_dump(const char* dumpfile_name = "dump.dot")
		const;

	void graphviz_beauty_dump(const char* dumpfile_name)
		const;

	void show_tree() const;

};

//! For dump

void print_all_elements(tree_element* tmp, FILE* dump);
void print_all_elements_beauty(tree_element* tmp, FILE* dump);

//! Make buffer

long size_of_file(FILE *user_code);
char* make_buffer(const char* name_file);


//! Console play

void print_hello();
void check_answer(tree_element* question);
int get_number_of_game();
char* get_data_from_user();

tree_element* create_root(char* data, tree_element* left = nullptr, tree_element* right = nullptr, tree_element* prev = nullptr);

//void free_all(tree_element* root);

#endif // TREE_H_INCLUDED
