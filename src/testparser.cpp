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

void printNode(Node node, int indent = 0)
{
    for(auto arg : node.args)
    {
	// add indent based on current tree depth
	std::cout << std::string(indent, ' ') << arg.first << " : " << arg.second << "\n";
    }

    //if we have children print them
    if(!node.block.empty())
    {
	for(auto child : node.block)
	    printNode(child, indent + 1);
    }
}

int main()
{
    // read file
    ifstream *f = new ifstream("test.txt");

    // attempt to lex file f into token vector v
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

    //print token vector
    std::cout << "Lexer output:" << std::endl;
    for(auto t : v)
    {
	std::cout << t.val << " : " << m[t.cat] << std::endl;
    }


    //create parser from token vec and parse into AST var
    Parlex::Parser p(v);
    AST* ast;
    ast = p.parse();

    //print AST
    std::cout << std::endl << "Parser output:" << std::endl;

    //print setup block real quick
    std::cout << "Setup Block:\n";
    for (auto node : ast->setup.block)
    {
	std::cout << "Node : " << nodeNameMap[node.type] << "\n";
	for (const auto &arg : node.args)
	    std::cout << " - " << arg.first << " : " << arg.second << "\n";
	std::cout << "\n";
    }

    //print each section
    std::cout << "Section Blocks:\n";
    for (auto section : ast->sections)
    {
	//recur print child nodes of section
	printNode(section);
    }
}
