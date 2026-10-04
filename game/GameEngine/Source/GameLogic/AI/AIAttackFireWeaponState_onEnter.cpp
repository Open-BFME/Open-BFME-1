// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport
// BFME AIAttackFireWeaponState::onEnter, retail RVA 0x0017BF70 (586 bytes).
// Identity: constructor 0x001712C0 installs vtable VA 0x01097DC0;
// slot +0x10 routes through ILT 0x00027151 to this body. Adjacent slots
// are the independently named update and onExit; ZH AIStates.cpp onEnter
// witnesses the mood gate, common-team target and pre-fire sequence.
// Layout: State machine +0x1c, owner +0x10; Object AI +0x204 and team
// +0x23c; Weapon template +4, all decoded from this retail body.
// Preserve the template reload after the first predicate and the absence
// of friend_setGoalObject on the kind-0x6c rejection path.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef bool Bool;
typedef char Int8;
typedef int Int;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum MoodMatrixAction
{
	MM_Action_Attack = 2
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum WeaponStatus
{
	WEAPON_STATUS_NONE = 0
};

enum KindOfType
{
	KINDOF_INFANTRY = 0x36
};

struct Coord3D;

template <Int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags() {}

	BitFlags(_dummy_kInit, Int index)
	{
		m_bits.set(index);
	}

	void set(Int index)
	{
		m_bits._Unchecked_set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object;
class Player;
class StateMachine;
class AIUpdateInterface;
class Team;
class Weapon;
class BfmeThingEQT;
class BfmeHoldEQT;

class Thing
{
public:
	virtual void slot00() = 0;
	Bool isKindOf(KindOfType kind) const;
};

class BfmeCheckerNW
{
public:
	Int8 bfmeBusyNW();
};

class BfmeHordeMember
{
public:
	Bool bfmeBlocksFormationRefresh();
};

class TeamPrototype
{
};

class Team
{
public:
	Object *getTeamTargetObject();
	void setTeamTargetObject(const Object *target);

	TeamPrototype *getPrototype() const
	{
		return *(TeamPrototype * const *)((const char *)this + 4);
	}
};

class GameLogic
{
public:
	unsigned char m_padding000[0x3c];
	unsigned char m_flags;
};

extern GameLogic *TheGameLogic;

class AIUpdateInterface
{
public:
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
	void friend_setGoalObject(Object *object);
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

	Team *getTeam() const
	{
		return *(Team * const *)((const char *)this + 0x23c);
	}

	Player *getControllingPlayer() const;
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Bool testStatus(Int bit) const;
	void setStatus(const ObjectStatusMaskType &mask, Bool set);
	void setStatusBit(Int bit, Bool set);
	void preFireCurrentWeapon(const Object *victim, const Coord3D *position);

	Bool hasStatusByteBit(Int bit) const
	{
		return (*(const unsigned char *)((const char *)this + 0x98) & (1 << bit)) != 0;
	}

private:
	unsigned char m_padding000[0x200];
	AIUpdateInterface *m_ai;
};

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
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setGoalObject(const Object *object) = 0;

	Object *getGoalObject();
	void setGoalPosition(const Coord3D *position);

	unsigned char m_machineFields04[0x0c];
	Object *m_owner;
	unsigned char m_machineFields14[0x10];
	unsigned char m_goalPositionBytes[12];

	const Coord3D *getGoalPosition() const
	{
		return reinterpret_cast<const Coord3D *>(m_goalPositionBytes);
	}
};

class Gen_001e1790
{
public:
	Int8 m();
};

class Rva001E1770ByteField
{
public:
	unsigned char get() const;
};

class Weapon
{
public:
	void *m_vtable;
	void *m_template;

	Bool isWithinAttackRange(const Object *source, const Object *target,
		Int extra) const;
	Bool isWithinAttackRange(const Object *source, const Coord3D *position,
		Int extra) const;
	WeaponStatus getStatus() const;
};

extern Int8 bfmeCheckEQT(BfmeThingEQT *thing, void *arg, BfmeHoldEQT *hold);

class State
{
public:
	virtual ~State();

protected:
	unsigned char m_head[0x18];
	StateMachine *m_machine;
	unsigned char m_gap20[4];

	Object *getMachineOwner() const
	{
		return m_machine->m_owner;
	}
};

class AIAttackFireWeaponState : public State
{
public:
	virtual StateReturnType onEnter();

private:
	void *m_att;
	Bool m_28;
};

// Retail routes every call below through an ILT thunk, so each stand-in
// member is dispatched through a member-pointer union over that thunk
// instead of a linker alias.
// setGoalPosition keeps its alias: its thunk RVA 0x0000314D has no
// ?j_000314d@@YAXXZ row or pin anywhere (gen-thunk neighbours are
// 0x000314D0/D5/DA/DF), so the address is only reachable through the
// pinned ?setGoalPosition@StateMachine name at that RVA.
extern void j_000016a4();
extern void j_00032dee();
extern void j_0003960d();
extern void j_000296a9();
extern void j_0002a88d();
extern void j_0002e85c();
extern void j_0002e951();
extern void j_0000978c();
extern void j_00019349();
extern void j_00028f74();
extern void j_0003dc6c();

#pragma comment(linker, "/alternatename:?setGoalPosition@StateMachine@@QAEXPBUCoord3D@@@Z=?j_000314d@@YAXXZ")

StateReturnType AIAttackFireWeaponState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	m_28 = false;
	ObjectStatusMaskType firing(ObjectStatusMaskType::kInit, 81);
	obj->setStatus(firing, false);
	if ((ai->getMoodMatrixActionAdjustment(MM_Action_Attack) & 1) == 0)
		return STATE_FAILURE;

	Object *victim = m_machine->getGoalObject();
	if (victim && !obj->hasStatusByteBit(0))
	{
		if (!victim->isKindOf((KindOfType)0x36) &&
			!victim->isKindOf((KindOfType)0x9a) &&
			!victim->isKindOf((KindOfType)0x5d) &&
			victim->getControllingPlayer() == obj->getControllingPlayer())
		{
			ai->friend_setGoalObject(0);
			m_machine->setGoalObject(0);
			return STATE_FAILURE;
		}
	}

	if (victim)
	{
		BfmeCheckerNW *checker;
		checker = *(BfmeCheckerNW **)((char *)victim + 0x208);
		if (checker && checker->bfmeBusyNW())
		{
			m_machine->setGoalObject(0);
			return STATE_FAILURE;
		}

		if (!obj->isKindOf((KindOfType)0x6c))
		{
			if (victim && victim->isKindOf((KindOfType)0x6c))
			{
				m_machine->setGoalObject(0);
				return STATE_FAILURE;
			}
		}
	}

	Weapon *weapon = obj->getCurrentWeapon((WeaponSlotType *)0);
	if (!weapon)
		return STATE_FAILURE;

	if (!obj->isKindOf((KindOfType)2))
	{
		Gen_001e1790 *templateA = (Gen_001e1790 *)weapon->m_template;
		typedef Int8 (Gen_001e1790::*GenFn_m)();
		union { void (*fn)(); GenFn_m call; } gen_m_19349 = { j_00019349 };
		typedef unsigned char (Rva001E1770ByteField::*RvaFn_get)() const;
		union { void (*fn)(); RvaFn_get call; } rva_get_28f74 = { j_00028f74 };
		if (!(templateA->*gen_m_19349.call)() &&
			!(((Rva001E1770ByteField *)weapon->m_template)->*rva_get_28f74.call)() &&
			((BfmeHordeMember *)ai)->bfmeBlocksFormationRefresh())
			return STATE_FAILURE;
	}

	if (victim)
	{
		Team *team = obj->getTeam();
		TeamPrototype *prototype = team->getPrototype();
		typedef Object *(Team::*TeamFn_getTarget)();
		union { void (*fn)(); TeamFn_getTarget call; } team_get_296a9 = { j_000296a9 };
		typedef void (Team::*TeamFn_setTarget)(const Object *);
		union { void (*fn)(); TeamFn_setTarget call; } team_set_2a88d = { j_0002a88d };
		if (*(const unsigned char *)((const char *)prototype + 0x1c2) &&
			(team->*team_get_296a9.call)() == 0)
			(obj->getTeam()->*team_set_2a88d.call)(victim);
	}

	Bool inRange;
	if (victim)
	{
		typedef Bool (Weapon::*WeaponFn_rangeObj)(const Object *, const Object *, Int) const;
		union { void (*fn)(); WeaponFn_rangeObj call; } range_obj_2e85c = { j_0002e85c };
		inRange = (weapon->*range_obj_2e85c.call)(obj, victim, 0);
	}
	else
	{
		typedef Bool (Weapon::*WeaponFn_rangePos)(const Object *, const Coord3D *, Int) const;
		union { void (*fn)(); WeaponFn_rangePos call; } range_pos_2e951 = { j_0002e951 };
		inRange = (weapon->*range_pos_2e951.call)(obj, m_machine->getGoalPosition(), 0);
	}
	if (!inRange)
		return STATE_FAILURE;

	typedef Int8 (__cdecl *CheckFn)(BfmeThingEQT *, void *, BfmeHoldEQT *);
	if (!((CheckFn)(void *)j_0003dc6c)((BfmeThingEQT *)obj, (void *)victim,
		(BfmeHoldEQT *)weapon))
		return STATE_FAILURE;
	{
		typedef WeaponStatus (Weapon::*WeaponFn_getStatus)() const;
		union { void (*fn)(); WeaponFn_getStatus call; } status_0978c = { j_0000978c };
		if ((weapon->*status_0978c.call)() != WEAPON_STATUS_NONE)
			return STATE_SUCCESS;
	}

	{
		typedef Bool (Object::*ObjectFn_testStatus)(Int) const;
		union { void (*fn)(); ObjectFn_testStatus call; } test_status_016a4 = { j_000016a4 };
		if ((obj->*test_status_016a4.call)(0x25) &&
			(*(const unsigned char *)((const char *)TheGameLogic + 0x3c) & 1))
		{
			m_28 = true;
			return STATE_CONTINUE;
		}
	}

	{
		typedef void (Object::*ObjectFn_setStatusBit)(Int, Bool);
		union { void (*fn)(); ObjectFn_setStatusBit call; } set_status_32dee = { j_00032dee };
		typedef void (Object::*ObjectFn_preFire)(const Object *, const Coord3D *);
		union { void (*fn)(); ObjectFn_preFire call; } pre_fire_3960d = { j_0003960d };

		(obj->*set_status_32dee.call)(0xd, true);
		Object *currentVictim = m_machine->getGoalObject();
		(obj->*pre_fire_3960d.call)(currentVictim, m_machine->getGoalPosition());
		if (*(const unsigned char *)((const char *)weapon->m_template + 0x533) && victim)
			m_machine->setGoalPosition((const Coord3D *)((const char *)victim + 0x38));
	}

	return STATE_CONTINUE;
}
