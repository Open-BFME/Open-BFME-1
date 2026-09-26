// cl: /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS
// stlport
// AIGuardInnerState::onEnter at retail RVA 0x0015C570.
// The dedicated AIGuardInnerState vtable 0x01096160 slot 4 routes through
// ILT 0x0003D6FE to this body.  The local structure follows the exact
// GiantBirdGuardInnerState::onEnter donor at 0x002BD020; all callees below
// are address-routed ABI views, not semantic guesses.

#include <algorithm>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class Xfer;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheBfmeGameLogic;

class Team
{
public:
	Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *position) const;
};

class TeamFactory
{
public:
	Team *findTeamByID(UnsignedInt id);
};

extern TeamFactory *TheTeamFactory;

class AI
{
public:
	static Real getAdjustedVisionRangeForObject(const Object *object, Int factors);
};

class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *centerPosition) const;
};

// BFME layout view: 0x0015C330 and this body independently use polygon
// pointer +0x4c, position +0x50, and target ID +0x6c. The inferred
// AIGuardMachine setter witness describes conflicting offsets; do not
// make this partial view assert that disputed complete class layout.
class Rva0015C570GuardMachine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
	unsigned char m_pad14[0x30];
	Int m_targetToGuard;
	UnsignedInt m_teamToGuard;
	PolygonTrigger *m_areaToGuard;
	Coord3D m_positionToGuard;
	unsigned char m_pad5c[0x10];
	Int m_nemesisToAttack;
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(const Object *object);
};

class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const;
};

class AIGuardExitConditions : public AttackExitConditionsInterface
{
public:
	Int m_conditionsToConsider;
	Coord3D m_center;
	Real m_radiusSqr;
	UnsignedInt m_attackGiveUpFrame;
};

class Rva002BD020AIAttackState
{
protected:
	virtual ~Rva002BD020AIAttackState();

public:
	enum MagicEnum
	{
		GLUE_NOT_IMPLEMENTED = 0
	};

	static void *operator new(unsigned int size, MagicEnum)
	{
		return ::operator new(size);
	}

	static void operator delete(void *memory, MagicEnum)
	{
		::operator delete(memory);
	}

	protected:
	static void *operator new(unsigned int size)
	{
		return ::operator new(size);
	}
	static void operator delete(void *memory)
	{
		::operator delete(memory);
	}

	public:
	Rva002BD020AIAttackState(StateMachine *machine, Bool follow,
		Bool attackingObject, Bool forceAttacking,
		AttackExitConditionsInterface *conditions);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual StateReturnType onEnter();

	private:
	virtual void *getObjectMemoryPool();

	public:
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_tail20[0x34];
};

class State
{
public:
	virtual ~State() { }

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

public:
	virtual StateReturnType onEnter();
	virtual void onExit();
	virtual StateReturnType update();
	virtual Bool isIdle() const;
	virtual Bool isAttack() const;
	virtual Bool isGuardIdle() const;
	virtual Bool isBusy() const;

	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	StateMachine *getMachine()
	{
		return m_machine;
	}
};

class AIGuardInnerState : public State
{
public:
	virtual ~AIGuardInnerState() { }
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	virtual void onExit();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

	unsigned char m_pad20[4];
	AIGuardExitConditions m_exitConditions;
	Rva002BD020AIAttackState *m_attackState;
	void *m_enterState;
	UnsignedInt m_frameAt48;
};

typedef Real (PolygonTrigger::*GetAreaValueCall)() const;

extern void j_0000bf3c();
extern void j_00007ad6();
extern void j_0001f253();
extern void j_000241fe();
extern void j_00044c2e();
extern void j_00045a02();

typedef Object *(GameLogic::*FindObjectByIDCall)(Int);
typedef Team *(TeamFactory::*FindTeamByIDCall)(UnsignedInt);
typedef Coord3D *(Team::*EstimateTeamPositionCall)(Coord3D *) const;
typedef void (PolygonTrigger::*GetCenterPointCall)(Coord3D *) const;

