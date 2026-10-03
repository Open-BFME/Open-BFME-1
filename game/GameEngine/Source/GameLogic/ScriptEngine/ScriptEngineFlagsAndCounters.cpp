// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// The three script-action entry points that write a named flag or counter:
//
//   0x00345CA0  addCounter  71 bytes
//   0x00345D00  subCounter  71 bytes
//   0x00345EB0  setFlag    165 bytes, either from a literal or from another flag
//
// The two counter halves are the same body with one operator changed, and
// setFlag is their flag-side equivalent. All three take the name out of a
// ScriptAction parameter and hand it to a by-value lookup.
//
// ScriptCounter carries the millisecond flag at +0x05 here even though none of
// these three touches it: ScriptEngineTimers.cpp's setTimer writes it, and the
// counter is one record whatever reads it. addCounter and subCounter had
// stopped at the countdown flag because that is as far as their own bodies see.
//
// ScriptAction is the array-of-pointers spelling that setTimer and adjustTimer
// pinned by reaching indices 1 and 2; these three use indices 0 and 1 and agree.

#include "StringInline.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	// Retail inlines these reads. Accessing the existing fields directly
	// avoids emitting getter COMDATs for this partial Parameter layout.
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
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
	bool m_isCountdownTimer;					// +0x04
	bool m_isMillisecondTimer;					// +0x05
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
// Retail's read-only flag lookup body at 0x00344E10 is
// ?findFlag@BFMEScriptEngineFlagLookup@@QAEPA_NVAsciiString@@@Z
// (ScriptEngineClearFlag.cpp); setFlag reaches it through the ILT thunk at
// 0x0004278F, which is the defined name here.
extern void j_0004278f();

class BFMEScriptEngineFlagLookup
{
public:
	bool *findFlag(AsciiString name);
};

typedef bool *(BFMEScriptEngineFlagLookup::*FindFlagFunction)(AsciiString);

class ScriptEngine
{
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	bool *bfmeFlagForWrite(AsciiString name);
	void addCounter(ScriptAction *action);
	void subCounter(ScriptAction *action);
	void setFlag(ScriptAction *action, bool copyFromFlag);
};

void ScriptEngine::addCounter(ScriptAction *action)
{
	int value = action->getParameter(0)->m_integer;
	bfmeCounter(action->getParameter(1)->m_string)->m_value += value;
}

void ScriptEngine::subCounter(ScriptAction *action)
{
	int value = action->getParameter(0)->m_integer;
	bfmeCounter(action->getParameter(1)->m_string)->m_value -= value;
}

void ScriptEngine::setFlag(ScriptAction *action, bool copyFromFlag)
{
	ScriptAction *sourceAction = action;
	bool *flag = bfmeFlagForWrite(sourceAction->getParameter(0)->m_string);
	bool value = false;
	if (copyFromFlag)
	{
		union { void (*raw)(void); FindFlagFunction member; } findFlag;
		findFlag.raw = j_0004278f;
		bool *source =
			(reinterpret_cast<BFMEScriptEngineFlagLookup *>(this)->*findFlag.member)(
				sourceAction->getParameter(1)->m_string);
		if (source)
			value = *source;
	}
	else
	{
		value = sourceAction->getParameter(1)->m_integer != 0;
	}
	*flag = value;
}
