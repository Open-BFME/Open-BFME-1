// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// The second argument is not stored anywhere -- retail zeroes both members and ignores it.
#include "Common/AsciiString.h"

class StateMachine;

class AttackExitConditionsInterface;

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
