#include "pch.h"
#include "CppUnitTest.h"
#include "..\\Shannon–Fano_Coding\Shannon-Fano_Coding.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestShannonFanoCoding
{
	TEST_CLASS(UnitTestShannonFanoCoding)
	{
	public:
		TEST_METHOD(Test_text_processing_one)
		{
			ofstream out("in.txt");
			out << "s";
			out.close();
			L1List* list = text_processing_from_file("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_symbol(), 's');
		}
		TEST_METHOD(Test_code_one)
		{
			ofstream out("in.txt");
			out << "s";
			out.close();
			L1List* list = shannon_fano_code("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_code(), string("1"));
		}
		TEST_METHOD(Test_text_processing_two)
		{
			ofstream out("in.txt");
			out << "su";
			out.close();
			L1List* list = text_processing_from_file("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_symbol(), 's');
			Assert::AreEqual(list->at(1)->get_symbol(), 'u');
		}
		TEST_METHOD(Test_code_two)
		{
			ofstream out("in.txt");
			out << "su";
			out.close();
			L1List* list = shannon_fano_code("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_code(), string("1"));
			Assert::AreEqual(list->at(1)->get_code(), string("0"));
		}
		TEST_METHOD(Test_text_processing_three)
		{
			ofstream out("in.txt");
			out << "ssunnn";
			out.close();
			L1List* list = text_processing_from_file("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_symbol(), 'n');
			Assert::AreEqual(list->at(1)->get_symbol(), 's');
			Assert::AreEqual(list->at(2)->get_symbol(), 'u');
		}

		TEST_METHOD(Test_code_three)
		{
			ofstream out("in.txt");
			out << "ssunnn";
			out.close();
			L1List* list = shannon_fano_code("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_code(), string("1"));
			Assert::AreEqual(list->at(1)->get_code(), string("01"));
			Assert::AreEqual(list->at(2)->get_code(), string("00"));
		}
		TEST_METHOD(Test_text_processing)
		{
			ofstream out("in.txt");
			out << "aaabbbbbccdddd";
			out.close();
			L1List* list = text_processing_from_file("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_symbol(), 'b');
			Assert::AreEqual(list->at(1)->get_symbol(), 'd');
			Assert::AreEqual(list->at(2)->get_symbol(), 'a');
			Assert::AreEqual(list->at(3)->get_symbol(), 'c');
		}
		TEST_METHOD(Test_code)
		{
			ofstream out("in.txt");
			out << "aaabbbbbccdddd";
			out.close();
			L1List* list = shannon_fano_code("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_code(), string("11"));
			Assert::AreEqual(list->at(1)->get_code(), string("01"));
			Assert::AreEqual(list->at(2)->get_code(), string("00"));
			Assert::AreEqual(list->at(3)->get_code(), string("10"));
		}
		TEST_METHOD(Test_text_processing_sentence)
		{
			ofstream out("in.txt");
			out << "the sun will shine soon";
			out.close();
			L1List* list = text_processing_from_file("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_symbol(), ' ');
			Assert::AreEqual(list->at(1)->get_symbol(), 's');
			Assert::AreEqual(list->at(2)->get_symbol(), 'n');
			Assert::AreEqual(list->at(3)->get_symbol(), 'h');
			Assert::AreEqual(list->at(4)->get_symbol(), 'e');
			Assert::AreEqual(list->at(5)->get_symbol(), 'i');
			Assert::AreEqual(list->at(6)->get_symbol(), 'l');
			Assert::AreEqual(list->at(7)->get_symbol(), 'o');
			Assert::AreEqual(list->at(8)->get_symbol(), 't');
			Assert::AreEqual(list->at(9)->get_symbol(), 'u');
			Assert::AreEqual(list->at(10)->get_symbol(), 'w');
		}

		TEST_METHOD(Test_code_sentence)
		{
			ofstream out("in.txt");
			out << "the sun will shine soon";
			out.close();
			L1List* list = shannon_fano_code("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_code(), string("111"));
			Assert::AreEqual(list->at(1)->get_code(), string("011"));
			Assert::AreEqual(list->at(2)->get_code(), string("001"));
			Assert::AreEqual(list->at(3)->get_code(), string("1011"));
			Assert::AreEqual(list->at(4)->get_code(), string("1001"));
			Assert::AreEqual(list->at(5)->get_code(), string("0101"));
			Assert::AreEqual(list->at(6)->get_code(), string("110"));
			Assert::AreEqual(list->at(7)->get_code(), string("000"));
			Assert::AreEqual(list->at(8)->get_code(), string("1010"));
			Assert::AreEqual(list->at(9)->get_code(), string("0100"));
			Assert::AreEqual(list->at(10)->get_code(), string("1000"));
		}

		TEST_METHOD(Test_code_test_string)
		{
			ofstream out("in.txt");
			out << "it is test string";
			out.close();
			L1List* list = shannon_fano_code("in.txt");
			list->print_to_file("out.txt");
			Assert::AreEqual(list->at(0)->get_symbol(), 't');
			Assert::AreEqual(list->at(1)->get_symbol(), 'i');
			Assert::AreEqual(list->at(2)->get_symbol(), ' ');
			Assert::AreEqual(list->at(3)->get_symbol(), 's');
			Assert::AreEqual(list->at(4)->get_symbol(), 'e');
			Assert::AreEqual(list->at(5)->get_symbol(), 'r');
			Assert::AreEqual(list->at(6)->get_symbol(), 'n');
			Assert::AreEqual(list->at(7)->get_symbol(), 'g');
			Assert::AreEqual(list->at(0)->get_code(), string("111"));
			Assert::AreEqual(list->at(1)->get_code(), string("011"));
			Assert::AreEqual(list->at(2)->get_code(), string("001"));
			Assert::AreEqual(list->at(3)->get_code(), string("101"));
			Assert::AreEqual(list->at(4)->get_code(), string("010"));
			Assert::AreEqual(list->at(5)->get_code(), string("100"));
			Assert::AreEqual(list->at(6)->get_code(), string("000"));
			Assert::AreEqual(list->at(7)->get_code(), string("110"));
		}
		TEST_METHOD(Test_code_my)
		{
			ofstream out("in.txt");
			out << "I'm trying to find a sentense that will break my thoughts about the length of the code";
			out.close();
			L1List* list = shannon_fano_code("in.txt");
			list->print_to_file("out.txt");
		}


		TEST_METHOD(Test_decode_test_string)
		{
			string filename = "out.txt";
			string input = "it is test string";
			ofstream out(filename);
			out << input;
			out.close();
			L1List* list = shannon_fano_code(filename);
			string coded_text = code_from_file(list, filename);
			out.open(filename);
			out << coded_text;
			out.close();
			string decoded_text = decode_from_file(list, filename);
			Assert::AreEqual(input, decoded_text);
		}
		TEST_METHOD(Test_decode_test_char)
		{
			string filename = "out.txt";
			string input = "s";
			ofstream out(filename);
			out << input;
			out.close();
			L1List* list = shannon_fano_code(filename);
			string coded_text = code_from_file(list, filename);
			out.open(filename);
			out << coded_text;
			out.close();
			string decoded_text = decode_from_file(list, filename);
			Assert::AreEqual(input, decoded_text);
		}
		TEST_METHOD(Test_decode_test_two_letters)
		{
			string filename = "out.txt";
			string input = "it is test string";
			ofstream out(filename);
			out << input;
			out.close();
			L1List* list = shannon_fano_code(filename);
			string coded_text = code_from_file(list, filename);
			out.open(filename);
			out << coded_text;
			out.close();
			string decoded_text = decode_from_file(list, filename);
			Assert::AreEqual(input, decoded_text);
		}

		TEST_METHOD(Test_decode_test_two_sentece)
		{
			string filename = "out.txt";
			string input = "The sun will shine soon!";
			ofstream out(filename);
			out << input;
			out.close();
			L1List* list = shannon_fano_code(filename);
			string coded_text = code_from_file(list, filename);
			out.open(filename);
			out << coded_text;
			out.close();
			string decoded_text = decode_from_file(list, filename);
			Assert::AreEqual(input, decoded_text);
		}
	};
}
