// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// BFME COUNTER_SECONDS (script_conditions.cpp template 112).
// Retail 0x00325D00, 268 bytes including the comparison table. Seconds scaled by LOGICFRAMES_PER_SECOND=5.
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
	// These reads are inlined in retail; direct field access keeps this
	// caller's layout from emitting competing getter COMDATs.
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
	bool evaluateCounterSeconds(Condition *pCondition);
};

// ?evaluateCounterSeconds@ScriptConditions@@IAE_NPAVCondition@@@Z
bool ScriptConditions::evaluateCounterSeconds(Condition *pCondition)
{
	int value;
	Condition *cond = pCondition;
	int count = 0;

	union { void (*raw)(void); GetCounterFunction member; } getCounter;
	getCounter.raw = j_000142b3;
	ScriptCounter *counter = (reinterpret_cast<BfmeGetCounterCall *>(TheScriptEngine)
		->*getCounter.member)(cond->getParameter(0)->m_string);
	if (counter)
		count = counter->m_value;

	value = (int)fast_float2long_round(
		(float)ceil((double)(cond->getParameter(2)->m_real * 5.0f)));

	switch (cond->getParameter(1)->m_integer) {
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
