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
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual StateReturnType initDefaultState() = 0;
	virtual void slot20() = 0;
	virtual StateMachine *slot24() = 0;	// AIStateMachine slot 9 -> 0x00184C00 factory
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(Object *object) = 0;

	Object *getOwner() const { return m_owner; }
	int getCurrentStateID() const;

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
	void *find(int slot);
	Player *getControllingPlayer() const;

	unsigned char m_pad000[0x1f5];
	Bool byte_1f5;
	unsigned char m_pad1f6[0x204 - 0x1f6];
	AIUpdateInterface *m_ai;	// receiver of the matched AIUpdateInterface callees
};

class AIAttackSquadState : public State
{
public:
	virtual StateReturnType onEnter();
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
