// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ScriptEngine helper at 0x00345A50, named by matched executeActions via
// ILT 0x0000757C. Preserve that established name. The first mode is an int:
// retail reads all 32 bits at +0x85/+0x134 and distinguishes 0, 1, and other
// values. The other two arguments are byte-tested booleans.
// A missing optional source counter FALLS THROUGH to ordinary assignment;
// only a successful copy returns. This edge is visible at retail +0x6B.
// By-value string copies target StringBase<char> at 0x00887B60, not the
// misleading GameSpyGroupRoom alias printed by the historical ledger.
#include "ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

typedef bool Bool;
typedef int Int;

class Parameter
{
public:
	Int getInt() const { return m_int; }
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	Int m_int;
	float m_real;
	AsciiString m_string;
};

class ScriptAction
{
public:
	Parameter *getParameter(Int index)
	{
		if (index >= 0 && index < m_numParms)
			return m_parms[index];
		return 0;
	}

private:
	char m_unknown[8];
	Int m_numParms;
	Parameter *m_parms[12];
};

struct ScriptCounter
{
	Int m_value;
	Bool m_isCountdownTimer;
	Bool m_isMillisecondTimer;
};

// Existing matched lookup at 0x00344B20 reads the counter map at +0x16040
// and returns node+0x18. Its historical shim calls this a flag and returns
// bool*, but the writable sibling and this caller prove an 8-byte ScriptCounter.
// Reuse the existing ABI and explicitly convert its returned storage pointer.
class Open2Lookup344B20
{
public:
    bool *findFlag(AsciiString name);
};

extern float GetGameLogicRandomValueReal(float low, float high,
	char *file, Int line);
extern float GetGameClientRandomValueReal(float low, float high,
	char *file, Int line);
extern Int GetGameLogicRandomValue(Int low, Int high,
	char *file, Int line);
extern Int GetGameClientRandomValue(Int low, Int high,
	char *file, Int line);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

// Retail uses FISTP under the active x87 control word. A normal VC7.1 cast
// calls __ftol2; this is the same proven two-instruction conversion used by
// the matched executeActions caller, rather than lifted function assembly.
__forceinline long rva00345a50FloatToLong(float value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class ScriptEngine
{
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	void Rva00345a50(ScriptAction *action, Int random,
		Bool copyCounter, Bool seconds);
};

void ScriptEngine::Rva00345a50(ScriptAction *action, Int random,
	Bool copyCounter, Bool seconds)
{
	ScriptCounter *counter = bfmeCounter(
		action->getParameter(0)->getString());
	if (!counter)
		return;

	if (copyCounter)
	{
		const ScriptCounter *source = reinterpret_cast<const ScriptCounter *>(
			((Open2Lookup344B20 *)this)->findFlag(action->getParameter(1)->getString()));
		if (source)
		{
			counter->m_value = source->m_value;
			return;
		}
	}

	if (seconds)
	{
		float value;
		if (random)
		{
			value = action->getParameter(1)->getReal();
			float randomValue = action->getParameter(2)->getReal();
			if (random == 1)
				value = GetGameLogicRandomValueReal(value, randomValue,
					"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp",
					0x709);
			else
				value = GetGameClientRandomValueReal(value, randomValue,
					"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp",
					0x70d);
		}
		else
			value = action->getParameter(1)->getReal();
		counter->m_value = rva00345a50FloatToLong(
			(float)ceil((double)(value * 30.0f)));
		counter->m_isMillisecondTimer = true;
		return;
	}

	Int value;
	if (random)
	{
		value = action->getParameter(1)->getInt();
		Int randomValue = action->getParameter(2)->getInt();
		if (random == 1)
			value = GetGameLogicRandomValue(value, randomValue,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp",
				0x723);
		else
			value = GetGameClientRandomValue(value, randomValue,
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp",
				0x727);
	}
	else
		value = action->getParameter(1)->getInt();
	counter->m_value = value;
	counter->m_isMillisecondTimer = false;
}
