#include <iostream>
#include <fstream>
#include <vector>

#include "parlex.hpp"

using std::ifstream;
using std::vector;

int main()
{
    ifstream *f = new ifstream("test.txt");
    Parlex::Lexer l(f);
    vector<Parlex::Token> v;
    try
    {
	v = l.lex();
    }
    catch(std::runtime_error ex)
    {
	std::cout << "[ERROR]" << ex.what()
		  << " on line: " << l.line_num
		  << std::endl;
	return 1;
    }

    for(auto t : v)
    {
	std::cout << t.val << std::endl;
    }
}
