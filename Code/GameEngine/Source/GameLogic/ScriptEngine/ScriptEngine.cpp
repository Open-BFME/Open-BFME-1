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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	AsciiString getStats( Real *curTimePtr, Real *script1Time, Real *script2Time );
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
