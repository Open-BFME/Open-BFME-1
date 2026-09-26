// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// State subclass constructor: build the name, hand it to the base by value,
// install this class's vptr, initialise the members this class adds.
//
// The AsciiString is the shim's rather than a hand-rolled stand-in -- the
// temporary is passed by value and only the StringBase-backed shim emits
// `mov [esp+8],esp` before `mov ecx,esp` the way retail does.
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
class AIAttackAreaState : public State
{
public:
	AIAttackAreaState(StateMachine *machine);

private:
	int m_24;
	int m_28;
};

// ??0AIAttackAreaState@@QAE@PAVStateMachine@@@Z
AIAttackAreaState::AIAttackAreaState(StateMachine *machine) :
	State(machine, "AIAttackAreaState"),
	m_24(0),
	m_28(0)
{
}
