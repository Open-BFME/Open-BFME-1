// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class StateMachine;
class AttackExitConditionsInterface;
class Team;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	State(StateMachine *machine, AsciiString name);
	virtual ~State();

private:
	unsigned char m_head[0x20];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdateModule.h
class NotifyWeaponFiredInterface
{
public:
	virtual void notifyFired() = 0;
};

struct Coord3D
{
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

// upstream source: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// The four tail fields are BFME additions absent from the later Generals header;
// their initialization and offsets are preserved from the retail constructor.
class AIAttackState : public State, public NotifyWeaponFiredInterface
{
public:
	AIAttackState(
		StateMachine *machine,
		bool follow,
		bool attackingObject,
		bool forceAttacking,
		AttackExitConditionsInterface *attackParameters);

	virtual bool isAttack() const;
	virtual void notifyFired();

private:
	void *m_attackMachine;
	AttackExitConditionsInterface *m_attackParameters;
	Team *m_victimTeam;
	Coord3D m_originalVictimPos;
	AsciiString m_lockedWeaponOnEnter;
	bool m_follow;
	bool m_isAttackingObject;
	bool m_isForceAttacking;
	unsigned char m_pad47;
	unsigned int m_bfmeAttackState48;
	bool m_bfmeAttackState4C;
	bool m_bfmeAttackState4D;
	unsigned char m_pad4E[2];
	unsigned int m_attackMachineType;
};

// ??0AIAttackState@@QAE@PAVStateMachine@@_N11PAVAttackExitConditionsInterface@@@Z
AIAttackState::AIAttackState(
	StateMachine *machine,
	bool follow,
	bool attackingObject,
	bool forceAttacking,
	AttackExitConditionsInterface *attackParameters) :
	State(machine, "AIAttackState"),
	m_attackMachine(0),
	m_attackParameters(attackParameters),
	m_victimTeam(0),
	m_lockedWeaponOnEnter(),
	m_follow(follow),
	m_isAttackingObject(attackingObject),
	m_isForceAttacking(forceAttacking),
	m_bfmeAttackState48(0),
	m_bfmeAttackState4C(false),
	m_bfmeAttackState4D(false),
	m_attackMachineType(3)
{
	m_originalVictimPos.zero();
}
