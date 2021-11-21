#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <TXLib.h>
#include "list_info.h"


using data_type = double;
#define POISON NAN

class list_element
{
private:

	data_type 	  data_ = 0;
	list_element* next_ = nullptr;
	list_element* prev_ = nullptr;

public:

	list_element(data_type data = 0, list_element* next = nullptr, list_element* prev = nullptr);
	~list_element();

//! SETTERS

	void set_data(data_type new_data) {data_ = new_data;};
	void set_next(list_element* new_next) {next_ = new_next;};
	void set_prev(list_element* new_prev) {prev_ = new_prev;};

    data_type& non_const_get_data() {assert(this && "You passed nullptr to get_data()"); return data_;};

    list_element* get_next() {assert(this && "nullptr list_element in get_next()"); return next_;};
    list_element* get_prev() {assert(this && "nullptr list_element in get_prev()"); return prev_;};


//! GETTERS

	const data_type& get_data()     const {assert(this && "You passed nullptr to get_data()"); return data_;};

	const list_element* get_next()  const {assert(this && "nullptr list_element in get_next()"); return next_;};
	const list_element* get_prev()  const {assert(this && "nullptr list_element in get_prev()"); return prev_;};


};




class list:list_element
{
private:

	size_t cur_size_ 	= 0;
	size_t error_state_ = 0;
	const char* name_ 	= nullptr;

	list_element* start_ = nullptr;
	list_element* end_ 	 = nullptr;

public:

	list(const char* name);
	~list();

//! SETTERS

	void set_start(list_element* start) {start_ = start;};
	void set_end(list_element* end) {end_ = end;};

// * MAIN SETTERS

	list_element* set_element_from_end(data_type number);
	list_element* set_element_to_start(data_type number);
	list_element* set_element_prev_to_x(list_element* x, data_type number);

// * MAIN SETTERS

	data_type& non_const_get_data_from_element(list_element* element) {assert(this && "You passed nullptr list");  return element->non_const_get_data();};
	data_type& operator[] (list_element* element) {return non_const_get_data_from_element(element);};

    list_element* get_start() {return start_;};
	list_element* get_end() {return end_;};

//! GETTERS

	const void print_list(bool need_graphviz_dump = false)
									const;
    const void graphviz_dump(char* dumpfile_name) const;

	const size_t get_cur_size()     const {return cur_size_;};
	const size_t get_error_state()  const {return error_state_;};

	const data_type& get_data_from_element (list_element* element)
                                    const {assert(this && "You passed nullptr list");  return element->get_data();};

	const data_type& operator[](list_element* element)
                                    const {return get_data_from_element(element);};

	const char* get_name()          const {return name_;};

	const list_element* get_start() const {return start_;};
	const list_element* get_end()   const {return end_;};

	const bool is_start(const list_element* element)
									const {assert(element && "You passed nullptr element to is_start()"); assert(this && "You passed nullptr list to is_start()"); return (element == start_);};
	const bool is_end(const list_element* element)
									const {assert(element && "You passed nullptr element to is_start()"); assert(this && "You passed nullptr list to is_start()"); return (element == end_);};

};

void graphviz_dump(char* dumpfile_name);

#define CONSTRUCT(name)	\
	list name(#name);


#endif // LIST_H_INCLUDED
