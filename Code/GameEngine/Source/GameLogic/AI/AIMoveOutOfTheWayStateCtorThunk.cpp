// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// Derives from AIInternalMoveToState, not from State directly. The base call
// resolves to 0x0014F280, which is where thirteen of these subclasses go, and
// the reference declares exactly that set as AIInternalMoveToState's children.
//
// That base takes the name by value and passes it on by value, which is why its
// own body copy-constructs a second AsciiString before calling State.
#include "Common/AsciiString.h"

class StateMachine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);

	virtual ~State();

private:
	unsigned char m_head[0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, AsciiString name);

private:
	unsigned char m_body[0x1C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIMoveOutOfTheWayState : public AIInternalMoveToState
{
public:
	AIMoveOutOfTheWayState(StateMachine *machine);
};

// ??0AIMoveOutOfTheWayState@@QAE@PAVStateMachine@@@Z
AIMoveOutOfTheWayState::AIMoveOutOfTheWayState(StateMachine *machine) :
	AIInternalMoveToState(machine, "AIMoveOutOfTheWayState")
{
}
