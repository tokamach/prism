#include "parlex.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include <iostream>
#include <stack>
#include <map>
#include <iterator>

#include "ast.hpp"

using std::string;
using std::stringstream;
using std::ifstream;
using std::vector;
using std::regex;
using std::stack;
using std::map;

namespace Parlex
{
    Lexer::Lexer(ifstream* _file)
    {
	file = _file;
	line_num = 0;
	context.push(ScopeFrame::Root);
	regex_list = {{"KEYWORD",      regex("speaker|var|set|bg|show|menu|jump|if|fin")},
		      {"PUNC_OPEN",    regex("[{\\[]")},
		      {"PUNC_MID",     regex("\\|")},
		      {"PUNC_CLOSE",   regex("[}\\]]")},
		      {"IMG_PATH",     regex("[a-z\\/]+")},
		      {"WORD",         regex("[A-Za-z]+")}};
	advanceLine(); //just to get started
    }

    bool Lexer::advanceLine()
    {
	//try read next line, if returns false we done
	string cur;
	if(std::getline(*file, cur))
	{
	    line_num++;
	    cur_line_ss = std::stringstream(cur);
	    return true;
	} else {
	    return false;
	}
    }

    //move ahead one word, line if necessary
    bool Lexer::advanceWord()
    {
	if(cur_line_ss.eof())
	{
	    if(w == "\n")
	    {
		if(advanceLine())
		{
		    cur_line_ss >> w;
		    return true;
		}
		else
		{
		    //file done
		    return false;
		}
	    }
	    else
	    {
		w = "\n";
		return true;
	    }
	} else {
	    cur_line_ss >> w;
	    return true;
	}

    }

    vector<Token> Lexer::lex()
    {
	while(advanceWord())
	{
	    switch(context.top())
	    {
	    case ScopeFrame::Root:
		if(w == "setup")
		{
		    tokens.push_back(Token {w, TokenType::Setup});
		    advanceWord();
		    
		    if(w == "\n")
		    {
			advanceWord();
		    }
		    
		    if(std::regex_match(w, regex_list["PUNC_OPEN"]))
		    {
			tokens.push_back(Token {w, TokenType::Punc_Open});
			context.push(ScopeFrame::Setup);
		    }
		    else
		    {
			throw std::runtime_error("[Lexer] No { after setup label");
		    }
		}
		else if(std::regex_match(w, regex_list["WORD"]))
		{
		    tokens.push_back(Token {w, TokenType::Ident_Section});
		    advanceWord();
		    
		    if(w == "\n")
			advanceWord();
		    
		    if(std::regex_match(w, regex_list["PUNC_OPEN"]))
		    {
			tokens.push_back(Token {w, TokenType::Punc_Open});
			context.push(ScopeFrame::Section);
		    }
		    else
		    {
			throw std::runtime_error("[Lexer] No { after section label");
		    }
		}
		else if(w == "\n")
		{
		}
		else
		{
		    throw std::runtime_error("[Lexer] Unexpected word in root: " + w);
		}
		break;
		
	    case ScopeFrame::Section:
	    case ScopeFrame::Setup:
		//check if word is keyword
		if(std::regex_match(w, regex_list["KEYWORD"]))
		{
		    tokens.push_back(Token {w, TokenType::Keyword});
		    context.push(ScopeFrame::Keyword);
		}
		//TODO: use speaker lookup table to verify
		else if(std::regex_match(w, regex_list["WORD"]))
		{
		    tokens.push_back(Token {w, TokenType::Ident_Speaker});
		    context.push(ScopeFrame::Speaker);
		}
		else if(w == "}")
		{
		    tokens.push_back(Token {w, TokenType::Punc_Close});
		    context.pop();
		}
		else if(w == "\n")
		{
		}
		else
		{
		    throw std::runtime_error("[Lexer] Invalid word in Section or Setup: " + w);
		}
		break;
		
	    case ScopeFrame::Keyword:
		if(std::regex_match(w, regex_list["WORD"]))
		{
		    tokens.push_back(Token {w, TokenType::Arg});
		}
		else if(std::regex_match(w, regex_list["IMG_PATH"]))
		{
		    tokens.push_back(Token {w, TokenType::Arg_Image});
		}
		else if(std::regex_match(w, regex_list["PUNC_OPEN"]))
		{
		    tokens.push_back(Token {w, TokenType::Punc_Open_Menu});
		    context.push(ScopeFrame::Menu);
		}
		else if(w == "\n")
		{
		    context.pop();
		}
		break;
		
	    case ScopeFrame::Speaker:
		if(w != "\n")
		{
		    tokens.push_back(Token {w, TokenType::Dialogue_String});
		}
		else
		{
		    context.pop();
		}
		break;
		
	    case ScopeFrame::Menu:
		if(w == "|")
		{
		    tokens.push_back(Token {w, TokenType::Punc_Mid_Menu});
		    advanceWord();
		    tokens.push_back(Token {w, TokenType::Ident_Section});
		}
		else if(std::regex_match(w, regex_list["PUNC_CLOSE"]))
		{
		    tokens.push_back(Token {w, TokenType::Punc_Close_Menu});
		    advanceWord();
		    if(w == "\n")
			advanceWord();
		    
		    if(std::regex_match(w, regex_list["PUNC_OPEN"]))
		    {
			tokens.push_back(Token {w, TokenType::Punc_Open_Menu});
		    }
		    else
		    {
			context.pop();
			context.pop(); //twice to return from both menu and keyword frames
		    }
		}
		else
		{
		    tokens.push_back(Token {w, TokenType::Dialogue_String});
		}

		break;
	    }
	}
	return tokens;
    }
    
