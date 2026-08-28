// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// Two bool arguments stored at 0x24 and 0x27, with 0x25 and 0x26 zeroed first.
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
class AIAttackAimAtTargetState : public State
{
public:
	AIAttackAimAtTargetState(StateMachine *machine, bool a, bool b);

private:
	bool m_24;
	bool m_25;
	bool m_26;
	bool m_27;
};

// ??0AIAttackAimAtTargetState@@QAE@PAVStateMachine@@_N1@Z
AIAttackAimAtTargetState::AIAttackAimAtTargetState(StateMachine *machine, bool a, bool b) :
	State(machine, "AIAttackAimAtTargetState")
{
	m_25 = false;
	m_26 = false;
	m_24 = a;
	m_27 = b;
}
