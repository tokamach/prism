#include<vector>
#include<string>
#include<map>

using std::vector;
using std::string;
using std::map;

enum class Statement
{
    Speaker,
    Var,
    Set,
    Bg,
    Show,
    Menu,
    Jump,
    If,
    Fin
};

class ScriptElem
{
public:
    Statement statementComponent;
    vector<string> stringComponent;

    ScriptElem(Statement _sta, vector<string> _str)
    {
	statementComponent = _sta;
	stringComponent = _str;
    }

    bool hasArgs()
    {
	switch(statementComponent)
	{
	case Statement::Speaker:
	case Statement::Bg:
	case Statement::Show:
	case Statement::Fin:
	    return true;
	default:
	    return false;
	}
    }
    
};

//TODO: implement Iterator class
class Script
{
public:
    vector<ScriptElem> elemArr;
    map<string, string> speakers;
    map<string, int> labels;
    map<string, string> globals;

    Script();
    ScriptElem operator[](int x);
};

class ScriptVM
{
public:
    Script script;
    int scriptPos;

    ScriptVM(Script _sc);
    void step();
};
