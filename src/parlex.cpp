#include "parlex.hpp"

#include <string>
#include <fstream>
#include <vector>

#include "ast.hpp"

using std::string;
using std::ifstream;
using std::vector;

namespace Parlex
{
    Lexer::Lexer(ifstream _file)
    {
	file = _file;
    }

    Token Lexer::doLine(string str)
    {

    }

    Lexer::until(char c)
    {
	char next;
//	while()
    }

    vector<Token> Lexer::lex()
    {
	const char delimiters[] = {' ', '\n', '{', '['};
	char c;
	string str;
	bool done = false;;

	do {
	    while (1) {
		c = file.get();
		
		if(c != ' '  &&
		   c != '\n' &&
		   c != '{'  &&
		   c != '[') {
		    str.append(c);
		}
	    }

	    //done = true;
	} while (!done)
    }
    
    Parser::Parser(vector<Token> tokVec)
    {
	
    }
    
    *AST Parser::parse()
    {
	AST *tree = new AST();
	
	while(parseString.find('\n') != string::npos)
	{
	    //get a single line to work on
	    int index = parseString.find('\n');
	    string workLine = parseString.substr(0, index);
	    
	    parseStep(&tree, workLine);
	    
	    //chomp off parsed line
	    parseString = parseString.substr(index);
	}
    }
}
