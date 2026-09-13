// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The Object block. It is one line: read the name and hand off to the shared
// four-argument body at 0x00139D00, which the ObjectReskin and ChildObject
// blocks also use -- they pass the original's name where this one passes empty
// strings, which is why that function carries both "ObjectReskin must come after
// the original Object (%s, %s)." and "ChildObject must come after the original
// Object (%s, %s)."
//
// Zero Hour's shared body takes two names; BFME's takes three.
#include "PreRTS.h"
#include "Common/INI.h"

void INI::parseObjectDefinition( INI* ini )
{
	parseObjectDefinition( ini, AsciiString( ini->getNextToken() ),
												 AsciiString::TheEmptyString, AsciiString::TheEmptyString );
}

void INI::parseObjectReskinDefinition( INI* ini )
{
	AsciiString name( ini->getNextToken() );
	AsciiString reskinFrom( ini->getNextToken() );
	parseObjectDefinition( ini, name, reskinFrom, AsciiString::TheEmptyString );
}

// BFME-only. Same shape as the reskin block, but the second name goes to the
// fourth argument rather than the third -- which is what makes it a child of the
// original rather than a reskin of it.
void INI::parseChildObjectDefinition( INI* ini )
{
	AsciiString name( ini->getNextToken() );
	AsciiString childOf( ini->getNextToken() );
	parseObjectDefinition( ini, name, AsciiString::TheEmptyString, childOf );
}
