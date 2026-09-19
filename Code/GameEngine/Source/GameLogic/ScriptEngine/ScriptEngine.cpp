// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib

// FILE: ScriptEngine.cpp /////////////////////////////////////////////////////
//
// A partial port. No ScriptEngine.cpp existed under Code/; this carries
// ScriptEngine::getStats, retail 0x003395A0 - found by the "Script Engine
// Profiling disabled." literal it pushes, which appears in exactly one
// reference source.
//
// Retail is Zero Hour's body with SPECIAL_SCRIPT_PROFILING off: three zero
// stores and the one string. The class is declared here for that member alone
// rather than reconstructed; ScriptEngine.h reaches most of GameLogic.
//
///////////////////////////////////////////////////////////////////////////////

#include "Common/AsciiString.h"

typedef float Real;

extern "C" float __cdecl sinf(float);
extern "C" float __cdecl cosf(float);

class Parameter
{
public:
	int getInt() const { return m_int; }
	float getReal() const { return m_real; }

private:
	char m_unknown[8];
	int m_int;
	float m_real;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	AsciiString getStats( Real *curTimePtr, Real *script1Time, Real *script2Time );

protected:
	void setSway(ScriptAction *pAction);

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
