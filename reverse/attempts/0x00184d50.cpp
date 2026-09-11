// ?update@AIAttackSquadState@@UAE?AW4StateReturnType@@XZ
// partial score=0.7 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// readable body of ?update@AIAttackSquadState@@UAE?AW4StateReturnType@@XZ
// BFME layout reconstruction for retail RVA 0x00184D50.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum
{
	AI_IDLE = 0,
	AI_ATTACK_OBJECT = 10,
	AI_PICK_UP_CRATE = 39
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class Player;
class Weapon;
class AIUpdateInterface;
class Pathfinder;

// BFME's current state stores its ID at +0x04.
class BfmeCurrentState
{
public:
	UnsignedByte m_padding00[4];
	UnsignedInt m_id;
};

// The nested attack machine has updateStateMachine at vtable +0x10,
// setState at +0x20, and setGoalObject at +0x38.  Its owner and current
// state are the BFME fields at +0x10 and +0x1c.
class BfmeAttackStateMachine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual StateReturnType updateStateMachine() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual StateReturnType setState(UnsignedInt state) = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(const Object *object) = 0;
	Object *getGoalObject();
	__forceinline Object *getOwner() { return m_owner; }

	UnsignedByte m_padding04[0x10 - 4];
	Object *m_owner;
	UnsignedByte m_padding14[0x1c - 0x14];
	BfmeCurrentState *m_currentState;
};

// State::m_machine is the BFME +0x1c member.  Only its size and the derived
// field offsets matter to this body.
class State
{
public:
	virtual void slot00() = 0;
	UnsignedByte m_padding04[0x1c - 4];
	BfmeAttackStateMachine *m_machine;
	__forceinline Object *getMachineOwner() { return m_machine->getOwner(); }
	const Object *getMachineOwner() const { return m_machine->getOwner(); }
};

class AIAttackSquadState : public State
{
public:
	virtual StateReturnType update();

	UnsignedByte m_padding20[4];
	BfmeAttackStateMachine *m_attackSquadMachine;
	Bool m_attackFlag;
};

class Object
{
public:
	virtual void slot00() = 0;
	UnsignedByte m_padding00[0x90 - 4];
	UnsignedInt m_status;
	UnsignedByte m_padding94[0x204 - 0x94];
	AIUpdateInterface *m_ai;
	UnsignedByte m_padding208[0x214 - 0x208];
	Object *m_containedBy;
	UnsignedByte m_padding218[0x344 - 0x218];
	UnsignedByte m_field344;
	__forceinline AIUpdateInterface *getAI() const { return m_ai; }
};

class AIUpdateInterface
{
public:
	UnsignedByte m_padding00[0x33a];
	UnsignedByte m_field33a;
};

class Pathfinder
{
public:
	UnsignedByte m_padding00[0x0c];
};

class AI
{
public:
	UnsignedByte m_padding00[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

extern void j_0000e570();
extern void j_00031a7f();
extern void j_00032b46();
extern void j_000016a4();
extern void j_000265a8();
extern void j_0000ab7d();
extern void j_0003251f();
extern void j_00020824();
extern void j_0002e85c();
extern void j_0004ab4c();
extern void j_000125e9();
extern Bool d_0016b010();

#pragma comment(linker, "/alternatename:?getGoalObject@BfmeAttackStateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")

class BfmeObjectMethods
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Bool testStatus(Int status) const;
	Player *getControllingPlayer() const;
};

class BfmePathfinderMethods
{
public:
	Bool check(const Object *source, const Coord3D *goal,
		const Weapon *weapon, Int extra);
};

class BfmeAIUpdateMethods
{
public:
	Object *checkForCrateToPickup();
	void clearCurrentVictim(const Object *victim);
	void friend_setGoalObject(Object *goal);
};

class BfmeChooseVictimMethods
{
public:
	Object *chooseVictim();
};

class BfmeThingMethods
{
public:
	Bool isKindOf(Int kind) const;
};

class BfmeWeaponMethods
{
public:
	Bool isWithinAttackRange(const Object *source, const Object *target,
		Int extra) const;
};

