// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// Constructors and protected scalar-deleting wrappers for the two attack-action
// states share these exact layouts. Constructor-installed vtables 0x01097C60
// and 0x01097DC0 route slot zero to wrappers 0x0017FE20 and 0x0017FEE0;
// their complete destructors remain reached through ILTs 0x0000C0C7/0x00028DD0.

// AIStateMachine.h names the two bool arguments and four fields. Retail ctor
// 0x001711B7/+0x24 and 0x001711BA/+0x27 store attackingObject/forceAttacking.
// Independent onEnter 0x00183E40 clears setLocomotor at +0x26 (0x00183E96),
// sets canTurnInPlace at +0x25 (0x00183EBA), and tests +0x24 before passing
// +0x27 to setTurretTargetObject. The constructor zeroes both transient flags.
#include "Common/AsciiString.h"

class StateMachine;
class NotifyWeaponFiredInterface;

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
class AIAttackAimAtTargetState : public State
{
public:
	AIAttackAimAtTargetState(StateMachine *machine, bool attackingObject, bool forceAttacking);

protected:
	virtual ~AIAttackAimAtTargetState();

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

// The typed NotifyWeaponFiredInterface* argument is stored at this+0x24 by
// retail 0x001712EB; AIStateMachine.h names this non-owning member m_att.
// The BFME-only bool at +0x28 remains unnamed.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackFireWeaponState : public State
{
public:
	AIAttackFireWeaponState(StateMachine *machine, NotifyWeaponFiredInterface * notify);

protected:
	virtual ~AIAttackFireWeaponState();

private:
	NotifyWeaponFiredInterface * m_att;
	bool m_28;
};

// ??0AIAttackFireWeaponState@@QAE@PAVStateMachine@@PAVNotifyWeaponFiredInterface@@@Z
AIAttackFireWeaponState::AIAttackFireWeaponState(StateMachine *machine, NotifyWeaponFiredInterface * notify) :
	State(machine, "AIAttackFireWeaponState"),
	m_att(notify),
	m_28(false)
{
}
