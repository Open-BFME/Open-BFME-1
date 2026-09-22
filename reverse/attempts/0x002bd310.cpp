// ?onEnter@Rva002BD310State@@UAE?AW4StateReturnType@@XZ
// partial score=0.99 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// ?onEnter@Rva002BD310State@@UAE?AW4StateReturnType@@XZ

#include "Lib/BaseType.h"

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
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
	void getPosition(Coord3D *position);
};

class TeamFactory
{
public:
	Team *findTeamByID(UnsignedInt id);
};

extern TeamFactory *TheTeamFactory;

struct BfmeVec1263
{
	Real x;
	Real y;
	Real z;
};

class BfmeA1263
{
public:
	void bfmeGet1263(BfmeVec1263 *out);

	unsigned char m_pad00[0x1c];
	Int m_1c;
	Int m_20;
	Int m_24;
	Int m_28;
	unsigned char m_pad2c[4];
	unsigned char m_30;
};

class TAiData
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_guardChaseUnitFrames;
};

class AI
{
public:
	static Real getAdjustedVisionRangeForObject(const Object *object, Int flags);

	unsigned char m_pad00[0x14];
	TAiData *m_aiData;
};

extern AI *TheAI;
extern const Real g_bfmeUint32Scale;

class Rva002BD310Machine
{
public:
	unsigned char m_pad00[0x10];
	Object *m_owner;
	unsigned char m_pad14[0x30];
	Int m_targetToGuard;
	UnsignedInt m_teamToGuard;
	BfmeA1263 *m_areaToGuard;
	Coord3D m_positionToGuard;
	Coord3D m_explicitPosition;
	unsigned char m_hasExplicitPosition;
	unsigned char m_pad69[3];
	Int m_nemesisToAttack;
	Int m_guardMode;
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

class Rva002BD310ExitConditions : public AttackExitConditionsInterface
{
public:
	Int m_conditionsToConsider;
	Coord3D m_center;
	Real m_radiusSqr;
	UnsignedInt m_attackGiveUpFrame;
};

class AIAttackState
{
protected:
	virtual ~AIAttackState();

public:
	AIAttackState(StateMachine *machine, Bool follow, Bool attackingObject,
		Bool forceAttacking, AttackExitConditionsInterface *conditions);
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

class Rva002BD310State
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
	virtual void onExit();
	virtual StateReturnType update();
	virtual Bool isIdle() const;
	virtual Bool isAttack() const;
	virtual Bool isBusy() const;

	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[4];
	Rva002BD310ExitConditions m_exitConditions;
	AIAttackState *m_attackState;
};

inline Object *findBfmeObject(GameLogic *logic, Int id)
{
	return logic->findObjectByID(id);
}

StateReturnType Rva002BD310State::onEnter()
{
	Rva002BD310State *state = this;
	Coord3D position;
	Rva002BD310Machine *machine =
		(Rva002BD310Machine *)state->m_machine;
	Int guardMode = machine->m_guardMode;
	if (guardMode == 1)
		return STATE_SUCCESS;
	{
		Object *target = TheBfmeGameLogic->findObjectByID(
			machine->m_targetToGuard);
		Team *team = TheTeamFactory->findTeamByID(machine->m_teamToGuard);

		if (target)
		{
			position = target->m_position;
		}
		else if (team)
		{
			team->getPosition(&position);
		}
		else
		{
			position = ((Rva002BD310Machine *)state->m_machine)->m_positionToGuard;
		}
	}

	machine = (Rva002BD310Machine *)state->m_machine;
	register Object *nemesis = findBfmeObject(TheBfmeGameLogic,
		machine->m_nemesisToAttack);
	if (!nemesis)
		return STATE_SUCCESS;

	Object *owner = machine->m_owner;
	Real range = AI::getAdjustedVisionRangeForObject(owner, 3);
	Rva002BD310Machine *machineForArea =
		(Rva002BD310Machine *)state->m_machine;
	BfmeA1263 *area = machineForArea->m_areaToGuard;
	if (area)
	{
		if (machineForArea->m_hasExplicitPosition)
			position = machineForArea->m_explicitPosition;
		else
			area->bfmeGet1263((BfmeVec1263 *)&position);
	}

	state->m_exitConditions.m_center = position;
	state->m_exitConditions.m_radiusSqr = range * range;
	AI *ai = TheAI;
	TAiData *aiData = ai->m_aiData;
	Real chaseFrames;
	if ((Real)aiData->m_guardChaseUnitFrames < 8.0f)
		chaseFrames = 8.0f;
	else
		chaseFrames = (Real)TheAI->m_aiData->m_guardChaseUnitFrames;
	state->m_exitConditions.m_attackGiveUpFrame =
		(UnsignedInt)(chaseFrames + (Real)TheBfmeGameLogic->m_frame);
	state->m_exitConditions.m_conditionsToConsider = 7;

	m_attackState = ::new
		AIAttackState(m_machine, false, true, false, &m_exitConditions);
	m_attackState->m_machine->setGoalObject(nemesis);
	StateReturnType result = m_attackState->onEnter();
	return result == STATE_CONTINUE ? STATE_CONTINUE : STATE_SUCCESS;
}
