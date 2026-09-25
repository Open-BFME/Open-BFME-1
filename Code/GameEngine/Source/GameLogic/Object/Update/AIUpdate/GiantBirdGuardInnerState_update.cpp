// cl: /DNDEBUG /MD /EHsc

// GiantBirdGuardInnerState::update (0x002BD230): slot 6 of
// GiantBirdGuardInnerState's table 0x010C7B28 (installed by the constructor at
// 0x002C03F0). The first half is AIGuardInnerState::update
// (AIGuardInnerStateUpdate.cpp, whose views this reuses): restart flag, follow
// the guarded object or team, run the attack state. It then gives up with
// STATE_SUCCESS once the attack goal is gone or dead and the attack state
// answers true at vtable +0x48, instead of rescanning. The give-up test
// null-checks the attack state as a value (?:), not as an && guard: MSVC then
// keeps the reloaded pointer in ECX, as retail does, instead of the dead ESI.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1, STATE_FAILURE = -2 };
enum StateExitType { EXIT_NORMAL = 0 };

struct Coord3D
{
	Real x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); }
	Bool bfmePrivateStatusBit0() const { return (*((const unsigned char *)this + 0x344) & 1) != 0; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Coord3D *getEstimateTeamPosition_000EDCD0( Coord3D *pos ) const;
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
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();

private:
	char m_unmodelled000[0x10];
	Object *m_owner;										///< this+0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuard.h
class AIGuardMachine : public StateMachine
{
public:
	Object *findTargetToGuardByID( void ) { return TheGameLogic->findObjectByID( m_targetToGuard ); }
	Team *findTeamToGuardByID( void ) { return TheTeamFactory->findTeamByID( m_teamToGuard ); }

private:
	char m_unreconstructed000[0x44 - 0x14];
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
	BFME_GUARD_STATE_SLOT(7) BFME_GUARD_STATE_SLOT(8) BFME_GUARD_STATE_SLOT(9) BFME_GUARD_STATE_SLOT(10)
	BFME_GUARD_STATE_SLOT(11) BFME_GUARD_STATE_SLOT(12) BFME_GUARD_STATE_SLOT(13) BFME_GUARD_STATE_SLOT(14)
	BFME_GUARD_STATE_SLOT(15) BFME_GUARD_STATE_SLOT(16) BFME_GUARD_STATE_SLOT(17)
	virtual Bool bfmeStateSlot18() = 0;						///< vtable +0x48

	StateMachine *getMachine() { return m_machine; }
	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }

private:
	char m_unreconstructed004[0x1c - 0x04];
	StateMachine *m_machine;								///< this+0x1C
};

#undef BFME_GUARD_STATE_SLOT

// Layout as landed in GiantBirdGuardInnerState_onEnter.cpp (0x002BD020).
class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit( const StateMachine *machine ) const;
};

class GiantBirdGuardExitConditions : public AttackExitConditionsInterface
{
public:
	Int m_conditionsToConsider;
	Coord3D m_center;										///< this+0x08
	Real m_radiusSqr;
	UnsignedInt m_attackGiveUpFrame;
};

class GiantBirdGuardInnerState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit( StateExitType status );
	virtual StateReturnType update();

	AIGuardMachine *getGuardMachine() { return (AIGuardMachine *)getMachine(); }

private:
	char m_unmodelled020[0x24 - 0x20];
	GiantBirdGuardExitConditions m_exitConditions;			///< this+0x24, m_center at +0x2C
	State *m_attackState;									///< this+0x40
	Bool m_bfmeRestart44;									///< this+0x44
	char m_unmodelled045[0x3];								///< object ends at +0x48 (operator new 0x48)
};

// ?update@GiantBirdGuardInnerState@@UAE?AW4StateReturnType@@XZ
StateReturnType GiantBirdGuardInnerState::update( void )
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
		if (m_attackState ? m_attackState->bfmeStateSlot18() : false)
			return STATE_SUCCESS;
	}

	return ret;
}
