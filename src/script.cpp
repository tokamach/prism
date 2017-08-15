#include<vector>
#include<string>
#include<map>
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
    case Statement::Speaker:
	break;

    case Statement::Var:
	break;

    case Statement::Set:
	break;

    case Statement::Bg:
	break;

    case Statement::Show:
	break;

    case Statement::Menu:
	break;

    case Statement::Jump:
	break;

    case Statement::If:
	break;

    case Statement::Fin:
	break;
    }
}
