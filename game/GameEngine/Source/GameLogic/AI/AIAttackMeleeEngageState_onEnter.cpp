// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
// ?onEnter@AIAttackMeleeEngageState@@UAE?AW4StateReturnType@@XZ
// RVA 0x00178140, 641 bytes. Vtable 0x01099848 (installed by the exact
// AIAttackMeleeEngageState constructor 0x0017F8D0) slot 4 routes through ILT
// 0x0002F5E5 to this body; slot 4 is State::onEnter (ZH StateMachine.h).
// The base call reaches AIInternalMoveToState::onEnter through ILT 0x00021E27
// and computePath is vtable slot 17 (+0x44), as in
// AIAttackMeleeEngageState_computePath.cpp. Field names follow the landed
// AIAttackMeleeEngageState_xfer.cpp; Thing+0x38, State+0x1C,
// AIInternalMoveToState+0x4C and Object+0x344 are name_oracle witnesses.
// The fire-weapon substate is built with the ZH State::getMachine() inline
// accessor, the same lever AIAttackMeleeEngageState_xfer.cpp documents: with
// a plain m_machine read VC7.1 rotates every later EAX/ECX/EDX choice
// (64 bytes from retail +0xB2).
// The in-range block is the ZH AIIdleState updateGoal/goalPosition pair; the
// file literal (VA 0x0109769C) and line 0x1C9A are read from retail.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "coord.h"

enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1, STATE_FAILURE = -2 };

class Object;
class NotifyWeaponFiredInterface;
class CRCParameterCheck;

template<int N> class UnresolvedVtablePrefix : public UnresolvedVtablePrefix<N-1> { public: virtual void slot(char (*)[N])=0; };
template<> class UnresolvedVtablePrefix<0> {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getOwner() { return m_owner; }
	Object *getGoalObject();
	Bool isGoalObjectDestroyed() const;

private:
	unsigned char m_pad000[0x10];
	Object *m_owner;
};

// Size 0x2C and constructor 0x001712C0 (ILT 0x0000FF1F), as in
// AIAttackMeleeEngageState_xfer.cpp.
class AIAttackFireWeaponState
{
public:
	AIAttackFireWeaponState(StateMachine *machine, NotifyWeaponFiredInterface *notify);

private:
	unsigned char m_storage[0x2c];
};

class AIUpdateInterface
{
public:
	void destroyPath();
};

// Retail call 0x00010910 -> 0x0016A6D0 takes the AI receiver and the
// goal-position address; ledger identity is still address-derived.
struct Rva0016A6D0Vec;
class Rva0016A6D0
{
public:
	void set(const Rva0016A6D0Vec *v);
};

// Object+0x208 receiver of the retail call 0x00006EEC -> 0x0029A7A0.
class Gen_0029A7A0
{
public:
	Bool bfmeFlagged() const;
};

enum WeaponSlotType;
class Weapon
{
public:
	Bool isWithinAttackRange(const Object *source, const Object *target, Int extra) const;
};

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Int getLayer() const;
	void setStatusBit(Int bit, Bool value);
	Bool testStatus(Int bit) const;

	unsigned char m_pad000[0x38];
	Coord3D m_cachedPos;
	unsigned char m_pad044[0x94 - 0x44];
	UnsignedInt m_field94;
	unsigned char m_pad098[0x204 - 0x98];
	AIUpdateInterface *m_ai;
	Gen_0029A7A0 *m_field208;
	unsigned char m_pad20c[0x214 - 0x20c];
	void *m_field214;
	unsigned char m_pad218[0x344 - 0x218];
	unsigned char m_privateStatus;
};

class Pathfinder
{
public:
	void updateGoal(Object *obj, const Coord3D *pos, Int layer, const char *file, Int line);
	Bool goalPosition(Object *obj, Coord3D *pos);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	unsigned char m_pad000[0xc];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;
extern bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *check, const char *format, ...);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State : public UnresolvedVtablePrefix<4>
{
public:
	StateMachine *getMachine() { return m_machine; }
	Object *getMachineOwner() { return m_machine->getOwner(); }
	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }

private:
	unsigned char m_unmodelled004[0x18];
	StateMachine *m_machine;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void slot14()=0;
	virtual void slot18()=0;
	virtual void slot1C()=0;
	virtual void slot20()=0;
	virtual void slot24()=0;
	virtual void slot28()=0;
	virtual void slot2C()=0;
	virtual void slot30()=0;
	virtual void slot34()=0;
	virtual void slot38()=0;
	virtual void slot3C()=0;
	virtual void slot40()=0;
	virtual Bool computePath()=0;

protected:
	unsigned char m_unmodelled020[0x4c - 0x20];
	Bool m_adjustDestinations;
};

class AIAttackMeleeEngageState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	AIAttackFireWeaponState *m_field50;
	Int m_field54;
	UnsignedInt m_field58;
	Coord3D m_field5C;
	unsigned char m_field68[8];
	UnsignedInt m_field70;
	Bool m_field74;
	Bool m_field75;
	unsigned char pad075[2];
	NotifyWeaponFiredInterface *m_field78;
};

StateReturnType AIAttackMeleeEngageState::onEnter()
{
	Object *source = getMachineOwner();
	if (getMachine()->isGoalObjectDestroyed())
		return STATE_SUCCESS;

	if (!m_field50)
		m_field50 = new AIAttackFireWeaponState(getMachine(), m_field78);
	m_field54 = -1;

	if (Glo012F0239 && TheCRCParameterCheck != 0)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: setAdjustDestination(FALSE) 35");
	m_adjustDestinations = false;
	m_field58 = 0;
	m_field74 = false;
	m_field70 = 0;

	AIUpdateInterface *ai = source->m_ai;
	Object *victim = getMachineGoalObject();
	if (!victim || (victim->m_field208 && victim->m_field208->bfmeFlagged()) ||
		(victim->m_privateStatus & 1) || (victim->m_field94 & 0x20000))
		return STATE_FAILURE;

	Weapon *weapon = source->getCurrentWeapon(0);
	if (!weapon)
		return STATE_FAILURE;

	if (weapon->isWithinAttackRange(source, victim, 0))
	{
		Coord3D pos;
		pos.set(&source->m_cachedPos);
		TheAI->pathfinder()->updateGoal(source, &pos, source->getLayer(),
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x1c9a);
		if (TheAI->pathfinder()->goalPosition(source, &pos))
			((Rva0016A6D0 *)ai)->set((const Rva0016A6D0Vec *)&pos);
		source->setStatusBit(28, true);
		return STATE_SUCCESS;
	}

	m_field5C = victim->m_cachedPos;
	if (source->testStatus(37) && source->m_field214)
	{
		source->setStatusBit(28, false);
		return STATE_FAILURE;
	}

	ai->destroyPath();
	if (Glo012F0239 && TheCRCParameterCheck != 0)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: ComputePath27");
	if (!computePath())
		return STATE_FAILURE;
	if (m_field74)
		return STATE_CONTINUE;

	StateReturnType ret = AIInternalMoveToState::onEnter();
	if (Glo012F0239 && TheCRCParameterCheck != 0)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: setAdjustDestination(TRUE) 36");
	m_adjustDestinations = true;
	return ret;
}
