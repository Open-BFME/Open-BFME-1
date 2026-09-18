// cl: /DNDEBUG /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// INI::parseDrawGroupNumberDefinition, clean C++ for the former __emit thunk.
// BFME throws the variadic INIException here, not Zero Hour's plain
// INI_UNKNOWN_ERROR int: retail builds the 8-byte exception on the stack,
// calls the (int, const char*, ...) ctor at 0x00850600 with arg count 9 and
// the stringified condition, then _CxxThrowException through the MSVCR71
// import thunk.
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/INI.h"
#include "Common/INIException.h"
#include "GameClient/DrawGroupInfo.h"

/*static */ void INI::parseDrawGroupNumberDefinition(INI* ini)
{
	if (!TheDrawGroupInfo) {
		throw INIException(9, "TheDrawGroupInfo==NULL");
	}

	ini->initFromINI(TheDrawGroupInfo, TheDrawGroupInfo->getFieldParse());
}
