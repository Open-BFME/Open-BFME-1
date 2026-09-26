// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The Object block. It is one line: read the name and hand off to the shared
// four-argument body at 0x00139D00, which the ObjectReskin and ChildObject
// blocks also use -- they pass the original's name where this one passes empty
// strings, which is why that function carries both "ObjectReskin must come after
// the original Object (%s, %s)." and "ChildObject must come after the original
// Object (%s, %s)."
//
// That body is ThingFactory::parseObjectDefinition, as in Zero Hour, whose
// shared body takes two names; BFME's takes three.
#include "PreRTS.h"
#include "Common/INI.h"

class ThingFactory
{
public:
	static void parseObjectDefinition( INI *ini, const AsciiString &name,
									   const AsciiString &reskinFrom,
									   const AsciiString &childOf );	// 0x00139D00
};

void INI::parseObjectDefinition( INI* ini )
{
	ThingFactory::parseObjectDefinition( ini, AsciiString( ini->getNextToken() ),
										 AsciiString::TheEmptyString, AsciiString::TheEmptyString );
}

void INI::parseObjectReskinDefinition( INI* ini )
{
	AsciiString name( ini->getNextToken() );
	AsciiString reskinFrom( ini->getNextToken() );
	ThingFactory::parseObjectDefinition( ini, name, reskinFrom, AsciiString::TheEmptyString );
}

// BFME-only. Same shape as the reskin block, but the second name goes to the
// fourth argument rather than the third -- which is what makes it a child of the
// original rather than a reskin of it.
void INI::parseChildObjectDefinition( INI* ini )
{
	AsciiString name( ini->getNextToken() );
	AsciiString childOf( ini->getNextToken() );
	ThingFactory::parseObjectDefinition( ini, name, AsciiString::TheEmptyString, childOf );
}
