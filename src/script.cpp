#include <vector>
#include <string>
#include <map>
#include "script.hpp"

using std::vector;
using std::string;
using std::map;

Script::Script()
{
    elemArr = vector<ScriptElem>();
    speakers = map<string, string>();
    labels = map<string, int>();
    globals = map<string, string>();
}


ScriptElem Script::operator[](int x)
{
    return elemArr[x];
}


ScriptVM::ScriptVM(Script _sc)
{
    scriptPos = 0;
    script = _sc;
}

void ScriptVM::step()
{
    switch(script[scriptPos].statementComponent)
    {
    case Keyword::Speaker:
	break;

    case Keyword::Var:
	break;

    case Keyword::Set:
	break;

    case Keyword::Bg:
	break;

    case Keyword::Show:
	break;

    case Keyword::Menu:
	break;

    case Keyword::Jump:
	break;

    case Keyword::If:
	break;

    case Keyword::Fin:
	break;
    }
}
