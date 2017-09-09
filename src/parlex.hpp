#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "ast.hpp"

using std::string;
using std::ifstream;
using std::vector;

namespace Parlex
{
    enum class Category
    {
	KEYWORD,
	IDENTIFIER,
	LITERAL,
	ARGUMENT,
	EOS,
	DELIM_OPEN,
	DELIM_CLOSE,
	DELIM_MID,
	COMPARISON_OPERATOR
    };

    struct Token
    {
	string val;
	Category cat;
    };
    
    class Lexer
    {
    public:
	Lexer(ifstream* _file);
	vector<Token> lex();

    private:
	bool advance();
	bool advance(char c);
	void doSection();
	void doSetup();
	ifstream* file;
	vector<Token> tokens;
	string cur;
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
