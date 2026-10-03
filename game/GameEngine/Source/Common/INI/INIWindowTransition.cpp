// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	TransitionGroup *getNewGroup( AsciiString name );
};

// Retail calls the handler's getNewGroup through the five-byte ILT thunk at
// 0x000480C7, which the ledger owns as ?j_000480c7@@YAXXZ
// (game/gen_small/thunks_034.cpp: `void j_000480c7() { b_0048b550(); }`, a
// tail jmp to ?getNewGroup@BFMETransitionHandler@@QAEPAVBFMETransitionGroup@@VBFMETransitionAsciiString@@@Z).
// That thunk is the only definition at the call target's address, so the
// reference has to carry its name.
//
// __thiscall is not available in this compilation, so the thunk is
// reinterpreted as a member-function pointer through the same union pun the
// Miles TUs use (SampleStarter006B4090.cpp) and BfmeConv1850.cpp; MSVC folds
// it back into a direct thiscall, which is retail's "receiver in ECX, name on
// the stack" shape.
extern void j_000480c7();

template <class M> inline M bfmeMemberOf(void (*fn)()) { union { void (*f)(); M m; } u; u.f = fn; return u.m; }
typedef TransitionGroup *(GameWindowTransitionsHandler::*GetNewGroup)(AsciiString name);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
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
		TransitionGroup *group = (TheTransitionHandler->*bfmeMemberOf<GetNewGroup>(j_000480c7))( name );
		ini->initFromINI( group, TransitionGroup::m_transitionGroupFieldParseTable );
	}
}
