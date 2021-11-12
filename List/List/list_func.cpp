#include "list.h"

list::list(const char* name) :
	cur_size_(0),
	error_state_(0),
	name_(name),
	start_(nullptr),
	end_(nullptr)
{
	assert(this && "You passed nullptr list to construct");
	assert(name && "You passed nullptr name to construct");
	//printf("in %s\n", __PRETTY_FUNCTION__);

}

list::~list()
{
	assert(this && "You passed nullptr to destruct");
	//printf("in %s\n", __PRETTY_FUNCTION__);


// * May be make all free, but class must call ~list_element

	list_element* tmp = nullptr;
	for (tmp = end_; (end_ != nullptr) && (tmp->get_prev() != nullptr); )
    {
        //printf("free memory in ~list\n", tmp->get_prev());
        tmp = tmp->get_prev();

        free(tmp->get_next());
        tmp->set_next(nullptr);
    }

    free(tmp); 		// free start element


	cur_size_    = -1;
	error_state_ = -1;

	//free(name_);
	name_ = nullptr;

	start_ = nullptr;
	end_ = nullptr;
}

list_element::list_element(data_type data, list_element* next, list_element* prev) :
	data_(data),
	next_(next),
	prev_(prev)
{
	//printf("in %s\n", __PRETTY_FUNCTION__);
	assert(this && "You passed nullptr to list_elem construct");
}

list_element::~list_element()
{
	assert(this && "You passed nullptr to ~list_element");
	//printf("in %s\n", __PRETTY_FUNCTION__);
	free(next_);
	next_ = nullptr;
	free(prev_);
	prev_ = nullptr;
	data_ = POISON;
}

list_element* list::set_element_from_end(data_type number)
{
	assert(!isnan(number) && "number is nan");
	assert(this && "You passed nullptr to set_element_from_end");

	list_element* tmp = (list_element*) calloc (1, sizeof(list_element));

	if((start_ == nullptr) && (end_ == nullptr))  // cur_size_ == 0
	{
		tmp->set_data(number);
		tmp->set_next(nullptr);
		tmp->set_prev(nullptr);

		set_start(tmp);
		set_end(tmp);
	}
	else
	{
		tmp->set_data(number);
		tmp->set_prev(get_end());
		tmp->set_next(nullptr);

		(get_end())->set_next(tmp);

		set_end(tmp);
	}

	cur_size_++;

	return tmp;
}

list_element* list::set_element_to_start(data_type number)
{
	assert(!isnan(number) && "number is nan");
	assert(this && "You passed nullptr to set_element_from_start");

	list_element* tmp = (list_element*) calloc (1, sizeof(list_element));

	if((start_ == nullptr) && (end_ == nullptr))  // cur_size_ == 0
	{
		tmp->set_data(number);
		tmp->set_next(nullptr);
		tmp->set_prev(nullptr);

		set_start(tmp);
		set_end(tmp);
	}
	else
	{
		tmp->set_data(number);
		tmp->set_prev(nullptr);
		tmp->set_next(get_start());

		(get_start())->set_prev(tmp);

		set_start(tmp);
	}

	cur_size_++;

	return tmp;
}

list_element* list::set_element_prev_to_x(list_element* x, data_type number)
{
	assert(this && "You passed nullptr list to set_element_prev_to_x");
	assert(x && "You passed nullptr x element");

	list_element* tmp = (list_element*) calloc(1, sizeof(list_element));

	if(is_start(x))
	{
		set_start(tmp);

		x->set_prev(tmp);
		tmp->set_next(x);

		tmp->set_data(number);
	}
	else
	{
		(x->get_prev())->set_next(tmp);

		tmp->set_next(x);
		tmp->set_prev(x->get_prev());
		tmp->set_data(number);
	}

	cur_size_++;

	return tmp;
}

const void list::print_list(bool need_graphviz_dump) const
{
	if(need_graphviz_dump)
	{
        //char* dumpfile_name = "dump.dot";
        graphviz_dump("dump.dot");
        system("dot dump.dot -Tpdf -o dump_list.pdf");
        system("dump_list.pdf");
// or   system("dot dump.dot -Tpng -o dump_list.png"); // if u want [.png] format
	}

	FILE* txt_dump = fopen("dump.txt", "wb");
	assert(txt_dump && "Can't open dump.txt");

	size_t counter = 0;

    const list_element* tmp = get_start();

    if(tmp == nullptr)
    {
        fprintf(txt_dump, "List if empty");
        return;
    }

    fprintf(txt_dump, "START_ELEMENT: [%d]: [%lg] -> ", ++counter, tmp->get_data());
    tmp = tmp->get_next();

	for(tmp; !is_end(tmp); tmp = tmp->get_next())
		fprintf(txt_dump, "[%d]: [%lg] -> ", ++counter, tmp->get_data());

    fprintf(txt_dump, "END_ELEMENT: [%d]: [%lg].\n", ++counter, tmp->get_data());
    fprintf(txt_dump, "SIZE: [%d]\nNAME: [%s]\nERROR_STATE: [%d]", cur_size_, name_, error_state_);

	return;
}

const void list::graphviz_dump(char* dumpfile_name) const
{
    assert(dumpfile_name && "You passed nullptr dumpfile_name");

    FILE* dump = fopen(dumpfile_name, "wb");
    assert(dump && "Can't open dump.dot");

    fprintf(dump, "digraph %s {\n", name_);
    fprintf(dump, "node [color=Red,fontname=Courier,shape=record]\n");
    fprintf(dump, "edge [color=Blue, style=dashed]\n");
    fprintf(dump, "rankdir=LR\n");

    size_t counter = 1;
    const list_element* tmp = get_start();
    fprintf(dump, "%d [label =\"<f0> value = [%lg]|{<f1> next| <here> prev}| {<f2> [%ld]| START}\"];\n", counter, tmp->get_data(), tmp->get_next());

    counter++;
    tmp = tmp->get_next();
    for(tmp; !is_end(tmp); (tmp = tmp->get_next()) && counter++)
        fprintf(dump, "%d [label =\"<f0> value = [%lg]|{<f1> next| <here> prev}| {<f2> [%ld]| [%ld]}\"];\n", counter, tmp->get_data(), tmp->get_next(), tmp->get_prev());

    fprintf(dump, "%d [label =\"<f0> value = [%lg]|{<f1> next| <here> prev}| {<f2> [%ld]| END}\"];\n", counter, tmp->get_data(), tmp->get_prev());

    tmp = get_start();
    counter = 1;

    for(tmp; !is_end(tmp); tmp = tmp->get_next())
    {
        fprintf(dump, "%d -> %d [color=blue,penwidth=2.0];\n", counter, counter + 1);
        fprintf(dump, "%d -> %d [color=blue,penwidth=2.0];\n", counter + 1, counter);
        counter++;
    }
    fprintf(dump, "}");
    fclose(dump);

    return;
}
