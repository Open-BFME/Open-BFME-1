// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The WindowTransition block. Reads the group name, asks the transition handler
// for a new group, and parses into it.
//
// TheTransitionHandler at 0x012F3330 is the same singleton
// GameWindowManager::reset and ::update call, both of which are byte-matched, so
// the receiver is not in doubt. getNewGroup is Zero Hour's declared signature --
// TransitionGroup *getNewGroup( AsciiString name ) -- and the call matches it:
// the name is copied into an argument slot by value and the returned pointer is
// what initFromINI writes into.
#include "PreRTS.h"
#include "Common/INI.h"

class TransitionGroup;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	TransitionGroup *getNewGroup( AsciiString name );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class TransitionGroup
{
public:
	static const FieldParse m_transitionGroupFieldParseTable[];
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

void INI::parseWindowTransitions( INI* ini )
{
	AsciiString name;
	name = ini->getNextToken();

	if( TheTransitionHandler )
	{
		TransitionGroup *group = TheTransitionHandler->getNewGroup( name );
		ini->initFromINI( group, TransitionGroup::m_transitionGroupFieldParseTable );
	}
}
