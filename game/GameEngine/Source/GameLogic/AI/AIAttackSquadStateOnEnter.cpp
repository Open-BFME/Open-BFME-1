// cl: /DNDEBUG /MD /EHsc
// ?onEnter@AIAttackSquadState@@UAE?AW4StateReturnType@@XZ   retail 0x00184C80..0x00184D22 (162 bytes)
// ?rva0016B010@@YAEPAVObject@@@Z                             retail 0x0016B010..0x0016B08B (123 bytes)
//
// AIAttackSquadState::onEnter is slot 4 of the AIAttackSquadState vtable
// 0x01097E30.  Its tail (store the new machine at +0x24, setGoalObject(victim),
// return initDefaultState()) is the Zero Hour AIStates.cpp body; BFME adds the
// owner check, the range/eligibility gate and the AI victim/goal updates.
//
// rva0016B010 is a STATIC helper: retail calls it directly (no ILT) from three
// sites (0x00174F2A, 0x00184CCF, 0x00184EFF) and passes the owner in EDI, a
// compiler-private convention.  Compiling the helper in the caller's TU lets
// VC7.1 choose that convention and the caller's EDI/EBX assignment
// (docs/shape_levers.md "Compiler-private ABI: compile the static helper with
// its caller").  Its identity is not proven, so it keeps the address token.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

typedef unsigned char Bool;

enum { INVALID_STATE_ID = 999999 };	// Zero Hour StateMachine.h
enum { AI_IDLE = 0, AI_ATTACK_OBJECT = 10, AI_PICK_UP_CRATE = 39 };

class Object;
class State;

// BFME State: one vptr, m_ID at +4, m_machine at +0x1c (landed precedent
// AIMoveAwayFromRepulsorsState_onExit.cpp; State+0x1c witnessed).
class StateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual StateReturnType updateStateMachine() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual StateReturnType initDefaultState() = 0;
	virtual StateReturnType setState(unsigned int state) = 0;
	virtual StateMachine *slot24() = 0;	// AIStateMachine slot 9 -> 0x00184C00 factory
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(Object *object) = 0;

	Object *getOwner() const { return m_owner; }
	int getCurrentStateID() const;
	Object *getGoalObject();

	unsigned char m_pad04[0x10 - 0x04];
	Object *m_owner;			// +0x10 witnessed
	unsigned char m_pad14[0x1c - 0x14];
	State *m_currentState;		// +0x1c witnessed
};

class State
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;

	int m_ID;
	unsigned char m_pad08[0x1c - 0x08];
	StateMachine *m_machine;	// +0x1c witnessed
};

// Zero Hour StateMachine::getCurrentStateID.
inline int StateMachine::getCurrentStateID() const
{
	return m_currentState ? m_currentState->m_ID : INVALID_STATE_ID;
}

class Rva001E1770ByteField { public: unsigned char get() const; };
class Rva001E1780ByteField { public: unsigned char get() const; };

class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *target, int extra) const;

	void *m_vptr;
	void *dword_4;
};

class Player
{
public:
	unsigned char m_pad00[0x2c];
	int dword_2c;
};

class AIUpdateInterface
{
public:
#define SLOT(n) virtual void slot##n() = 0;
#define SLOT8(a) SLOT(a##0) SLOT(a##1) SLOT(a##2) SLOT(a##3) SLOT(a##4) SLOT(a##5) SLOT(a##6) SLOT(a##7)
#define SLOT64(a) SLOT8(a##0) SLOT8(a##1) SLOT8(a##2) SLOT8(a##3) SLOT8(a##4) SLOT8(a##5) SLOT8(a##6) SLOT8(a##7)
	SLOT64(0) SLOT64(1)
#undef SLOT64
#undef SLOT8
#undef SLOT
	virtual int slot200() = 0;

	void setCurrentVictim(const Object *victim);
	void friend_setGoalObject(Object *object);

	unsigned char m_pad004[0x30 - 0x04];
	StateMachine *m_stateMachine;	// +0x30 witnessed
	unsigned char m_pad034[0x32f - 0x34];
	Bool byte_32f;
	unsigned char m_pad330[0x33a - 0x330];
	Bool byte_33a;
};

enum WeaponSlotType { PRIMARY_WEAPON = 0 };

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	bool testStatus(int status) const;
	void *find(int slot);
	Player *getControllingPlayer() const;

	unsigned char m_pad000[0x90];
	unsigned int m_status;
	unsigned char m_pad094[0x1f5 - 0x94];
	Bool byte_1f5;
	unsigned char m_pad1f6[0x204 - 0x1f6];
	AIUpdateInterface *m_ai;	// receiver of the matched AIUpdateInterface callees
	unsigned char m_pad208[0x214 - 0x208];
	Object *m_containedBy;
	unsigned char m_pad218[0x344 - 0x218];
	unsigned char m_privateStatus;
};

class AIAttackSquadState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	Object *chooseVictim();

	unsigned char m_pad20[0x24 - 0x20];
	StateMachine *m_attackSquadMachine;	// Zero Hour member at the same offset
	Bool byte_28;
};

