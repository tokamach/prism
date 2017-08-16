#include <string>
#include <list>

using std::string;
using std::list;

//TODO: macroize this whole step

class Node
{
//  Node next;
    Node() { }
};

class NodeSetup : public Node
{
    list<Node> block;

    NodeSetup() : Node() { }
};

class NodeLabel : public Node
{
    string label;
    list<Node> block;

    NodeLabel(string _label)
    {
	label = _label;
    }
}

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

    NodeSet(string _label, string _value) : Node()
    {
	label = _label;
	value = _value;
    }
};

class NodeBg : public Node
{
    string value;

    NodeBg(string _value) : Node()
    {
	value = _value;
    }
};

class NodeShow : public Node
{
    string value;

    NodeShow(string _value) : Node()
    {
	value = _value;
    }
};

class NodeMenu : public Node
{
    string value;
    list<Node> block;

    NodeMenu(string _value, list<Node> _block) : Node()
    {
	value = _value;
	block = _block;
    }
};

class NodeJump : public Node
{
    string value;

    NodeJump(string _value) : Node()
    {
	value = _value;
    }
};

class NodeIf : public Node
{
    string var1;
    string var2;
    string conditional;

    NodeIf(string _var1, string _var2, string _cond) : Node()
    {
	var1 = _var1;
	var2 = _var2;
	conditional = _cond;
    }
};

class NodeFin : public Node
{
    NodeIf() : Node() { }
};

class NodeNone : public Node
{
    NodeNone() : Node() { }
};

class AST 
{
    
};
