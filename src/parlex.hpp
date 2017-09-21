#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <utility>

#include "ast.hpp"

using std::string;
using std::ifstream;
using std::vector;
using std::regex;
using std::pair;

namespace Parlex
{
    struct Token
    {
	string val;
	string cat;
    };
    
    class Lexer
    {
    public:
	Lexer(ifstream* _file);
	vector<Token> lex();

    private:
	bool advance();
	bool advance(char c);
	void back();
	void back(int n);

	ifstream* file;
	vector<Token> tokens;
	string cur;
	vector<pair<regex, string>> regex_sub_list;
    };
    
    class Parser
    {
    public:
	//Finite State Machine variables
	bool inSetup;
	bool inLabel;
	std::string labelName;
	
	Parser(vector<Token> tokVec);
	
	AST* parse();
    };
    
}
