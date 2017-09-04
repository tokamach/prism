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
    }

    struct Token
    {
	string val;
	Category cat;
    };
    
    class Lexer
    {
    public:
	Lexer(ifstream _file);
	vector<Token> lex();

    private:
	void advance();
	ifstream file;
	string curLine;
//      void next();
    };
    
    class Parser
    {
    public:
	//Finite State Machine variables
	bool inSetup;
	bool inLabel;
	std::string labelName;
	
	Parser(vector<LexerToken> tokVec);
	
	*AST parse();
    };
    
}
