#pragma once

#include <string>
#include <list>

//TODO: macroize this whole step

enum class NodeType
{
    Setup,
    Section,
    Speaker,
    SpeakerSetup,
    Bg,
    Show,
    Fin,
    Jump,
    Var,
    Set,
    Menu,
    If,
    Data
};

struct Node
{
    NodeType type;
    std::list<Node> block;
    std::map<std::string, std::string> args;
};

class AST 
{
public:
    Node setup;
    std::list<Node> sections;

    AST() { }
};

/*
// Root level nodes
struct NodeSetup : public Node
{
    list<Node*> block;
};

struct NodeSection : public Node
{
    string label;
    list<Node> block;
};

// Keyword nodes
struct NodeSpeakerSetup : Node
{
    string alias;
    string name;
    string color;
};

struct NodeSpeaker : public Node
{
    string value;
};

struct NodeBg : public Node
{
    string value;
};

struct NodeShow : public Node
{
    string value;
};

struct NodeFin : public Node
{
//    NodeFin() { }
};

// Logic nodes
struct NodeJump : public Node
{
    string value;
};

struct NodeVar : public Node
{
    string label;
    string optValue;
};

struct NodeSet : public Node
{
    string label;
    string value;
};

//TODO: sort this proper
struct NodeMenu : public Node
{
    string value;
    list<Node> block;
};

struct NodeIf : public Node
{
    string var1;
    string var2;
    string conditional;
};

struct NodeNone : public Node
{
    NodeNone() { }
};
*/