inline Object *findBfmeObject(GameLogic *logic, Int id)
{
	union
	{
		void *asVoid;
		FindObjectByIDCall asMember;
	} findObjectCast;
	findObjectCast.asVoid = (void *)j_0001f253;
	return (logic->*findObjectCast.asMember)(id);
}

inline Object *getGuardOwner(Rva0015C570GuardMachine *machine)
{
	return machine->m_owner;
}

#pragma comment(linker, "/alternatename:??0Rva002BD020AIAttackState@@QAE@PAVStateMachine@@_N11PAVAttackExitConditionsInterface@@@Z=?j_0000bf3c@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva002BD020AIAttackState@@UAE@XZ=??1AIAttackState@@MAE@XZ")

StateReturnType AIGuardInnerState::onEnter()
{
	AIGuardInnerState *state = this;
	Coord3D guardPosition;
	{
	register Rva0015C570GuardMachine *machine = (Rva0015C570GuardMachine *)state->m_machine;
	union
		{
			void *asVoid;
			FindObjectByIDCall asMember;
		} findObjectCast;
		findObjectCast.asVoid = (void *)j_0001f253;
		Object *targetObject = (TheBfmeGameLogic->*findObjectCast.asMember)(
			machine->m_targetToGuard);
		union
		{
			void *asVoid;
			FindTeamByIDCall asMember;
		} findTeamCast;
		findTeamCast.asVoid = (void *)j_00044c2e;
		Team *targetTeam = (TheTeamFactory->*findTeamCast.asMember)(
			machine->m_teamToGuard);

		if (targetObject)
		{
			guardPosition = targetObject->m_position;
		}
		else if (targetTeam)
		{
			union
			{
				void *asVoid;
				EstimateTeamPositionCall asMember;
			} estimateTeamPositionCast;
			estimateTeamPositionCast.asVoid = (void *)j_000241fe;
			(targetTeam->*estimateTeamPositionCast.asMember)(&guardPosition);
		}
		else
		{
			guardPosition = ((Rva0015C570GuardMachine *)state->m_machine)->m_positionToGuard;
		}

	}

	register Rva0015C570GuardMachine *machine = (Rva0015C570GuardMachine *)state->m_machine;
	Object *nemesisObject = findBfmeObject(TheBfmeGameLogic,
		machine->m_nemesisToAttack);
	if (!nemesisObject)
		return STATE_SUCCESS;

	register Coord3D *guardCenter = &state->m_exitConditions.m_center;
	*guardCenter = guardPosition;
	Real visionRange = AI::getAdjustedVisionRangeForObject(
		getGuardOwner(machine), 7);
	const Real maximumVisionRange = 300.0f;
	visionRange = (_STL::min)(visionRange, maximumVisionRange);
	state->m_exitConditions.m_radiusSqr = visionRange * visionRange;
	state->m_exitConditions.m_conditionsToConsider = 5;

	Rva0015C570GuardMachine *machineForArea =
		(Rva0015C570GuardMachine *)state->m_machine;
	PolygonTrigger *guardArea = machineForArea->m_areaToGuard;
	if (guardArea)
	{
		union
		{
			void *asVoid;
			GetAreaValueCall asMember;
		} getAreaValueCast;
		getAreaValueCast.asVoid = (void *)j_00045a02;
		Real guardAreaRadius = (guardArea->*getAreaValueCast.asMember)();
		state->m_exitConditions.m_radiusSqr =
			(guardArea->*getAreaValueCast.asMember)() * guardAreaRadius;
		union
		{
			void *asVoid;
			GetCenterPointCall asMember;
		} getCenterPointCast;
		getCenterPointCast.asVoid = (void *)j_00007ad6;
		(guardArea->*getCenterPointCast.asMember)(guardCenter);
	}

	m_attackState = new(
		Rva002BD020AIAttackState::GLUE_NOT_IMPLEMENTED)
		Rva002BD020AIAttackState(
			getMachine(), false, true, false,
			&m_exitConditions);
	m_attackState->m_machine->setGoalObject(nemesisObject);
	m_frameAt48 = TheBfmeGameLogic->m_frame + 0xf;
	StateReturnType result = m_attackState->onEnter();
	return result == STATE_CONTINUE ? STATE_CONTINUE : STATE_SUCCESS;
}
