#include <string>
#include <list>

using std::string;
using std::list;

//TODO: macroize this whole step

class Node
{
    Node next;
    Node() { }
};

class NodeSpeaker : public Node
{
    string name;
    list<Node> block;

    NodeSpeaker(string name) : Node()
    {
	name = name;
    }
};

class NodeString : public Node
{
    string value;

    NodeString(string value) : Node()
    {
	value = value;
    }
};

class NodeVar : public Node
{
    string label;
    string optValue;

    NodeVar(string _label, string _optValue = ""s) : Node()
    {
	label = _label;
	if(_optValue != ""s)
	{
	    optValue = _optValue
	}
    }
};

class NodeSet : public Node
{
    string label;
    string value;
}:

class NodeNone : public Node
{
    NodeNone() : Node() { }
};

class AST 
{
    
};
