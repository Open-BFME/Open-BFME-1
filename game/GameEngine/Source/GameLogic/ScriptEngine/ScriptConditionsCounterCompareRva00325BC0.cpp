// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// Retail 0x00325BC0: compares the values of two script counters.
#include "StringInline.h"

class Parameter
{
public:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

class Condition
{
public:
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_numParms)
			return m_parameters[index];
		return 0;
	}
private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parameters[12];
};

struct ScriptCounter
{
	int m_value;
};

class ScriptEngine
{
public:
	ScriptCounter *getCounter(AsciiString name);
};
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	bool evaluateCounterCompareRva00325BC0(Condition *condition);
};

bool ScriptConditions::evaluateCounterCompareRva00325BC0(Condition *condition)
{
	int left = 0;
	ScriptCounter *counter = TheScriptEngine->getCounter(condition->getParameter(0)->m_string);
	if (counter)
		left = counter->m_value;

	int right = 0;
	counter = TheScriptEngine->getCounter(condition->getParameter(2)->m_string);
	if (counter)
		right = counter->m_value;

	switch (condition->getParameter(1)->m_integer) {
	case 0: return left < right;
	case 1: return left <= right;
	case 2: return left == right;
	case 3: return left >= right;
	case 4: return left > right;
	case 5: return left != right;
	}
	return false;
}
