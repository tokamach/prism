#include "parlex.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include <iostream>
#include <stack>
#include <map>

#include "ast.hpp"

using std::string;
using std::stringstream;
using std::ifstream;
using std::vector;
using std::regex;
using std::stack;
using std::map;

namespace Parlex
{
    Lexer::Lexer(ifstream* _file)
    {
	file = _file;
	context.push(ScopeFrame::Root);
	regex_list = {{"KEYWORD",      regex("speaker|var|set|bg|show|menu|jump|if|fin")},
		      {"IDENT_COLOUR", regex("red|orange|yellow|green|blue|purple|pink")},
		      {"PUNC_OPEN",    regex("[{\\[]")},
		      {"PUNC_CLOSE",   regex("[}\\]]")},
		      {"STRING",       regex("(\\[|\\|)(\\w| )+(\\]|\\|)")},
		      {"SETUP",        regex("setup")},
		      {"WORD",         regex("[a-z]+")}};
    }

    void Lexer::back()
    {
	file->unget();
    }

    void Lexer::back(int n)
    {
	for(int i = 0; i < n; i++)
	{
	    file->unget();
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
	//move ahead one line
	//TODO: move to pure word based
	while(advanceLine())
	{
	    //streamify line and do word by word
	    //TODO: internalize this to the class
	    stringstream ss(cur);
	    do
	    {
		string w;
		ss >> w;

		if(context.top == ScopeFrame::Root)
		{
		    if(std::regex_match(w, r["SETUP"]))
		    {
			tokens.push_back(Token {w, "SETUP"});
		    }
		    else if(std::regex_match(w, r["WORD"]))
		    {
			tokens.push_back(Token {w, "IDENT"});
		    }
		    else if(std::regex_match(w, r["PUNC_OPEN"]))
		    {
			tokens.push_back(Token {w, "PUNC_OPEN"});
			contex.push(ScopeFrame::Setup;)
		    }
		}

		if(context.top == ScopeFrame::Section ||
		   context.top == ScopeFrame::Setup)
		{
		    //check if word is keyword
		    if(std::regex_match(w, r["KEYWORD"]))
		    {
			if() {
			    tokens.push_back(Token {w, "KEYWORD"});
			    break;
			} else {
			    throw "[LEXER] Keyword used in wrong context";
			}
		    }
		}
	    } while (ss);
	}
	return tokens;
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
