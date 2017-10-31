#pragma once

#include <string>
#include <list>

using std::string;
using std::list;

//TODO: macroize this whole step

struct Node
{
//  Node next;
  virtual ~Node() { };
};

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

class AST 
{
public:
    NodeSetup setupBlock;
    list<NodeSection> sections;

    AST() { }
};
