#pragma once
#include "Element.h"
Element::Element()
{
	symbol = ' ';
	code = "";
	appearance_times = 0;
	next = nullptr;
}
Element::Element(char new_symbol)
{
	symbol = new_symbol;
	code = "";
	appearance_times = 0;
	next = nullptr;
}
Element::Element(char new_symbol, unsigned int times)
{
	symbol = new_symbol;
	code = "";
	appearance_times = times;
	next = nullptr;
}
Element* Element::get_next() { return next; }
void Element::set_next(Element* new_element) { next = new_element; }
void Element::set_symbol(char new_symbol) { symbol = new_symbol; }
void Element::set_code(string new_code) { code = new_code; }
void Element::set_appearance(unsigned int new_appearance) { appearance_times = new_appearance; }
void Element::plus_appearance(unsigned int times)
{ appearance_times += times; }
unsigned int Element::get_appearance() { return appearance_times; }
string Element::get_code() { return code; }
char Element::get_symbol() { return symbol; }
Element::~Element() { }