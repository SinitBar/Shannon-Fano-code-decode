// Shannon–Fano_Coding.cpp : Определяет функции для статической библиотеки.
//
#pragma once
#include "framework.h"
#include "Shannon-Fano_Coding.h"

L1List* text_processing_from_file(string filename)
{
	ifstream in(filename);
	if (!in.is_open())
		throw new invalid_argument("the data file doesn't exist");
	L1List* list = new L1List();
	// не заходим в while wtf
	while (in.peek() != EOF)
	{
		char now_char = in.get();
		if (list->isEmpty())
			list->push_back(new Element(now_char, 1));
		else
		{
			Element* current = list->search_on_symbol(now_char);
			if (current != nullptr)
				current->plus_appearance(1);
			else
				list->push_back(new Element(now_char, 1));
		}
	}
	in.close();
	// now we want to sort from biggest to smaller by appearence
	list->merge_sort_by_appearance(0, list->get_size() - 1);
	return list;
}

void shannon_fano_code_from_list(unsigned int* index_array, unsigned int size, L1List* list)
{
	if (size == 1)
		return;
	unsigned int left_sum = 0, right_sum = 0, count_left = 0, count_right = 0; // elements in tree that goes to right are marked by 0, to left - by 1
	unsigned int* splited = new unsigned int[size];
	for (unsigned int i = 0; i < size; i++)
	{
		if (left_sum <= right_sum) // adding element to the left
		{ // adding in splited in straight order
			splited[i - count_right] = index_array[i];
			count_left++;
			left_sum += list->at(index_array[i])->get_appearance();
			list->write_end_of_code(index_array[i], "1");
		}
		else // adding element to the right
		{// adding in splited in reverse order to save this part sorted
			for (unsigned int j = size - 1 - count_right; j < size - 1; j++) // shifting right elements on one to the left
				splited[j] = splited[j + 1];
			splited[size - 1] = index_array[i]; // adding element like last
			right_sum += list->at(index_array[i])->get_appearance();
			list->write_end_of_code(index_array[i], "0");
			count_right++;
		}
	}
	// now we have an array where in the left part indexses of elements of the left branch
	// we going to add next number to the codes by recursive calls
	shannon_fano_code_from_list(splited, count_left, list);
	shannon_fano_code_from_list(&splited[count_left], size - count_left, list);
}

L1List* shannon_fano_code(string filename) // when read from file
{
	L1List* list = text_processing_from_file(filename);
	if (list->get_size() == 1)
	{
		list->write_end_of_code(0, "1");
		return list;
	}
	unsigned int* index_array = new unsigned int[list->get_size()];
	for (unsigned int i = 0; i < list->get_size(); i++)
		index_array[i] = i;
	shannon_fano_code_from_list(&index_array[0], list->get_size(), list);
	return list;
}

string decode_from_file(L1List* list, string filename) // list with chars and their codes, name of the file
{ // file "filename" contains code to decode
	ifstream in(filename);
	if (!in.is_open())
		throw new invalid_argument("read from not-existing file");
	string decoded_text = "";
	// we are going to find min length of the code
	Element* current = list->get_head();
	unsigned int min_code_length = current->get_code().size();
	while (current != nullptr)
	{
		if (current->get_code().size() < min_code_length)
			min_code_length = current->get_code().size();
		current = current->get_next();
	}
	// processing input
	while (in.peek() != EOF)
	{
		string supposed_code = ""; // get from console
		for (unsigned i = 0; i < min_code_length; i++)
			supposed_code += char(in.get());
		current = list->get_head();
		while (current != nullptr)
		{
			string part_of_current_code = current->get_code();
			if (supposed_code.size() < part_of_current_code.size())
				part_of_current_code = part_of_current_code.substr(0, supposed_code.size());
			while ((supposed_code == part_of_current_code) && (part_of_current_code != current->get_code()))
			{ // if we found similar part it is the searched code or supposed code should be longer
				supposed_code += char(in.get());
				part_of_current_code += current->get_code()[part_of_current_code.size()];
			}
			if (supposed_code == current->get_code())
			{
				decoded_text += current->get_symbol();
				break;
			}
			current = current->get_next();
		}
		if (current == nullptr)
			throw new out_of_range("char by code not found");	
	}
	return decoded_text;
}

string code_from_file(L1List* list, string filename)
{ // file "filename" contains some text to code
	ifstream in(filename);
	if (!in.is_open())
		throw new invalid_argument("read from not-existing file");
	string coded_text = "";
	while (in.peek() != EOF)
	{
		Element* now = list->search_on_symbol(in.get());
		coded_text += now->get_code();
	}
	return coded_text;
}

void console_program() // user-session
{
	string filename = "out.txt";
	cout << "write some text to code:" << endl;
	ofstream out(filename);
	while (cin.peek() != '\n')
	{
		char now_char = cin.get();
		out << now_char;
	}
	out.close();
	L1List* list = shannon_fano_code(filename);
	string coded_text = code_from_file(list, filename);
	cout << endl << "coded text: " << endl;
	cout << coded_text << endl;
	out.open(filename);
	out << coded_text;
	out.close();
	cout << "decoded text: \n" << decode_from_file(list, filename) << endl;
	Element* current = list->get_head();
	unsigned int original_memory = 0;
	cout << "table of frequences and codes:" << endl;
	while (current != nullptr)
	{
		original_memory += current->get_appearance();
		cout << "symbol = " << current->get_symbol() << ", frequency = " 
			<< current->get_appearance() << ", code = " << current->get_code() << endl;
		current = current->get_next();
	}
	const int bites_in_byte = 8;
	cout << "original memory size = " << original_memory*sizeof(char)* bites_in_byte << " bit" << endl;
	cout << "zipped memory size = " << coded_text.size() << " bit" << endl;
	cout << "compression ratio = " << (double)coded_text.size() / (original_memory * sizeof(char) * 8.0) << endl;
}

int main()
{
	console_program();
	return 0;
}