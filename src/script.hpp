#include<vector>
#include<string>
#include<map>

using std::vector;
using std::string;
using std::map;

const string KEYWORDS[] = 
{
    "speaker",
    "var",
    "set",
    "bg",
    "show",
    "menu",
    "jump",
    "if",
    "fin"
};

class ScriptElem
{
public:
    Keyword statementComponent;
    vector<string> stringComponent;

    ScriptElem(Keyword _sta, vector<string> _str)
    {
	statementComponent = _sta;
	stringComponent = _str;
    }

    bool hasArgs()
    {
	switch(statementComponent)
	{
	case Keyword::Speaker:
	case Keyword::Bg:
	case Keyword::Show:
	case Keyword::Fin:
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
