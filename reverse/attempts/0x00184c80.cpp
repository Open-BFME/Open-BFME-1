// ?onEnter@AIAttackSquadState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// BFME AIAttackSquadState entry.  The local views preserve the retail state
// layout: State::m_machine at +0x1c, the nested machine at +0x24, and the
// reset flag at +0x28.

typedef unsigned char Bool;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object;
class BfmeOutOfWeaponRangeObject;
class BfmeOutOfWeaponRangeWeapon;
class AIUpdateInterface;
enum WeaponSlotType { PRIMARY_WEAPON = 0 };

// The outer AIStateMachine and the nested attack machine share these BFME
// virtual positions.  Slot 9 is the factory installed in AIStateMachine's
// vtable at 0x0109AEF8; slots 7 and 14 are initDefaultState and setGoalObject.
class BfmeAttackStateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual StateReturnType initDefaultState() = 0;
	virtual void slot20() = 0;
	virtual BfmeAttackStateMachine *createAttackMachine() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(Object *object) = 0;

	unsigned char m_padding004[0x0c];
	Object *m_owner;
	Object *getOwner() const { return m_owner; }
};

// The helper's name is still synthetic in the ledger, but its existing exact
// body is a matched dependency.  Reinterpret only its return type: retail
// consumes AL while retaining the owner in EDI across this cdecl call.
extern void d_0016b010();
extern void j_0000ab7d();
extern void j_000125e9();

class BfmeOutOfWeaponRangeObject
{
public:
	BfmeOutOfWeaponRangeWeapon *getCurrentWeapon(int slot);

	unsigned char m_padding000[0x204];
	AIUpdateInterface *m_ai;
};

class BfmeOutOfWeaponRangeWeapon
{
public:
	bool isWithinAttackRange(const BfmeOutOfWeaponRangeObject *source,
		const BfmeOutOfWeaponRangeObject *target, int extra) const;
};

class BfmeAIUpdateVictimThunk
{
public:
	void clearCurrentVictim(const Object *victim);
};

class AIUpdateInterface
{
public:
	void friend_setGoalObject(Object *object);

	unsigned char m_padding000[0x33a];
	Bool m_attackDisabled;
};

class Object
{
public:
	AIUpdateInterface *getAI() const { return m_ai; }
	unsigned char m_padding000[0x204];
	AIUpdateInterface *m_ai;
};

// State's real four virtual positions precede AIAttackSquadState::onEnter.
// Keeping the machine field in the base also models the retail +0x1c access.
class State
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;

	unsigned char m_padding004[0x18];
	BfmeAttackStateMachine *m_machine;
};

// ?onEnter@AIAttackSquadState@@UAE?AW4StateReturnType@@XZ
class AIAttackSquadState : public State
{
public:
	virtual StateReturnType onEnter();
	Object *chooseVictim();

	unsigned char m_padding020[4];
	BfmeAttackStateMachine *m_attackSquadMachine;
	Bool m_attackFlag;
};

static Bool bfmeAttackEligibility()
{
	typedef Bool (__cdecl *Function)();
	return reinterpret_cast<Function>(d_0016b010)();
}

StateReturnType AIAttackSquadState::onEnter()
{
	Object *owner = m_machine->getOwner();
	if (owner == 0)
		return STATE_FAILURE;

	m_attackSquadMachine = m_machine->createAttackMachine();
	AIUpdateInterface *ai = owner->m_ai;
	Object *victim = chooseVictim();
	BfmeOutOfWeaponRangeWeapon *weapon =
		reinterpret_cast<BfmeOutOfWeaponRangeObject *>(owner)->getCurrentWeapon(0);
	if (weapon != 0 && victim != 0 &&
		!weapon->isWithinAttackRange(
			reinterpret_cast<BfmeOutOfWeaponRangeObject *>(owner),
			reinterpret_cast<BfmeOutOfWeaponRangeObject *>(victim), 0))
	{
		if (!bfmeAttackEligibility() || ai->m_attackDisabled)
			return STATE_FAILURE;
	}

	m_attackSquadMachine->setGoalObject(victim);
	if (ai != 0)
	{
		reinterpret_cast<BfmeAIUpdateVictimThunk *>(ai)->clearCurrentVictim(
		victim);
		m_machine->setGoalObject(victim);
		typedef void (AIUpdateInterface::*SetGoalObjectCall)(Object *);
		union
		{
			void *raw;
			SetGoalObjectCall member;
		} setGoalObjectCast;
		setGoalObjectCast.raw = (void *)j_000125e9;
		(ai->*setGoalObjectCast.member)(victim);
	}
	m_attackFlag = 0;
	return m_attackSquadMachine->initDefaultState();
}
