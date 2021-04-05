#pragma once
#include "Element.h"
#include <fstream>
class L1List
{
	Element* head = nullptr;
	Element* tail = nullptr;
	void set_head(Element*);
	void set_tail(Element*);
	void set_next(Element*, Element*); // change next regarding to cur 
	//static void set_symbol(Element*, char); // chage cur data
public:
	L1List();
	Element* get_head();
	Element* get_tail();
	char get_symbol(Element*); // get cur data
	Element* get_next(Element*); // get next regarding to cur
	bool isEmpty(); // check for empty list
	void push_back(Element*); // adding to the end of the list
	void push_front(Element*); // adding to the begining of the list
	void pop_back(); // delete last element
	void pop_front(); // delete first element
	unsigned int get_size(); // get size of the list
	void insert(Element*, unsigned int); // adding element on index (before the element, that had this index lately)
	Element* at(unsigned int); // return element on index
	void remove(unsigned int); // delete element on index
	void print_to_console(); // print elements to console without using at()
	void print_to_file(string filename = "out.txt"); // print all to file
	void clear(); // delete all elements of the list
	void set(unsigned int, char); // change data of element on index
	void push_front(L1List*); // insertion another list into begining of the data-list
	Element* search_on_symbol(char); // finds element with data symbol
	void merge_sort_by_appearance(unsigned int, unsigned int); // sorts list by appearence from bigger to smaller
	void write_end_of_code(unsigned int, string); // write data string to the end of the code of the element with data index
	~L1List();

};