// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// Derives from AIInternalMoveToState, so its own members start at 0x50.
//
// The two stores are written in the body, not the initialiser list, and in
// retail's order: the flag at 0x54 before the word at 0x50. Member
// initialisation follows declaration order and cannot express that; body
// statements are emitted as written and can.
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
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, AsciiString name);

private:
	unsigned char m_body[0x2C];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveAwayFromRepulsorsState : public AIInternalMoveToState
{
public:
	AIMoveAwayFromRepulsorsState(StateMachine *machine);

private:
	int m_50;
	bool m_54;
};

// ??0AIMoveAwayFromRepulsorsState@@QAE@PAVStateMachine@@@Z
AIMoveAwayFromRepulsorsState::AIMoveAwayFromRepulsorsState(StateMachine *machine) :
	AIInternalMoveToState(machine, "AIMoveAwayFromRepulsors")
{
	m_54 = false;
	m_50 = 0;
}
