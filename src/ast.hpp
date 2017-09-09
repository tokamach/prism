#pragma once

#include <string>
#include <list>

using std::string;
using std::list;

//TODO: macroize this whole step

struct Node
{
//  Node next;
//  Node() { };
};

struct NodeSetup : public Node
{
    list<Node> block;
};

struct NodeLabel : public Node
{
    string label;
    list<Node> block;
};

struct NodeSpeaker : public Node
{
    string name;
    list<Node> block;
};

struct NodeString : public Node
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

struct NodeBg : public Node
{
    string value;
};

struct NodeShow : public Node
{
    string value;
};

struct NodeMenu : public Node
{
    string value;
    list<Node> block;
};

struct NodeJump : public Node
{
    string value;
};

struct NodeIf : public Node
{
    string var1;
    string var2;
    string conditional;
};

struct NodeFin : public Node
{
    NodeFin() { }
};

struct NodeNone : public Node
{
    NodeNone() { }
};

class AST 
{
public:
    NodeSetup setupBlock;
    list<NodeLabel> labels;

    AST() { }
};
