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
	line_num = 0;
	context.push(ScopeFrame::Root);
	regex_list = {{"KEYWORD",      regex("speaker|var|set|bg|show|menu|jump|if|fin")},
		      {"IDENT_COLOUR", regex("red|orange|yellow|green|blue|purple|pink")},
		      {"PUNC_OPEN",    regex("[{\\[]")},
		      {"PUNC_CLOSE",   regex("[}\\]]")},
		      {"STRING",       regex("(\\[|\\|)(\\w| )+(\\]|\\|)")},
		      {"SETUP",        regex("setup")},
		      {"WORD",         regex("[a-z]+")}};
	advanceLine(); //just to get started
	//advanceWord();
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

    bool Lexer::advanceLine()
    {
	//try read next line, if returns false we done
	string cur;
	if(std::getline(*file, cur))
	{
	    line_num++;
	    std::cout << "[DEBUG] advline val:" << cur << "\n";
	    cur_line_ss = std::stringstream(cur);
	    return true;
	} else {
	    return false;
	}
    }

    //move ahead one word, line if necessary
    bool Lexer::advanceWord()
    {
	std::cout << "[DEBUG] Advanced a word!\n";
	if(cur_line_ss.eof())
	{
	    if(w == "\n")
	    {
		if(advanceLine())
		{
		    cur_line_ss >> w;
		    return true;
		}
		else
		{
		    //file done
		    return false;
		}
	    }
	    else
	    {
		w = "\n";
		return true;
	    }
	} else {
	    cur_line_ss >> w;
	    return true;
	}

    }

    vector<Token> Lexer::lex()
    {
	while(advanceWord())
	{
	    std::cout << "[DEBUG] w in loop: " << w << std::endl;
	    //if(w == "\n") {}
	    if(context.top() == ScopeFrame::Root)
	    {
		if(std::regex_match(w, regex_list["SETUP"]))
		{
		    std::cout << "[DEBUG] Matched Setup!\n";
		    tokens.push_back(Token {w, "SETUP"});
		    advanceWord();
		    
		    if(w == "\n")
		    {
			std::cout << "[DEBUG] Matched newl!\n";
			advanceWord();
		    }
		    
		    if(std::regex_match(w, regex_list["PUNC_OPEN"]))
		    {
			std::cout << "[DEBUG] Matched punco!\n";
			tokens.push_back(Token {w, "PUNC_OPEN"});
			context.push(ScopeFrame::Setup);
		    }
		    else
		    {
			throw std::runtime_error("[Lexer] No { after setup label");
		    }
		}
		else if(std::regex_match(w, regex_list["WORD"]))
		{
		    tokens.push_back(Token {w, "IDENT"});
		    advanceWord();
		    
		    if(w == "\n")
			advanceWord();
		    
		    if(std::regex_match(w, regex_list["PUNC_OPEN"]))
		    {
			tokens.push_back(Token {w, "PUNC_OPEN"});
			context.push(ScopeFrame::Section);
		    }
		    else
		    {
			throw std::runtime_error("[Lexer] No { after section label");
		    }
		}
		else if(w == "\n")
		{
		}
		else
		{
		    throw std::runtime_error("[Lexer] Unexpected word in root: " + w);
		}
	    }
	    else if(context.top() == ScopeFrame::Section ||
		    context.top() == ScopeFrame::Setup)
	    {
		//check if word is keyword
		if(std::regex_match(w, regex_list["KEYWORD"]))
		{
		    tokens.push_back(Token {w, "KEYWORD"});
		    context.push(ScopeFrame::Keyword);
		}
		//TODO: use speaker lookup table to verify
		else if(std::regex_match(w, regex_list["WORD"]))
		{
		    tokens.push_back(Token {w, "IDENT_SPEAKER"});
		    context.push(ScopeFrame::Speaker);
		}
		else if(w == "}")
		{
		    tokens.push_back(Token {w, "PUNC_CLOSE"});
		    context.pop();
		}
		else if(w == "\n")
		{
		}
		else
		{
		    throw std::runtime_error("[Lexer] Invalid word in Section or Setup: " + w);
		}
	    }
	    else if(context.top() == ScopeFrame::Keyword)
	    {
		if(std::regex_match(w, regex_list["WORD"]))
		{
		    tokens.push_back(Token {w, "ARGUMENT"});
		}
		else if(w == "\n")
		{
		    context.pop();
		}
	    }
	    
	    std::cout << "[DEBUG] Finished one loop!\n";
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
