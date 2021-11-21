#include "tree.h"

tree_element::tree_element(data_type data, tree_element* prev, tree_element* left, tree_element* right) :
	data_(data),
	prev_(prev),
	left_(left),
	right_(right)
{
	assert(this && "You passed nullptr to list_elem construct");
}

tree_element::~tree_element()
{
	assert(this && "You passed nullptr to ~tree_element");
	data_ = POISON;

	prev_ = nullptr;
	left_ = nullptr;
	right_ = nullptr;

    if (user_data_)
    {
        delete[] user_data_;
        user_data_ = nullptr;
    }

}

tree::tree(const char* name) :
	cur_size_(0),
	error_state_(0),
	name_(name),
	root_(nullptr),
    buffer_(nullptr)
{
	assert(this && "You passed nullptr to constructor");
	assert(name && "You need to pass name");
}

tree::~tree()
{
	assert(this && "nullptr in desctructor");

    assert(root_);

    if (root_)
        root_->free_all();

    if (buffer_)
    {
        delete[] buffer_;
        buffer_ = nullptr;
    }

	cur_size_ = -1;
	error_state_ = -1;
	name_ = nullptr;
	root_ = nullptr;
}

void tree_element::free_all()
{
    assert(this);

    if (get_left())
        left_->free_all();
    if (get_right())
        right_->free_all();

    if (user_data_)
        delete[] user_data_;
  
    if (this)
        free(this);

    return;
}

tree_element* tree::add_to_left(tree_element* x, data_type number)
{
	assert(this && "You passed nullptr tree");

    tree_element* tmp = new tree_element;
	assert(tmp && "Can't calloc memory for tree_element");

    if((x == nullptr) && (cur_size_ == 0))
    {
        root_ = tmp;

    	tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        cur_size_++;
    }
    else if(cur_size_ && tmp)
    {
        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        cur_size_++;

        x->set_left(tmp);
	}
	else
        printf("You must pass x\n");

	return tmp;
}

tree_element* tree::add_to_right(tree_element* x, data_type number)
{
	assert(this && "You passed nullptr tree");

    tree_element* tmp = new tree_element;
	assert(tmp && "Can't calloc memory for tree_element");

    if((x == nullptr) && (cur_size_ == 0))
    {
        root_ = tmp;

    	tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);
       
        cur_size_++;
    }
    else if(cur_size_)
    {
        tmp->set_prev(x);
        tmp->set_right(nullptr);
        tmp->set_left(nullptr);
        tmp->set_data(number);

        x->set_right(tmp);

        cur_size_++;
	}
	else
        printf("You must pass x\n");

	return tmp;
}

void tree::print_tree_info() const
{
    graphviz_dump("dump.dot");

    system("iconv.exe -t UTF-8 -f  CP1251 < dump.dot > dump_temp.dot");
    system("dot dump_temp.dot -Tpdf -o dump.pdf");
    system("del dump.dot");
    system("ren dump_temp.dot dump.dot");
    system("dump.pdf");

	return;
}

void tree::graphviz_dump(const char* dumpfile_name) const
{
    assert(dumpfile_name && "You passed nullptr dumpfile_name");

    FILE* dump = fopen(dumpfile_name, "wb");
    assert(dump && "Can't open dump.dot");

    fprintf(dump, "digraph %s {\n", name_);
    fprintf(dump, "node [color = Red, fontname = Courier, style = filled, shape=record, fillcolor = purple]\n");
    fprintf(dump, "edge [color = Blue, style=dashed]\n");

    tree_element* tmp = root_;

	print_all_elements(tmp, dump);
    fprintf(dump, "}\n");

    fclose(dump);

    return;
}

void tree::show_tree() const
{
    graphviz_beauty_dump("beauty_tree.dot");

    system("iconv.exe -t UTF-8 -f  CP1251 < beauty_tree.dot > beauty_tree_temp.dot");
    system("dot beauty_tree_temp.dot -Tpdf -o beauty_dump.pdf");
    system("del beauty_tree.dot");
    system("ren beauty_tree_temp.dot beauty_tree.dot");

    system("beauty_dump.pdf");

    return;
}

void tree::graphviz_beauty_dump(const char* dumpfile_name) const
{
    assert(dumpfile_name && "You passed nullptr dumpfile_name");

    FILE* dump = fopen(dumpfile_name, "wb");
    assert(dump && "Can't open dump.dot");

    fprintf(dump, "digraph %s {\n", name_);
    fprintf(dump, "node [color = Red, fontname = Courier, style = filled, shape=ellipse, fillcolor = purple]\n");
    fprintf(dump, "edge [color = Blue, style=dashed]\n");

    tree_element* root = root_;

    print_all_elements_beauty(root, dump);
    fprintf(dump, "}\n");

    fclose(dump);
    return;
}

void tree::fill_tree(const char* name_file)
{
	assert(this && "you passed nullptr to fill_tree");
	assert(name_file && "U need to pas FILE* database");

    buffer_ = make_buffer(name_file);
    char* copy_of_buffer = buffer_;

    while (*buffer_ != '[');
        buffer_++;

    root_ = fill_root();

    if (root_)
        build_prev_connections(root_);

    buffer_ = copy_of_buffer;

	return;
}

