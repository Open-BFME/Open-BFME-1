// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
int GetGameLogicRandomValue(int low, int high, char *file, int line);

__forceinline long bfmeSetTimerFloatToLong(float value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

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
	bool m_isMillisecondTimer;
};

class ScriptEngine
{
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	void setTimer(ScriptAction *action, bool millisecondTimer, bool random);
};

void ScriptEngine::setTimer(ScriptAction *action,
	bool millisecondTimer, bool random)
{
	ScriptCounter *counter = bfmeCounter(
		action->getParameter(0)->getString());
	if (millisecondTimer)
	{
		Parameter *amount = action->getParameter(1);
		float value = amount->getReal();
		if (random)
		{
			float randomValue = action->getParameter(2)->getReal();
			value = (float)GetGameLogicRandomValue((int)value,
				(int)randomValue,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp",
				2244);
		}
		counter->m_value = bfmeSetTimerFloatToLong(
			(float)ceil((double)(value * 30.0f)));
		counter->m_isMillisecondTimer = true;
	}
	else
	{
		Parameter *amount = action->getParameter(1);
		int value = amount->getInt();
		if (random)
		{
			int randomValue = action->getParameter(2)->getInt();
			value = GetGameLogicRandomValue(value, randomValue,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp",
				2252);
		}
		counter->m_value = value;
		counter->m_isMillisecondTimer = false;
	}
	counter->m_isCountdownTimer = true;
}
