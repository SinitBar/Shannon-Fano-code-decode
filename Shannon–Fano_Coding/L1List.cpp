#pragma once
#include "L1List.h"
L1List::L1List()
{
	head = nullptr;
	tail = nullptr;
}
Element* L1List::get_head() { return head; }
Element* L1List::get_tail() { return tail; }
void L1List::set_head(Element* head_element) { head = head_element; }
void L1List::set_tail(Element* tail_element) { tail = tail_element; }
void L1List::set_next(Element* now_element, Element* next_element) { now_element->set_next(next_element); }
//static void L1List::set_symbol(Element* now_element, char new_symbol) { now_element->symbol = new_symbol; }
Element* L1List::get_next(Element* now_element) { return (now_element->get_next()); }
char L1List::get_symbol(Element* now_element) { return (now_element->symbol); }

void L1List::write_end_of_code(unsigned int index, string code_end)
{ 
	if (index >= get_size())
		throw new invalid_argument("Invalid index");
	at(index)->code += code_end; 
}

bool L1List::isEmpty()
{
	if (head != nullptr)
		return false; // list is not empty
	return true;
}

void L1List::push_back(Element* new_element)
{
	if (isEmpty())
		head = tail = new_element;
	else
	{
		tail->set_next(new_element);
		tail = tail->get_next();
	}
}

void L1List::push_front(Element* new_element)
{
	if (isEmpty())
		head = tail = new_element;
	else
	{
		Element* current = new_element; // cur = new elem
		current->set_next(head); // cur->next = head
		head = current; // head = cur
	}
}

void L1List::pop_back()
{
	Element* current = get_head();
	if (!isEmpty())
	{
		if (get_next(current) == nullptr) // delete head
		{
			Element* element_to_delete = head;
			current = head = tail = nullptr;
			delete element_to_delete;
		}
		else
		{
			while (get_next(current)->get_next() != nullptr) // while cur->next->next exists
			{
				current = get_next(current); // cur = cur->next
			} // cur = the element before the last existing element
			Element* element_to_delete = get_next(current);
			current->set_next(nullptr);
			tail = current;
			delete element_to_delete;
		}
	}
	else
		throw out_of_range("The List is empty");
}

void L1List::pop_front()
{
	Element* current = get_head();
	if (!isEmpty())
	{
		if (get_next(current) == nullptr) // delete head
		{
			Element* element_to_delete = head;
			head = current = tail = nullptr;
			delete element_to_delete;
		}
		else
		{
			Element* element_to_delete = head;
			current = head->get_next();// cur = head->next
			set_head(current); // head = cur
			delete element_to_delete;
		}
	}
	else
		throw out_of_range("The List is empty");
}

unsigned int L1List::get_size()
{
	unsigned int List_size = 0;
	Element* current = get_head();
	if (!isEmpty())
	{
		List_size = 1;
		while (get_next(current) != nullptr) // while cur->next exists
		{
			current = get_next(current); // cur = cur->next
			List_size++;
		} // cur = last existing element
	}
	return List_size;
}

void L1List::insert(Element* new_element, unsigned int index) // first index = 0
{
	if (index == get_size())
		push_back(new_element);
	else if (index == 0)
		push_front(new_element);
	else if (index > get_size())
		throw out_of_range("Invalid index");
	else
	{
		Element* current = get_head(); // now = head
		while (index > 1)
		{
			index--;
			current = get_next(current); // cur = cur->next
		} // cur is the element before the future new element
		new_element->set_next(get_next(current)); //e->next = cur->next
		set_next(current, new_element); // cur->next = e
	}
}

Element* L1List::at(unsigned int index) // first index = 0
{
	if (index >= get_size())
		throw out_of_range("Invalid index");
	else if (index == 0)
		return head;
	else
	{
		Element* current = head;
		while (index > 0)
		{
			index--;
			current = get_next(current); // cur = cur->next
		} // cur is the element with data index
		return current;
	}
}

void L1List::remove(unsigned int index)
{
	if (index >= get_size())
		throw out_of_range("Invalid index");
	else if (index == 0) // delete head
		pop_front();
	else if (index == get_size() - 1)
		pop_back();
	else
	{
		Element* current = head;
		while (index > 1)
		{
			index--;
			current = get_next(current); // cur = cur->next
		} // cur is the element before the deleting element
		Element* element_to_delete = new Element;
		element_to_delete = get_next(current);
		set_next(current, element_to_delete->get_next()); //cur->next = cur->next->next
		if (element_to_delete == nullptr)
			tail = current;
		delete element_to_delete;
	}
}

