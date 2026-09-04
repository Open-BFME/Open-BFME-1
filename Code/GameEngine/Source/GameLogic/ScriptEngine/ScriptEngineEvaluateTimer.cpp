// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

// Retail 0x00345FE0, 73 bytes.  Evaluate the named counter's expiration state.

#include "StringInline.h"

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	char m_beforeString[0x10];
	AsciiString m_string;
};

class Condition
{
public:
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_parameterCount)
			return m_parameters + index;
		return 0;
	}

private:
	char m_unknown[8];
	int m_parameterCount;
	Parameter *m_parameters;
};

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
};

class ScriptEngine
{
protected:
	ScriptCounter *bfmeCounter(AsciiString name);

public:
	bool evaluateTimer(Condition *condition);
};

bool ScriptEngine::evaluateTimer(Condition *condition)
{
	ScriptCounter *counter = bfmeCounter(
		condition->getParameter(0)->getString());
	if (!counter->m_isCountdownTimer)
		return false;
	return counter->m_value < 1;
}