    Parser::Parser(vector<Token> tokVec)
    {
	this->tokens = tokVec;
	t = tokens.begin();
	tree = new AST();
    }

    void Parser::parseSection()
    {
	//pseudo:
	//move to, check, then eat the PUNC_OPEN token (t++)
	//do while until token is PUNC_CLOSE
	//  ensure token is KEYWORD
	//    switch on t->val for different keyword type
	//      t++ and add each arg according to keyword type


	//add section node, with arg "label" as sections label
	tree->sections.push_back(Node{NodeType::Section, {}, {{"label", t->val}}});

	t++; //advance to punc
	if(t->cat == TokenType::Punc_Open)
	{
	    t++; //eat punc
	    while (t->cat != TokenType::Punc_Close)
	    {
		if(t->cat == TokenType::Keyword)
		{
		    //can't switch on strings, so if else chain
		    if(t->val == "bg")
		    {
			t++; //eat keyword
			string img = t->val; //bg img pseudopath
			tree->sections.back().block.push_back(Node{NodeType::Bg, {},
				{{"path", img}}});
			t++; //eat pseudopath
		    }
		    else if (t->val == "show")
		    {
			t++;
			string img = t->val;
			tree->sections.back().block.push_back(Node{NodeType::Show, {},
				{{"path", img}}});
			t++;
		    }
		    else if (t->val == "fin")
		    {
			t++;
			string msg;
			while(t->cat == TokenType::Arg)
			{
			    msg += t->val;
			    t++;
			}
			tree->sections.back().block.push_back(Node{NodeType::Fin, {},
				{{"message", msg}}});
		    }
		    else if (t->val == "jump")
		    {
			t++;
			string label = t->val;
			tree->sections.back().block.push_back(Node{NodeType::Jump, {},
				{{"target", label}}});
			t++;
		    }
		    else if (t->val == "set")
		    {
			t++;
			string var = t->val;
			t++;
			string value = t->val;
			tree->sections.back().block.push_back(Node{NodeType::Set, {},
				{{"var", var},
				 {"val", value}}});
			t++;
		    }
		    else if (t->val == "if")
		    {
			//TODO: implement if
		    }
		    else if (t->val == "none")
		    {
			//TODO: you know this actually is never lexed
		    }
		    else if (t->val == "menu")
		    {
			//TODO: check for all cases and throw errors when appropriate
			//TODO: let menu have more than two options in parse

			t++; //eat keyword
			t++; //eat punc_open_menu

			// fill first menuText arg
			string menuTextA;
			while(t->cat == TokenType::Dialogue_String)
			{
			    //TODO: don't just randomly space pad end, do it smart
			    menuTextA += t->val + " ";
			    t++;
			}

			t++; //eat punc_mid_menu
			string menuLabelA = t->val; // set jump label A
			t++;

			t++;
			t++; //eat punc close and open

			// fill second menuText arg
			string menuTextB;
			while(t->cat == TokenType::Dialogue_String)
			{
			    //TODO: don't just randomly space pad end, do it smart
			    menuTextB += t->val + " ";
			    t++;
			}

			t++; //eat punc_mid_menu
			string menuLabelB = t->val; // set jump label A

			// temp use args instead of node block
			tree->sections.back().block.push_back(Node{NodeType::Menu, {},
				   {{"label_a", menuLabelA},
				    {"text_a", menuTextA},
				    {"label_b", menuLabelB},
				    {"text_b", menuTextB}}});

			t++;
			t++; // eat jump label and PUNC_END
		    }
		    else
		    {
			//TODO: tell us which keyword
			std::cout << "[DEBUG ERROR SPEW] bad keyword is: " << t->val << "\n";
			throw std::runtime_error("[Parser] invalid keyword in section");
		    }
		}
		else if(t->cat == TokenType::Ident_Speaker)
		{
		    string speaking = t->val;
		    t++;
		    
		    string speech;
		    while(t->cat == TokenType::Dialogue_String)
		    {
			//TODO: don't just randomly space pad end, do it smart
			speech += t->val + " ";
			t++;
		    }

		    tree->sections.back().block.push_back(Node{NodeType::Speaker, {},
			    {{"name", speaking},
			     {"speech", speech}}});
		}
		else
		{
		    std::cout << "[DEBUG ERROR SPEW] bad token val is: " << t->val << "\n";
		    throw std::runtime_error("[Parser] unexpected non-keyword in section");
		}
	    }
	}
	else
	    throw std::runtime_error("[Parser] section label not followed by '{'");

	t++; //eat final PUNC_CLOSE
    }

