#include <string>
#include <fstream>
#include "parlex.hpp"
#include "ast.hpp"

using std::string;
using std::ifstream;

Parser::Parser(const char *filename)
{
    parseFile.open(filename);
}

//seek through file until find an instance of char
string Parser::expect(char expecting)
{
    std::string ret;
    std::getline(parseFile, ret, expecting);
    return ret;
}

AST Parser::parseStep(AST *workTree, string workString)
{

}

AST Parser::parse()
{
    AST tree = new AST();

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
