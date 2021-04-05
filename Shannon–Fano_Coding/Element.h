#include <iostream>
#include <stdexcept>
using namespace std;
class Element
{
	Element* next;
	string code = ""; // Shannon-Fano code of the symbol
	char symbol;
	unsigned int appearance_times = 0; // how many times current sybol was in the text
	void set_next(Element*);
	void set_symbol(char);
	void set_appearance(unsigned int);
	void set_code(string);
	Element(); // to forbid creating with uncknown symbol
public:
	Element(char);
	Element(char, unsigned int);
	void plus_appearance(unsigned int); // pluses to appearence_times data number
	unsigned int get_appearance();
	string get_code();
	char get_symbol();
	friend class L1List;
	Element* get_next();
	~Element();
};