// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// AIStateMachine.h names the two bool arguments and four fields. Retail ctor
// 0x001711B7/+0x24 and 0x001711BA/+0x27 store attackingObject/forceAttacking.
// Independent onEnter 0x00183E40 clears setLocomotor at +0x26 (0x00183E96),
// sets canTurnInPlace at +0x25 (0x00183EBA), and tests +0x24 before passing
// +0x27 to setTurretTargetObject. The constructor zeroes both transient flags.
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
	AIAttackAimAtTargetState(StateMachine *machine, bool attackingObject, bool forceAttacking);

private:
	bool m_isAttackingObject;
	bool m_canTurnInPlace;
	bool m_setLocomotor;
	bool m_isForceAttacking;
};

// ??0AIAttackAimAtTargetState@@QAE@PAVStateMachine@@_N1@Z
AIAttackAimAtTargetState::AIAttackAimAtTargetState(StateMachine *machine, bool attackingObject, bool forceAttacking) :
	State(machine, "AIAttackAimAtTargetState")
{
	m_canTurnInPlace = false;
	m_setLocomotor = false;
	m_isAttackingObject = attackingObject;
	m_isForceAttacking = forceAttacking;
}
