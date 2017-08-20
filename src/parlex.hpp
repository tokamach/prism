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
	ARGUMENT,
	EOS,
	DELIM_OPEN,
	DELIM_CLOSE,
	DELIM_MID,
	COMPARISON_OPERATOR
    }

    class Token
    {
	string val;
	Category cat;

	Token(string _val, Category _cat)
	{
	    val = _val;
	    cat = _cat;
	}
    };
    
    class Lexer
    {
    public:
	Lexer(ifstream _file);
	vector<Token> lex();

    private:
	ifstream file;
	string curString;
	void next();
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
