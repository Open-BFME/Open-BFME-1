// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "coord.h"
enum StateReturnType { STATE_FAILURE=-2, STATE_SUCCESS=-1 };

// AIAttackMeleeHordeApproachTargetState::onEnter, retail RVA 0x001834E0.
// Identity proven by the constructor at 0x0017F610
// (AIAttackMeleeHordeApproachTargetStateCtor.cpp) installing the same
// vtable, by the shared field layout of the already-landed
// AIAttackMeleeHordeApproachTargetState::onExit sibling
// (AIAttackMeleeHordeApproachTargetState_onExit.cpp), and by the three
// "CritterDesync: ..." strings embedded in this body (read from the
// retail EXE at their DIR32 addresses).
// State +50/+54/+58 are cleared at retail +99/+9C/+9F; these are NOT
// m_goalPosition (+24). Unknown field semantics retain their offsets.
// docs/analysis/0x00172600.md proves the base-entry and cdecl logger ABI.
// Native virtual dispatch and repeated m_machine reads reproduce retail.
// Slot +68 yields the receiver for slot +124(Object*); both use thiscall.

class Object;
template<int N> class UnresolvedVtablePrefix : public UnresolvedVtablePrefix<N-1> { public: virtual void slot(char (*)[N])=0; };
template<> class UnresolvedVtablePrefix<0> {};

class HordeContainInterface : public UnresolvedVtablePrefix<73>
{
public:
	virtual Bool isMeleeTargetReady(Object *target) = 0;
};

class ContainModuleInterface : public UnresolvedVtablePrefix<26>
{
public:
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};


class StateMachine : public UnresolvedVtablePrefix<14>
{
public:
	virtual void call38(Int)=0;
	unsigned char m_pad004[0xc];
	Object *m_owner;
};

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_COMPUTER
};

class Player
{
public:
	unsigned char m_pad000[0x2c];
	PlayerType m_playerType;
};

class AIUpdateInterface
{
public:
	unsigned char m_pad000[0x33a];
	unsigned char m_playerIdle;
};

class Object
{
public:
	unsigned char m_pad000[0x98];
	UnsignedInt m_statusWordAt0x98;
	unsigned char m_pad09c[0x1fc - 0x9c];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[0x204 - 0x200];
	AIUpdateInterface *m_ai;
};

extern void j_00020824();
extern void j_0000e570();
extern void j_0000432c();
extern void j_0002056d();
extern void j_00004c37();
extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *check, const char *format, ...);

extern bool Glo012F0239;
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;

static Player *ownerGetControllingPlayer(Object *self)
{
	struct Thunk { void *call(); };
	typedef void *(Thunk::*Function)();
	union { void (*raw)(); Function member; } fn;
	fn.raw = j_00020824;
	return reinterpret_cast<Player *>((reinterpret_cast<Thunk *>(self)->*fn.member)());
}

static Object *machineGetGoalObject(StateMachine *self)
{
	struct Thunk { void *call(); };
	typedef void *(Thunk::*Function)();
	union { void (*raw)(); Function member; } fn;
	fn.raw = j_0000e570;
	return reinterpret_cast<Object *>((reinterpret_cast<Thunk *>(self)->*fn.member)());
}

static Bool machineIsGoalObjectDestroyed(StateMachine *self)
{
	struct Thunk { Bool call(); };
	typedef Bool (Thunk::*Function)();
	union { void (*raw)(); Function member; } fn;
	fn.raw = j_0000432c;
	return (reinterpret_cast<Thunk *>(self)->*fn.member)();
}

static Bool bfmeMeleeHordeTargetInvalid(Object *attacker, Object *target)
{
	typedef Bool (__cdecl *Call)(Object *, Object *);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = (void (*)(void))j_0002056d;
	return fn.member(attacker, target);
}

static Bool passesWeaponTargetPredicate(Object *attacker, Object *target)
{
	typedef Bool (__cdecl *Call)(void *, void *);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = (void (*)(void))j_00004c37;
	return fn.member(attacker, target);
}

class AIInternalMoveToState : public UnresolvedVtablePrefix<4>
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
	unsigned char m_unmodelled004[0x18];
	StateMachine *m_machine;
};

class AIAttackMeleeHordeApproachTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();

private:
	unsigned char m_unmodelled020[4];
	Coord3D m_goalPosition;
	unsigned char m_unmodelled030[0x4c - 0x30];
	unsigned char m_adjustDestinations;
	unsigned char m_unmodelled04d[3];
	Int m_field50;
	Int m_field54;
	Int m_field58;
	Int m_field5c;
	unsigned char m_successOnPathFailure;
	unsigned char m_isInitialApproach;
};

StateReturnType AIAttackMeleeHordeApproachTargetState::onEnter()
{
	StateMachine *machine = m_machine;
	Object *owner = machine->m_owner;

	Player *player = ownerGetControllingPlayer(owner);
	register PlayerType playerType = player->m_playerType;
	if (playerType == PLAYER_COMPUTER)
		m_isInitialApproach = false;

	Object *goalObject = machineGetGoalObject(m_machine);
	if (goalObject == 0)
		return STATE_FAILURE;

	if (machineIsGoalObjectDestroyed(m_machine))
		return STATE_SUCCESS;

	if (owner->m_contain != 0 && !bfmeMeleeHordeTargetInvalid(owner, goalObject))
	{
		HordeContainInterface *hordeContain =
			owner->m_contain->getHordeContainInterface();
		if (hordeContain != 0 && hordeContain->isMeleeTargetReady(goalObject))
			return STATE_SUCCESS;
	}

	if ((owner->m_statusWordAt0x98 & 8) != 0 || owner->m_ai->m_playerIdle != 0)
	{
		if (!passesWeaponTargetPredicate(owner, goalObject))
		{
			m_machine->call38(0);
			return STATE_FAILURE;
		}
		return STATE_SUCCESS;
	}

	m_field50 = 0;
	m_field54 = 0;
	m_field58 = 0;
	m_field5c = -5;

	if (Glo012F0239 && TheCRCParameterCheck != 0)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: ComputePath11");

	if (!computePath())
		return m_successOnPathFailure ? STATE_SUCCESS : STATE_FAILURE;

	if (Glo012F0239 && TheCRCParameterCheck != 0)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: setAdjustDestination(FALSE) 24");

	m_adjustDestinations = 0;
	StateReturnType baseResult = AIInternalMoveToState::onEnter();

	if (Glo012F0239 && TheCRCParameterCheck != 0)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: setAdjustDestination(TRUE) 25");

	m_adjustDestinations = m_isInitialApproach;
	return baseResult;
}
