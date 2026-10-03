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

// Retail's counter lookup body at 0x00344B20 is
// ?findFlag@Open2Lookup344B20@@QAEPA_NVAsciiString@@@Z (Open2Twins015.cpp); the
// caller reaches it through the ILT thunk at 0x000142B3, which is the defined
// name here. Same proven ABI -- thiscall, by-value name, returns the node's
// 8-byte ScriptCounter storage -- so cast the returned pointer's view.
extern void j_000142b3();

class BfmeGetCounterCall
{
public:
	ScriptCounter *getCounter(AsciiString name);
};

typedef ScriptCounter *(BfmeGetCounterCall::*GetCounterFunction)(AsciiString);

class ScriptEngine;

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	bool evaluateCounterCompareRva00325BC0(Condition *condition);
};

bool ScriptConditions::evaluateCounterCompareRva00325BC0(Condition *condition)
{
	union { void (*raw)(void); GetCounterFunction member; } getCounter;
	getCounter.raw = j_000142b3;
	int left = 0;
	ScriptCounter *counter = (reinterpret_cast<BfmeGetCounterCall *>(TheScriptEngine)
		->*getCounter.member)(condition->getParameter(0)->m_string);
	if (counter)
		left = counter->m_value;

	int right = 0;
	counter = (reinterpret_cast<BfmeGetCounterCall *>(TheScriptEngine)
		->*getCounter.member)(condition->getParameter(2)->m_string);
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
