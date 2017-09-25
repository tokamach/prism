#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>
#include <stack>
#include <map>

#include "ast.hpp"

namespace Parlex
{
    enum class ScopeFrame
    {
	Setup,
	Section,
	Keyword,
	Menu,
	Speaker,
	Root,
	None
    };

    struct Token
    {
	std::string val;
	std::string cat;
    };
    
    class Lexer
    {
    public:
	Lexer(std::ifstream* _file);
	std::vector<Token> lex();
	int line_num;

    private:
	bool advanceLine();
	bool advanceWord();

	std::ifstream* file;
	std::stringstream cur_line_ss;
	std::string w;

	std::vector<Token> tokens;
	std::map<std::string, std::regex> regex_list;
	std::stack<ScopeFrame> context;
    };
    
    class Parser
    {
    public:
	Parser(std::vector<Token> tokVec);
	AST* parse();

    private:
	
    };
    
}
