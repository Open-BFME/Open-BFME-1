// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

__forceinline long bfmeTimerFloatToLong(float value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	int getInt() const { return m_integer; }
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	void adjustTimer(ScriptAction *action, bool millisecondTimer, bool add);
};

void ScriptEngine::adjustTimer(ScriptAction *action,
	bool millisecondTimer, bool add)
{
	ScriptCounter *counter = bfmeCounter(
		action->getParameter(1)->getString());
	if (millisecondTimer)
	{
		Parameter *amount = action->getParameter(0);
		float value = amount->getReal();
		if (!add)
			value = -value;
		counter->m_value += bfmeTimerFloatToLong(
			(float)ceil((double)(value * 30.0f)));
	}
	else
	{
		Parameter *amount = action->getParameter(0);
		int value = amount->getInt();
		if (!add)
			value = -value;
		counter->m_value += value;
	}
}
