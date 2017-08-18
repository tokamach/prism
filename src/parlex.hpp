#include <string>
#include <fstream>
#include "ast.hpp"

using std::string;
using std::ifstream;

// Script parser
class Parser
{
public:
    ifstream parseFile;

    //Finite State Machine variables
    bool inSetup;
    bool inLabel;
    std::string labelName;
    char expectingChar;

    //parse from string for now, add files later
    Parser(const char *filename);

    AST parse();
    string expect(char expecting);
//  AST parseFile(const *char filename);

private:
    parseStep(AST* workTree, string workString);
};