void tree_element::build_prev_connections(tree_element* root)
{
    assert(root);

    if(root->get_right())
    {
        if( ((root->get_right())->get_left() == nullptr) && ((root->get_right())->get_right() == nullptr) )
            (root->get_right())->set_prev(root);
        else
        {
            (root->get_right())->set_prev(root);
            build_prev_connections(root->get_right());
        }
    }
    if(root->get_left())
    {
        if( ((root->get_left())->get_left() == nullptr) && ((root->get_left())->get_right() == nullptr) )
            (root->get_left())->set_prev(root);
        else
        {
            (root->get_left())->set_prev(root);
            build_prev_connections(root->get_left());
        }
    }
}

tree_element* tree::fill_root()
{
    while(isspace(*buffer_))
        buffer_++;

    if (*buffer_ == '[')
        buffer_++;

    while(isspace(*buffer_))
        buffer_++;

    tree_element* tmp_element = new tree_element;
    assert(tmp_element && "Can't calloc mempry for tmp");

    if((*buffer_ == '`') || (*buffer_ == '?'))
    {
        buffer_++;

        int lenght = 0;
        while((*buffer_ != '?') && (*buffer_ != '`'))
        {
            lenght++;
            buffer_++;
        }

        
        buffer_ -= lenght;
        
        tmp_element->data_ = buffer_;
        tmp_element->length_ = lenght;

        buffer_ += lenght;

        tmp_element->set_left(nullptr);
        tmp_element->set_right(nullptr);
        tmp_element->set_prev(nullptr);

        while(isspace(*buffer_))
            buffer_++;

        if(*buffer_ == '?') 
        {
            buffer_++;

            tmp_element->set_left(fill_root());
            tmp_element->set_right(fill_root());
        }
    }

    buffer_++;

    while(isspace(*buffer_))
        buffer_++;
  
    if (*buffer_ == ']')
    {
        buffer_++;
        return tmp_element;
    }
    else
    {
        printf("Something bad..\n");
        return nullptr;
    }
}

void print_all_elements(tree_element* tmp, FILE* dump)
{
    assert(tmp && "tmp is nullptr in print_all_elements");

    if (tmp->get_right())
    {
        print_all_elements(tmp->get_right(), dump);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Да\", fontcolor=darkblue]\n", tmp, tmp->get_right());
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Да\", fontcolor=darkblue]\n", tmp->get_right(), (tmp->get_right())->get_prev());
    }
    if (tmp->get_left())
    {
        print_all_elements(tmp->get_left(), dump);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Нет\", fontcolor=darkblue]\n", tmp, tmp->get_left());
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Нет\", fontcolor=darkblue]\n", tmp->get_left(), (tmp->get_left())->get_prev());
    }


    if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
        fprintf(dump, "\"%p\" [label = \"<f0> value = [%.*s]|{<f1> left| <here> prev| right}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = lightgreen] \n", tmp, tmp->length_, tmp->non_const_get_data(), tmp->get_left(), tmp->get_prev(), tmp->get_right());
    else
        if (tmp->get_prev() == nullptr)
            fprintf(dump, "\"%p\" [label = \"{<f0> value = [%.*s] |<here> [%p]}|{<f1> right| <here> prev| left}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = red] \n", tmp, tmp->length_, tmp->non_const_get_data(), tmp, tmp->get_left(), tmp->get_prev(), tmp->get_right());
        else
            fprintf(dump, "\"%p\" [label = \"{<f0> value = [%.*s] |<here> [%p]}|{<f1> right| <here> prev| left}| {<f2> [%p]| [%p]| [%p]}\",style = filled, fillcolor = purple] \n", tmp, tmp->length_, tmp->non_const_get_data(), tmp, tmp->get_left(), tmp->get_prev(), tmp->get_right());


    return;

}

void print_all_elements_beauty(tree_element* tmp, FILE* dump)
{
    assert(tmp && "tmp is nullptr in print_all_elements");

    if (tmp->get_right())
    {
        print_all_elements_beauty(tmp->get_right(), dump);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Да\", fontcolor=darkblue]\n", tmp, tmp->get_right());
    }
    if (tmp->get_left())
    {
        print_all_elements_beauty(tmp->get_left(), dump);
        fprintf(dump, "\"%p\" -> \"%p\" [label=\"Нет\", fontcolor=darkblue]\n", tmp, tmp->get_left());
    }

    if ((tmp->get_right() == nullptr) && (tmp->get_left() == nullptr))
        fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = lightgreen] \n", tmp, tmp->length_, tmp->non_const_get_data());
    else
        if (tmp->get_prev() == nullptr)
            fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = red] \n", tmp, tmp->length_, tmp->non_const_get_data());
        else
            fprintf(dump, "\"%p\" [label = \"%.*s\",style = filled, fillcolor = purple] \n", tmp, tmp->length_, tmp->non_const_get_data());
    return;
}

tree_element* create_root(char* data, tree_element* left, tree_element* right, tree_element* prev)
{
    tree_element* root = new tree_element;

    root->set_left(left);

    if (left)
        left->set_prev(root);

    root->set_right(right);

    if (right)
        right->set_prev(root);

    root->set_data(data);
    root->set_prev(prev);


    root->user_length_ = strlen(root->data_);
    root->length_ = root->user_length_;


    return root;
}
