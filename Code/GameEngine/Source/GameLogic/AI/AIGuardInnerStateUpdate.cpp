// cl: /DNDEBUG /MD /EHsc

// AIGuardInnerState::update (0x0015E180): slot 6 of AIGuardInnerState's table
// 0x01096160. State's slots are onEnter 4 (?onEnter@AIGuardInnerState is
// matched there), onExit 5 and update 6, in Zero Hour's declaration order.
// Zero Hour's body keeps the guarded position in step with the target, then
// runs the attack state. BFME drops the enter state, also follows a guarded
// team, restarts itself on request, and rescans for a new inner target when
// the attack goal is gone or dead, or (every 5 frames) when a kind-of-7 goal
// is being fought with a weapon that is not in status 4.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1, STATE_FAILURE = -2 };
enum StateExitType { EXIT_NORMAL = 0 };
enum KindOfType { BFME_KINDOF_7 = 7 };
enum WeaponSlotType { BFME_WEAPONSLOT_INVALID = -1 };
enum WeaponStatus { BFME_WEAPON_STATUS_4 = 4 };

struct Coord3D
{
	Real x, y, z;
};

class AIGuardInnerState;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
	friend class AIGuardInnerState;

private:
	WeaponStatus bfmeComputeStatus( Bool *reloading ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf( KindOfType t ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Weapon *getCurrentWeapon( WeaponSlotType *wslot = 0 );

	const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); }
	Bool bfmePrivateStatusBit0() const { return (*((const unsigned char *)this + 0x344) & 1) != 0; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Coord3D *getEstimateTeamPosition_000EDCD0( Coord3D *position ) const;
};

class TeamFactory
{
public:
	Team *findTeamByID( UnsignedInt id );
};

extern TeamFactory *TheTeamFactory;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID( Int id );
	UnsignedInt getFrame() { return m_frame; }

private:
	char m_unmodelled000[0x3c];
	UnsignedInt m_frame;									///< this+0x3C
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();
	Object *getOwner() { return m_owner; }

private:
	char m_unmodelled000[0x10];
	Object *m_owner;										///< this+0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuard.h
class AIGuardMachine : public StateMachine
{
public:
	Bool lookForInnerTarget( void );

	Object *findTargetToGuardByID( void ) { return TheGameLogic->findObjectByID( m_targetToGuard ); }
	Team *findTeamToGuardByID( void ) { return TheTeamFactory->findTeamByID( m_teamToGuard ); }

private:
	char m_unmodelled014[0x44 - 0x14];
	Int m_targetToGuard;									///< this+0x44
	UnsignedInt m_teamToGuard;								///< this+0x48
};

#define BFME_GUARD_STATE_SLOT(n) virtual void bfmeGuardStateSlot##n() = 0;

class State
{
public:
	BFME_GUARD_STATE_SLOT(0) BFME_GUARD_STATE_SLOT(1) BFME_GUARD_STATE_SLOT(2) BFME_GUARD_STATE_SLOT(3)
	virtual StateReturnType onEnter() = 0;					///< vtable +0x10
	virtual void onExit( StateExitType status ) = 0;		///< vtable +0x14
	virtual StateReturnType update() = 0;					///< vtable +0x18

	StateMachine *getMachine() { return m_machine; }
	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }

private:
	char m_unmodelled004[0x1c - 0x04];
	StateMachine *m_machine;								///< this+0x1C
};

#undef BFME_GUARD_STATE_SLOT

struct ExitConditions
{
	Coord3D m_center;										///< this+0x00
};

class AIGuardInnerState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit( StateExitType status );
	virtual StateReturnType update();

	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }

private:
	char m_unmodelled020[0x2c - 0x20];
	ExitConditions m_exitConditions;						///< this+0x2C
	char m_unmodelled038[0x40 - 0x38];
	State *m_attackState;									///< this+0x40
	Bool m_bfmeRestart44;									///< this+0x44
	char m_unmodelled045[0x3];
	UnsignedInt m_bfmeNextWeaponCheckFrame48;				///< this+0x48
};

// ?update@AIGuardInnerState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIGuardInnerState::update( void )
{
	if (m_bfmeRestart44)
	{
		m_bfmeRestart44 = false;
		return onEnter();
	}

	if (!m_attackState)
		return STATE_SUCCESS;

	// if the position has moved (IE we're guarding an object), move with it.
	AIGuardMachine *machine = getGuardMachine();
	Object* targetToGuard = machine->findTargetToGuardByID();
	Team* teamToGuard = machine->findTeamToGuardByID();
	if (targetToGuard) 
	{
		m_exitConditions.m_center = *targetToGuard->getPosition();
	}
	else if (teamToGuard)
	{
		teamToGuard->getEstimateTeamPosition_000EDCD0( &m_exitConditions.m_center );
	}

	StateReturnType ret = m_attackState->update();

	Object *goal = m_attackState->getMachineGoalObject();
	if (goal == 0 || goal->bfmePrivateStatusBit0())
	{
		if (getGuardMachine()->lookForInnerTarget())
		{
			onExit( EXIT_NORMAL );
			return onEnter();
		}
	}

	if (goal && goal->isKindOf( BFME_KINDOF_7 ) && TheGameLogic->getFrame() >= m_bfmeNextWeaponCheckFrame48)
	{
		Weapon *weapon = getMachine()->getOwner()->getCurrentWeapon();
		if (weapon && weapon->bfmeComputeStatus( 0 ) != BFME_WEAPON_STATUS_4)
		{
			m_bfmeNextWeaponCheckFrame48 = TheGameLogic->getFrame() + 5;
			if (getGuardMachine()->lookForInnerTarget())
			{
				onExit( EXIT_NORMAL );
				return onEnter();
			}
		}
	}

	return ret;
}
