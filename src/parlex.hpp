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

    enum class TokenType
    {
	Setup,
	Ident_Section,

	Keyword,
	Ident_Speaker,
	Arg,
	Arg_Image,
	Dialouge_String,
	Img_Path,
	Word,

	Punc_Open,
	Punc_Mid,
	Punc_Close,

	Punc_Open_Menu,
	Punc_Mid_Menu,
	Punc_Close_Menu
    };

    struct Token
    {
	std::string val;
	TokenType cat;
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
	std::vector<Token> tokens;
    };
    
}
