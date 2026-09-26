// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// The second argument is not stored anywhere -- retail zeroes both members and ignores it.
#include "Common/AsciiString.h"

class StateMachine;

class AttackExitConditionsInterface;

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
class AIAttackSquadState : public State
{
public:
	AIAttackSquadState(StateMachine *machine, AttackExitConditionsInterface *exitConditions);

private:
	int m_24;
	bool m_28;
};

// ??0AIAttackSquadState@@QAE@PAVStateMachine@@PAVAttackExitConditionsInterface@@@Z
AIAttackSquadState::AIAttackSquadState(StateMachine *machine, AttackExitConditionsInterface *exitConditions) :
	State(machine, "AIAttackSquadState"),
	m_24(0),
	m_28(false)
{
}