    void Parser::parseSetup()
    {
	tree->setup = Node{NodeType::Setup, {}, {}};

	t++; //advance to punc
	if(t->cat == TokenType::Punc_Open)
	{
	    t++; //eat punc
	    do
	    {
		if(t->cat == TokenType::Keyword)
		{
		    //only check for speaker and var since we in setup
		    //TODO: add speaker to character name table, for use in parsing
		    if(t->val == "speaker")
		    {
			t++;
			string a = t->val;
			t++;
			string n = t->val;
			t++;
			string c = t->val;
			tree->setup.block.push_back(Node {NodeType::SpeakerSetup, {},
				{{"alias", a},
				 {"name" , n},
				 {"color", c}}});
			t++;
		    }
		    else if (t->val == "var")
		    {
			//TODO: parse for optional inital value
			t++;
			string name = t->val;
			tree->setup.block.push_back(Node {NodeType::Var, {}, {{"name", name}}});

			t++;
		    }
		}
		else
		    throw std::runtime_error("[Parser] unexpected non-keyword in setup block");
	    } while (t->cat != TokenType::Punc_Close);

	    t++;
	}
    }
    
    AST* Parser::parse()
    {
	if(t->cat == TokenType::Setup)
	{
	    parseSetup();

	    while(t->cat == TokenType::Ident_Section)
		parseSection();

	    //else throw std::runtime_error("[Parser] non label after setup block");
	}
	else throw std::runtime_error("[Parser] tokl did not start in setup block");

	return tree;
    }
}
