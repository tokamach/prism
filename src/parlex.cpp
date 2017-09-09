#include "parlex.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "ast.hpp"

using std::string;
using std::ifstream;
using std::vector;

namespace Parlex
{
    Lexer::Lexer(ifstream* _file)
    {
	file = _file;
    }

    void Lexer::doSection()
    {
	
    }

    void Lexer::doSetup()
    {
	advance();
	tokens.push_back(Token {cur, Category::IDENTIFIER});
	advance();
	tokens.push_back(Token {cur, Category::DELIM_OPEN});

	advance();
	while(cur != "}")
	{
	    tokens.push_back(Token {cur, Category::KEYWORD});
	    advance(' ');
	}
    }

    bool Lexer::advance()
    {
	//try read next line, if returns false we done
	if(std::getline(*file, cur))
	{
	    return true;
	} else {
	    return false;
	}
    }

    bool Lexer::advance(char c)
    {
	if(std::getline(*file, cur, c))
	{
	    return true;
	} else {
	    return false;
	}
    }

    vector<Token> Lexer::lex()
    {
//	doSetup();
	advance('{');
	std::cout << cur;
    }
    
    Parser::Parser(vector<Token> tokVec)
    {
	
    }
    
    AST* Parser::parse()
    {
	AST *tree = new AST();

	return tree;
    }
}
