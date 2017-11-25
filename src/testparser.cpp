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

std::map<NodeType, std::string> nodeNameMap =
{
    {NodeType::Setup, "Setup"},
    {NodeType::Section, "Section"},
    {NodeType::Speaker, "Speaker"},
    {NodeType::SpeakerSetup, "SpeakerSetup"},
    {NodeType::Bg, "Bg"},
    {NodeType::Show, "Show"},
    {NodeType::Fin, "Fin"},
    {NodeType::Jump, "Jump"},
    {NodeType::Var, "Var"},
    {NodeType::Set, "Set"},
    {NodeType::Menu, "Menu"},
    {NodeType::If, "If"},
    {NodeType::None, "None"}
};

void printTree(AST *ast, int indent = 0)
{

    for (auto node : ast->sections)
    {
	
    }
}

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

    //print setup block real quick
    for (auto node : ast->setup.block)
    {
	std::cout << "Node type: " << nodeNameMap[node.type] << "\n";
	for (const auto &arg : node.args)
	    std::cout << " - " << arg.first << " : " << arg.second << "\n";
	std::cout << "\n";
    }

    //print full tree
    printTree(ast);
}
