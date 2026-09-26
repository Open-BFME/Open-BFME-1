// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// Derives from TurretState, which the base call at 0x0018D890 names -- five
// retail states go there and the reference declares exactly that set as its
// children. Its constructor is protected, so it mangles IAE; making it public
// would rename the symbol QAE and the call would stop resolving.
//
// TurretState adds nothing of its own, so this class's members start at 0x24.
#include "Common/AsciiString.h"

class StateMachine;

class TurretStateMachine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);

	virtual ~State();

private:
	unsigned char m_head[0x20];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretState : public State
{
protected:
	TurretState(TurretStateMachine *machine, AsciiString name);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretAIIdleState : public TurretState
{
public:
	TurretAIIdleState(TurretStateMachine *machine);

private:
	unsigned int m_nextIdleScan;
};

// ??0TurretAIIdleState@@QAE@PAVTurretStateMachine@@@Z
TurretAIIdleState::TurretAIIdleState(TurretStateMachine *machine) :
	TurretState(machine, "TurretAIIdleState"),
	m_nextIdleScan(0)
{
}
