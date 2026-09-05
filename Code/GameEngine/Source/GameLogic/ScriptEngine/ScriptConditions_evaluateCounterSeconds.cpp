// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// BFME COUNTER_SECONDS (script_conditions.cpp template 112).
// Retail 0x00325D00, 243 bytes. Seconds scaled by LOGICFRAMES_PER_SECOND=5.
//
// Integer narrowing is BaseType.h fast_float2long_round: MSVC 7.1 C casts
// emit _ftol2 (no /QIfist) or fistp qword plus sub esp,8 (/QIfist). Retail
// is fstp dword / fld / fistp dword. See build/grok/counter_revision.json.

#include "StringInline.h"

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
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

class Condition
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
	bool evaluateCounterSeconds(Condition *pCondition);
};

// ?evaluateCounterSeconds@ScriptConditions@@IAE_NPAVCondition@@@Z
bool ScriptConditions::evaluateCounterSeconds(Condition *pCondition)
{
	int value;
	Condition *cond = pCondition;
	int count = 0;

	ScriptCounter *counter =
		TheScriptEngine->getCounter(cond->getParameter(0)->getString());
	if (counter)
		count = counter->m_value;

	value = (int)fast_float2long_round(
		(float)ceil((double)(cond->getParameter(2)->getReal() * 5.0f)));

	switch (cond->getParameter(1)->getInt()) {
	case 0:
		return count < value;
	case 1:
		return count <= value;
	case 2:
		return count == value;
	case 3:
		return count >= value;
	case 4:
		return count > value;
	case 5:
		return count != value;
	}
	return false;
}