static Bool rva0016B010(Object *obj)
{
	Weapon *weapon = (Weapon *)obj->find(0);
	if (weapon && (((Rva001E1770ByteField *)weapon->dword_4)->get() ||
			((Rva001E1780ByteField *)weapon->dword_4)->get()))
		return 1;
	if (obj->getControllingPlayer()->dword_2c)
		return 1;
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return 1;
	return ai->m_stateMachine->getCurrentStateID() == 0x3e || ai->slot200() != 2 ||
		ai->byte_32f || obj->byte_1f5;
}

StateReturnType AIAttackSquadState::onEnter()
{
	Object *owner = m_machine->getOwner();
	if (owner == 0)
		return STATE_FAILURE;

	m_attackSquadMachine = m_machine->slot24();
	AIUpdateInterface *ai = owner->m_ai;
	Object *victim = chooseVictim();
	Weapon *weapon = owner->getCurrentWeapon(0);
	if (weapon != 0 && victim != 0 && !weapon->isWithinAttackRange(owner, victim, 0))
	{
		if (!rva0016B010(owner) || ai->byte_33a)
			return STATE_FAILURE;
	}

	m_attackSquadMachine->setGoalObject(victim);
	if (ai != 0)
	{
		ai->setCurrentVictim(victim);
		m_machine->setGoalObject(victim);
		ai->friend_setGoalObject(victim);
	}
	byte_28 = 0;
	return m_attackSquadMachine->initDefaultState();
}

struct Coord3D { float x, y, z; };
class Pathfinder
{
public:
	unsigned char m_padding00[0x0c];
};

class AI
{
public:
	unsigned char m_padding00[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

// These ABI views keep the verified ILT routes at this retail call site.
// In particular the pathfinder receives the current Weapon* as its third argument.
class BfmePathfinderMethods
{
public:
	bool check(const Object *source, const Coord3D *goal,
		const Weapon *weapon, int extra);
};
class BfmeAIUpdateMethods
{
public:
	Object *checkForCrateToPickup();
};
class BfmeThingMethods
{
public:
	bool isKindOf(int kind) const;
};
// ?update@AIAttackSquadState@@UAE?AW4StateReturnType@@XZ
// Retail vtable 0x01097E30 slot 6 routes here. Keep the actual rva0016B010
// helper in this TU: the compiler passes its Object* in EDI, not on the stack.
// The update and onEnter callers each require that compiler-private ABI.
StateReturnType AIAttackSquadState::update()
{
	if (this->m_attackSquadMachine == 0)
		return STATE_FAILURE;

	if ((this->m_machine->m_owner->m_status & 0x10000000) != 0)
		this->byte_28 = true;

	Object *owner = this->m_machine->m_owner;
	Object *goal;
	AIUpdateInterface *ai = owner->m_ai;
	goal = this->m_machine->getGoalObject();
	if (goal != this->m_attackSquadMachine->getGoalObject())
		this->m_attackSquadMachine->setGoalObject(goal);

	StateReturnType attackStatus = this->m_attackSquadMachine->updateStateMachine();
	attackStatus = attackStatus > STATE_CONTINUE ? STATE_CONTINUE : attackStatus;

	if (this->m_attackSquadMachine == 0)
		return STATE_CONTINUE;
	State *current = this->m_attackSquadMachine->m_currentState;
	if (current == 0 || current->m_ID != AI_IDLE)
		return attackStatus;

	Weapon *weapon = owner->getCurrentWeapon(0);
	if (weapon == 0)
		return STATE_FAILURE;

	if (goal != 0 && (goal->m_privateStatus & 1) == 0)
	{
		if (!((BfmePathfinderMethods *)TheAI->m_pathfinder)->check(owner,
			reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(goal) + 0x38),
			weapon, 0))
			return STATE_FAILURE;
	}

	if (owner->testStatus(0x25) && owner->m_containedBy != 0)
		return STATE_SUCCESS;

	Object *crate = ((BfmeAIUpdateMethods *)ai)->checkForCrateToPickup();
	if (crate != 0)
	{
		this->m_attackSquadMachine->setGoalObject(crate);
		this->m_attackSquadMachine->setState(AI_PICK_UP_CRATE);
		return STATE_CONTINUE;
	}

	goal = chooseVictim();
	if (goal == 0)
		return STATE_SUCCESS;

	if (owner->testStatus(0x40) ||
		((BfmeThingMethods *)goal)->isKindOf(0x36) ||
		((BfmeThingMethods *)goal)->isKindOf(0x9a) ||
		((BfmeThingMethods *)goal)->isKindOf(0x5d) ||
		goal->getControllingPlayer() != owner->getControllingPlayer())
	{
		if (!weapon->isWithinAttackRange(owner, goal, 0))
		{
			if (!rva0016B010(owner))
				return STATE_FAILURE;
			if (ai->byte_33a)
				return STATE_FAILURE;
		}

		this->m_attackSquadMachine->setGoalObject(goal);
		ai->setCurrentVictim(goal);
		this->m_machine->setGoalObject(goal);
		ai->friend_setGoalObject(goal);
		this->m_attackSquadMachine->setState(AI_ATTACK_OBJECT);
		return STATE_CONTINUE;
	}

	ai->friend_setGoalObject(0);
	this->m_machine->setGoalObject(0);
	this->m_attackSquadMachine->setGoalObject(0);
	return STATE_SUCCESS;
}
