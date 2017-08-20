#include <string>
#include <fstream>
#include <vector>
#include "parlex.hpp"
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

    vector<Token> Lexer::lex()
    {
	const char delimiters[] = {' ', '\n', '{', '['};
	char c;

	do {
	    c = file.get();
	} while (c != ' '  &&
	         c != '\n' &&
	         c != '{'  &&
	         c != '[')
	
    }
    
    Parser::Parser(vector<LexerToken> tokVec)
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
