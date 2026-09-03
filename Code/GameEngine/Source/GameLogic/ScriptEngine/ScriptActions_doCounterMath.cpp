// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	int getInt() const { return m_integer; }
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
};

class ScriptActions;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
    friend class ScriptActions;

protected:
	ScriptCounter *bfmeCounter(AsciiString name);
};

extern ScriptEngine *TheScriptEngine;
extern void j_000142b3();

class BfmeGetCounterCall
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doCounterMathCounter(Parameter *counter, Parameter *operation,
		Parameter *otherCounter);
	void doCounterMathValue(Parameter *counter, Parameter *operation,
		Parameter *value);
};

void ScriptActions::doCounterMathCounter(Parameter *counter,
	Parameter *operation, Parameter *otherCounter)
{
	ScriptCounter *destination;
	int result;
	const ScriptCounter *source;
	destination = TheScriptEngine->bfmeCounter(counter->getString());
	result = destination->m_value;
	int value;
	value = 0;
	typedef const ScriptCounter *(BfmeGetCounterCall::*GetCounterFunction)(AsciiString);
	union { void (*raw)(void); GetCounterFunction member; } getCounter;
	getCounter.raw = j_000142b3;
	source = (reinterpret_cast<BfmeGetCounterCall *>(TheScriptEngine)
		->*getCounter.member)(otherCounter->getString());
	if (source)
		value = source->m_value;

	switch (operation->getInt())
	{
	case 0:
		result += value;
		break;
	case 1:
		result -= value;
		break;
	case 2:
		result *= value;
		break;
	case 3:
		result /= value;
		break;
	}
	destination->m_value = result;
}

void ScriptActions::doCounterMathValue(Parameter *counter,
	Parameter *operation, Parameter *value)
{
	ScriptCounter *destination = TheScriptEngine->bfmeCounter(
		counter->getString());
	int result = destination->m_value;
	int operand = value->getInt();

	switch (operation->getInt())
	{
	case 0:
		result += operand;
		break;
	case 1:
		result -= operand;
		break;
	case 2:
		result *= operand;
		break;
	case 3:
		result /= operand;
		break;
	}
	destination->m_value = result;
}