	#pragma comment(linker, "/alternatename:?getCurrentWeapon@BfmeObjectMethods@@QAEPAVWeapon@@PAW4WeaponSlotType@@@Z=?j_00031a7f@@YAXXZ")
#pragma comment(linker, "/alternatename:?testStatus@BfmeObjectMethods@@QBE_NH@Z=?j_000016a4@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@BfmeObjectMethods@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?check@BfmePathfinderMethods@@QAE_NPBVObject@@PBUCoord3D@@PBVWeapon@@H@Z=?j_00032b46@@YAXXZ")
#pragma comment(linker, "/alternatename:?checkForCrateToPickup@BfmeAIUpdateMethods@@QAEPAVObject@@XZ=?j_000265a8@@YAXXZ")
#pragma comment(linker, "/alternatename:?clearCurrentVictim@BfmeAIUpdateMethods@@QAEXPBVObject@@@Z=?j_0004ab4c@@YAXXZ")
#pragma comment(linker, "/alternatename:?friend_setGoalObject@BfmeAIUpdateMethods@@QAEXPAVObject@@@Z=?j_000125e9@@YAXXZ")
#pragma comment(linker, "/alternatename:?chooseVictim@BfmeChooseVictimMethods@@QAEPAVObject@@XZ=?j_0000ab7d@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@BfmeThingMethods@@QBE_NH@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?isWithinAttackRange@BfmeWeaponMethods@@QBE_NPBVObject@@0H@Z=?j_0002e85c@@YAXXZ")

// ?update@AIAttackSquadState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIAttackSquadState::update()
{
	if (this->m_attackSquadMachine == 0)
		return STATE_FAILURE;

	if ((this->m_machine->m_owner->m_status & 0x10000000) != 0)
		this->m_attackFlag = true;

	Object *owner = this->m_machine->m_owner;
	Object *goal;
	AIUpdateInterface *ai = owner->getAI();
	goal = this->m_machine->getGoalObject();
	if (goal != this->m_attackSquadMachine->getGoalObject())
		this->m_attackSquadMachine->setGoalObject(goal);

	StateReturnType attackStatus = this->m_attackSquadMachine->updateStateMachine();
	attackStatus = attackStatus > STATE_CONTINUE ? STATE_CONTINUE : attackStatus;

	if (this->m_attackSquadMachine == 0)
		return STATE_CONTINUE;
	BfmeCurrentState *current = this->m_attackSquadMachine->m_currentState;
	if (current == 0 || current->m_id != AI_IDLE)
		return attackStatus;

	Weapon *weapon = ((BfmeObjectMethods *)owner)->getCurrentWeapon(0);
	if (weapon == 0)
		return STATE_FAILURE;

	if (goal != 0 && (goal->m_field344 & 1) == 0)
	{
		if (!((BfmePathfinderMethods *)TheAI->m_pathfinder)->check(owner,
			reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(goal) + 0x38),
			weapon, 0))
			return STATE_FAILURE;
	}

	if (((BfmeObjectMethods *)owner)->testStatus(0x25) && owner->m_containedBy != 0)
		return STATE_SUCCESS;

	Object *crate = ((BfmeAIUpdateMethods *)ai)->checkForCrateToPickup();
	if (crate != 0)
	{
		this->m_attackSquadMachine->setGoalObject(crate);
		this->m_attackSquadMachine->setState(AI_PICK_UP_CRATE);
		return STATE_CONTINUE;
	}

	goal = ((BfmeChooseVictimMethods *)this)->chooseVictim();
	if (goal == 0)
		return STATE_SUCCESS;

	if (((BfmeObjectMethods *)owner)->testStatus(0x40) ||
		((BfmeThingMethods *)goal)->isKindOf(0x36) ||
		((BfmeThingMethods *)goal)->isKindOf(0x9a) ||
		((BfmeThingMethods *)goal)->isKindOf(0x5d) ||
		((BfmeObjectMethods *)goal)->getControllingPlayer() !=
		((BfmeObjectMethods *)owner)->getControllingPlayer())
	{
		if (!((BfmeWeaponMethods *)weapon)->isWithinAttackRange(owner, goal, 0))
		{
			if (!d_0016b010())
				return STATE_FAILURE;
			if (!ai->m_field33a)
				return STATE_FAILURE;
		}

		this->m_attackSquadMachine->setGoalObject(goal);
		((BfmeAIUpdateMethods *)ai)->clearCurrentVictim(goal);
		this->m_machine->setGoalObject(goal);
		((BfmeAIUpdateMethods *)ai)->friend_setGoalObject(goal);
		this->m_attackSquadMachine->setState(AI_ATTACK_OBJECT);
		return STATE_CONTINUE;
	}

	((BfmeAIUpdateMethods *)ai)->friend_setGoalObject(0);
	this->m_machine->setGoalObject(0);
	this->m_attackSquadMachine->setGoalObject(0);
	return STATE_SUCCESS;
}
