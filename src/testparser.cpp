#include <iostream>
#include <fstream>
#include <vector>

#include "parlex.hpp"
#include "ast.hpp"

using std::ifstream;
using std::vector;

std::map<Parlex::TokenType, std::string> m =
{
    {Parlex::TokenType::Arg, "Arg"},
    {Parlex::TokenType::Arg_Image, "Arg_Image"},
    {Parlex::TokenType::Dialogue_String, "Dialogue_String"},
    {Parlex::TokenType::Ident_Section, "Ident_Section"},
    {Parlex::TokenType::Ident_Speaker, "Ident_Speaker"},
    {Parlex::TokenType::Img_Path, "Img_Path"},
    {Parlex::TokenType::Keyword, "Keyword"},
    {Parlex::TokenType::Punc_Close, "Punc_Close"},
    {Parlex::TokenType::Punc_Close_Menu, "Punc_Close_Menu"},
    {Parlex::TokenType::Punc_Open, "Punc_Open"},
    {Parlex::TokenType::Punc_Open_Menu, "Punc_Open_Menu"},
    {Parlex::TokenType::Punc_Mid, "Punc_Mid"},
    {Parlex::TokenType::Punc_Mid_Menu, "Punc_Mid_Menu"},
    {Parlex::TokenType::Setup, "Setup"},
    {Parlex::TokenType::Word, "Word"}
};

int main()
{
    ifstream *f = new ifstream("test.txt");
    vector<Parlex::Token> v;

    Parlex::Lexer l(f);

    try
    {
	v = l.lex();
    }
    catch(std::runtime_error ex)
    {
	std::cout << "[ERROR]"    << ex.what()
		  << " on line: " << l.line_num
		  << std::endl;
	return 1;
    }

    std::cout << "Lexer output:" << std::endl;
    for(auto t : v)
    {
	std::cout << t.val << " : " << m[t.cat] << std::endl;
    }

    Parlex::Parser p(v);
    AST* ast;
    ast = p.parse();

    std::cout << std::endl << "Parser output:" << std::endl;

    //TODO: walk ast and pretty print
}
