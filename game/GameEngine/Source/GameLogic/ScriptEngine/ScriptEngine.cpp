// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib

// FILE: ScriptEngine.cpp /////////////////////////////////////////////////////
//
// Recovered ScriptEngine bodies share the original TU named by the timer
// cluster's embedded retail source path. The class stays local and partial;
// pulling in ScriptEngine.h would expose the unreconstructed GameLogic graph.
//
///////////////////////////////////////////////////////////////////////////////

#include "StringInline.h"

typedef float Real;

extern "C" float __cdecl sinf(float);
extern "C" float __cdecl cosf(float);
extern "C" __declspec(dllimport) double __cdecl ceil(double);
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

// The two retail bodies emit separate internal helper symbols.
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

class Parameter
{
public:
	int getInt() const { return m_int; }
	float getReal() const { return m_real; }
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

class Condition
{
public:
	Parameter *getParameter(int ndx)
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}

private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parms[12];
};

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
	bool m_isMillisecondTimer;
};

class ScriptAction
{
public:
	Parameter *getParameter(int ndx)
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}

private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parms[12];
};

struct Coord2D
{
	float x;
	float y;
};

struct BreezeInfo
{
	float m_direction;
	Coord2D m_directionVec;
	float m_intensity;
	float m_lean;
	float m_randomness;
	short m_breezePeriod;
	short m_breezeVersion;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	AsciiString getStats( Real *curTimePtr, Real *script1Time, Real *script2Time );
	bool evaluateTimer(Condition *condition);

protected:
	void setSway(ScriptAction *pAction);
	ScriptCounter *bfmeCounter(AsciiString name);
	void setTimer(ScriptAction *action, bool millisecondTimer, bool random);
	void pauseTimer(ScriptAction *action);
	void restartTimer(ScriptAction *action);
	void adjustTimer(ScriptAction *action, bool millisecondTimer, bool add);

private:
	unsigned char m_unreconstructed[0x17604];
	BreezeInfo m_breezeInfo;
};

// ?getStats@ScriptEngine@@QAE?AVAsciiString@@PAM00@Z
AsciiString ScriptEngine::getStats( Real *curTimePtr, Real *script1Time, Real *script2Time )
{
	*curTimePtr = 0;
	*script1Time = 0;
	*script2Time = 0;
	AsciiString msg = "Script Engine Profiling disabled.";
	return msg;
}

// ?setSway@ScriptEngine@@IAEXPAVScriptAction@@@Z
void ScriptEngine::setSway(ScriptAction *pAction)
{
	++m_breezeInfo.m_breezeVersion;
	m_breezeInfo.m_direction = pAction->getParameter(0)->getReal();
	m_breezeInfo.m_directionVec.x = sinf(m_breezeInfo.m_direction);
	m_breezeInfo.m_directionVec.y = cosf(m_breezeInfo.m_direction);
	m_breezeInfo.m_intensity = pAction->getParameter(1)->getReal();
	m_breezeInfo.m_lean = pAction->getParameter(2)->getReal();
	m_breezeInfo.m_breezePeriod = (short)pAction->getParameter(3)->getInt();
	if (m_breezeInfo.m_breezePeriod < 1)
		m_breezeInfo.m_breezePeriod = 1;
	m_breezeInfo.m_randomness = pAction->getParameter(4)->getReal();
}

bool ScriptEngine::evaluateTimer(Condition *condition)
{
	ScriptCounter *counter = bfmeCounter(condition->getParameter(0)->getString());
	if (!counter->m_isCountdownTimer)
		return false;
	return counter->m_value < 1;
}

void ScriptEngine::setTimer(ScriptAction *action,
	bool millisecondTimer, bool random)
{
	ScriptCounter *counter = bfmeCounter(action->getParameter(0)->getString());
	if (millisecondTimer)
	{
		Parameter *amount = action->getParameter(1);
		float value = amount->getReal();
		if (random)
		{
			float randomValue = action->getParameter(2)->getReal();
			value = (float)GetGameLogicRandomValue((int)value, (int)randomValue,
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
	ScriptCounter *counter = bfmeCounter(action->getParameter(1)->getString());
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
