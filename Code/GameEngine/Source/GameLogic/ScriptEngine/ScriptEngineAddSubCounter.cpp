// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

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

class ScriptAction
{
public:
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_parameterCount)
			return m_parameters[index];
		return 0;
	}

private:
	char m_unknown[8];
	int m_parameterCount;
	Parameter *m_parameters[12];
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
	void addCounter(ScriptAction *action);
	void subCounter(ScriptAction *action);
};

void ScriptEngine::addCounter(ScriptAction *action)
{
	int value = action->getParameter(0)->getInt();
	bfmeCounter(action->getParameter(1)->getString())->m_value += value;
}

void ScriptEngine::subCounter(ScriptAction *action)
{
	int value = action->getParameter(0)->getInt();
	bfmeCounter(action->getParameter(1)->getString())->m_value -= value;
}
