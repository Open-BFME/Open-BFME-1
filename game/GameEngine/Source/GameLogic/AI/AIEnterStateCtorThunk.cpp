// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// Derives from AIInternalMoveToState, which the base call at 0x0014F280 names --
// thirteen retail subclasses go there and the reference declares exactly that
// set as its children. That base takes the name by value and passes it on by
// value, which is why its own body copies the AsciiString a second time.
//
// Members of this class start at 0x50, so the base spans 0x50 bytes.
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
class AIEnterState : public AIInternalMoveToState
{
public:
	AIEnterState(StateMachine *machine);

private:
	int m_50;
};

// ??0AIEnterState@@QAE@PAVStateMachine@@@Z
AIEnterState::AIEnterState(StateMachine *machine) :
	AIInternalMoveToState(machine, "AIEnterState"),
	m_50(0)
{
}
