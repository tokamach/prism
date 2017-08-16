#include "ast.hpp"

// Script parser
class Parser
{
    Parser(const *char rawStr);

    AST parse(const *char rawStr);
    AST parseFile(const *char filename);
};
