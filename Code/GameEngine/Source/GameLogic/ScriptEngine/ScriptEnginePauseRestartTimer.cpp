// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	char m_beforeString[0x10];
	AsciiString m_string;
};

class ScriptAction
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
	void pauseTimer(ScriptAction *action);
	void restartTimer(ScriptAction *action);
};

void ScriptEngine::pauseTimer(ScriptAction *action)
{
	bfmeCounter(action->getParameter(0)->getString())->m_isCountdownTimer = false;
}

void ScriptEngine::restartTimer(ScriptAction *action)
{
	ScriptCounter *counter = bfmeCounter(action->getParameter(0)->getString());
	if (counter->m_value > 0)
		counter->m_isCountdownTimer = true;
}