void L1List::print_to_console()
{
	if (isEmpty())
		throw new invalid_argument("can't print empty list");
	Element* current = get_head(); // now = head
	while (current != nullptr)
	{
		cout << "symbol = " << get_symbol(current) << ", appearence_times = " << current->get_appearance() << ", code = " << current->get_code() << endl;
		current = get_next(current); // cur = cur->next
	}
}

void L1List::print_to_file(string filename)
{
	ofstream out(filename);
	if (isEmpty())
		throw new invalid_argument("can't print empty list");
	Element* current = get_head(); // now = head
	while (current != nullptr)
	{
		out << "symbol = " << get_symbol(current) << ", appearence_times = " << current->get_appearance() << ", code = " << current->get_code() << endl;
		current = get_next(current); // cur = cur->next
	}
}

void L1List::clear()
{
	if (!isEmpty())
	{
		Element* current = get_head(); // cur = head
		while (get_next(current) != nullptr) // while next exists
		{
			current = get_next(current); // cur = cur->next
			delete get_head();
			set_head(current); // head = cur

		} //cur - the last in the list
		Element* element_to_delete = get_head();
		head = current = tail = nullptr;
		delete element_to_delete;
	}
	else
		throw exception("The List is empty");
}

void L1List::set(unsigned int index, char new_symbol) // change data on index element
{
	if (index >= get_size())
		throw out_of_range("Invalid index");
	else if (index == 0)
		head->symbol = new_symbol;
	else if (index == get_size() - 1)
		tail->symbol = new_symbol;
	else
	{
		Element* current = get_head(); // now = head
		while (index > 0)
		{
			index--;
			current = get_next(current); // cur = cur->next
		} // cur is the element with data index
		current->symbol = new_symbol;
	}
}

void L1List::push_front(L1List* L) // insertion another list into the begining of data
{
	if (!L->isEmpty())
	{
		push_front(L->get_head()); // first in this is the same as the first in L now
		Element* head_element = head; // now head is a new element because that's how my push_front works
		Element* L_cur = L->get_head();
		while (L->get_next(L_cur) != nullptr) // while cur->next exists
		{
			L_cur = L->get_next(L_cur);
			insert(L_cur, 1);
			head = head->get_next(); // head is an inserted element - this is made for next iteration
		}
		set_head(head_element);
	}
}

Element* L1List::search_on_symbol(char s_symbol)
{ // SPECIALLY returns nullptr when searched for not-existing symbol
	if (isEmpty())
		throw new out_of_range("search in empty list");
	Element* current = get_head();
	while (current != nullptr)
	{
		if (current->symbol == s_symbol)
			return current;
		current = current->get_next();
	}
	return current;
}

void L1List::merge_sort_by_appearance(unsigned int start_index, unsigned int end_index)
{
	if (start_index == end_index)
		return;
	unsigned int middle_index = (start_index + end_index) / 2;
	merge_sort_by_appearance(start_index, middle_index);
	merge_sort_by_appearance(middle_index + 1, end_index);
	unsigned int left_index = start_index;
	unsigned int right_index = middle_index + 1;
	L1List* merge_list = new L1List();
	while ((left_index < middle_index + 1) && (right_index < end_index + 1))
	{
		if (at(left_index)->get_appearance() >= at(right_index)->get_appearance())
		{
			Element* new_element = new Element(this->at(left_index)->get_symbol(), this->at(left_index)->get_appearance());
			merge_list->push_back(new_element);
			left_index++;
		}
		else
		{
			Element* new_element = new Element(this->at(right_index)->get_symbol(), this->at(right_index)->get_appearance());
			merge_list->push_back(new_element);
			right_index++;
		}
	}
	while (left_index < middle_index + 1)
	{
		Element* new_element = new Element(this->at(left_index)->get_symbol(), this->at(left_index)->get_appearance());
		merge_list->push_back(new_element);
		left_index++;
	}
	while (right_index < end_index + 1)
	{
		Element* new_element = new Element(this->at(right_index)->get_symbol(), this->at(right_index)->get_appearance());
		merge_list->push_back(new_element);
		right_index++;
	}
	Element* current = at(start_index); // for going through elements of the original list
	Element* current_merged = merge_list->at(0);
	for (int i = 0; i <= end_index - start_index; i++)
	{
		current->set_symbol(current_merged->get_symbol());
		current->set_appearance(current_merged->get_appearance());
		//current->set_code(current_merged->get_code());
		current = current->get_next();
		current_merged = current_merged->get_next();
	}
}

L1List::~L1List()
{
	if (!isEmpty())
		clear();
}