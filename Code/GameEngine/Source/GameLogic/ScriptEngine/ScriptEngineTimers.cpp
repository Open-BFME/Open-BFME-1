// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// The five script-timer entry points, which are one feature:
//
//   0x00345FE0  evaluateTimer   73 bytes  has the countdown expired
//   0x00346040  setTimer       263 bytes  set it, optionally random, ms or frames
//   0x00346190  pauseTimer      52 bytes  clear the countdown flag
//   0x003461E0  restartTimer    57 bytes  set it again if there is time left
//   0x00346230  adjustTimer    160 bytes  add to or subtract from it
//
// Every one of them starts by resolving a named ScriptCounter through
// bfmeCounter and then reads or writes its two flags. Written apart, no file
// held the whole counter.
//
// ScriptCounter is the first thing the split hid: setTimer writes the
// millisecond flag at +0x05 and so declares it, while the other four stop at
// the countdown flag at +0x04 because that is all they touch. One declaration
// now carries both flags next to the value they qualify.
//
// ScriptAction is the second, and here the two spellings CONTRADICT each other.
// setTimer and adjustTimer declare the parameter block as an array of pointers
// and index it, `m_parameters[index]`; pauseTimer and restartTimer declare a
// pointer to an array and offset it, `m_parameters + index`. Those generate
// different code -- a load from this+0x0C+index*4 against a load of
// this+0x0C followed by an add of index*0x14 -- and they agree only at index 0.
// pauseTimer and restartTimer use nothing but index 0, so their spelling was
// never constrained by their own bodies; setTimer and adjustTimer reach indices
// 1 and 2 and byte-match with the array of pointers, which is what settles it.
// The merged declaration is the proven one.
//
// Condition is the same story once more. evaluateTimer, its only user here,
// reads index 0 only, where the two spellings coincide -- so this file cannot
// settle it. ScriptEngineEvaluateFlag.cpp can: that matched body declares
// Condition as an array of pointers and reaches index 1, which does constrain
// it. So Condition is written the same way as ScriptAction, on that evidence
// rather than on the symmetry.

#include "StringInline.h"

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
int GetGameLogicRandomValue(int low, int high, char *file, int line);

// Two names for one byte-identical helper. They stay two because each is
// inlined into a body that names it, and renaming either would edit a proven
// body's source to suit the grouping rather than the other way round.
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
		if (index >= 0 && index < m_numParms)
			return m_parameters[index];
		return 0;
	}

private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parameters[12];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
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
	bool m_isCountdownTimer;					// +0x04
	bool m_isMillisecondTimer;					// +0x05
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	void setTimer(ScriptAction *action, bool millisecondTimer, bool random);
	void pauseTimer(ScriptAction *action);
	void restartTimer(ScriptAction *action);
	void adjustTimer(ScriptAction *action, bool millisecondTimer, bool add);

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
