#include "parlex.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include <utility>
#include <iostream>

#include "ast.hpp"

using std::string;
using std::stringstream;
using std::ifstream;
using std::vector;
using std::regex;
using std::pair;

namespace Parlex
{
    Lexer::Lexer(ifstream* _file)
    {
	file = _file;
	regex_sub_list = {{regex("speaker|var|set|bg|show|menu|jump|if|fin"), "KEYWORD"},
	                  {regex("red|orange|yellow|green|blue|purple|pink"), "IDENTIFIER_COLOUR"},
			  {regex("[{}\\[\\]\\|]"), "PUNCTUATION"},
			  {regex("(\\[|\\|)(\\w| )+(\\]|\\|)"), "STRING"},
	                  {regex("[a-z]+"), "IDENTIFIER"}};
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
	while(advance())
	{
	    stringstream ss(cur);
	    do
	    {
		string w;
		ss >> w;

		std::cout << w ;

		for(auto r : regex_sub_list)
		{
		    if(std::regex_match(w, r.first))
		    {
			tokens.push_back(Token {w, r.second});
			break;
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
