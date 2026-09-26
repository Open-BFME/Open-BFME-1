// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// State subclass constructor: build the name, hand it to the base by value,
// install this class's vptr.
//
// The AsciiString is the shim's rather than a hand-rolled four-byte stand-in.
// That is the whole difference between matching and not: the temporary is passed
// by value, and only the StringBase-backed shim emits `mov [esp+8],esp` before
// `mov ecx,esp` the way retail does. An earlier attempt at this family declared
// its own AsciiString and stalled on exactly that pair.
//
// The base's mangled name spells its second parameter VAsciiString@@, so the
// class has to carry that name for the call to mangle the same way.
#include "Common/AsciiString.h"

class StateMachine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);

	virtual ~State();

private:
	unsigned char m_head[0x20];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIBusyState : public State
{
public:
	AIBusyState(StateMachine *machine);
};

// ??0AIBusyState@@QAE@PAVStateMachine@@@Z
AIBusyState::AIBusyState(StateMachine *machine) :
	State(machine, "AIBusyState")
{
}
