#pragma once
#include "L1List.h"

L1List* text_processing_from_file(string); // reading from file, parameter = filename
void shannon_fano_code_from_list(unsigned int*, unsigned int, L1List*);
L1List* shannon_fano_code(string); // when read from file
string code_from_file(L1List*, string);
string decode_from_file(L1List*, string);
void console_program(); // user-session