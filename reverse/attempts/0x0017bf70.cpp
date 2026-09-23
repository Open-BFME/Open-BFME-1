// ?d_0017bf70@@YAXXZ
// partial score=0.47 date=2026-09-24
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport
// BFME AIAttackFireWeaponState::onEnter, retail RVA 0x0017BF70.

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

struct Coord3D
{
	float x;
	float y;
	float z;
};

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
	Coord3D m_goalPosition;

	const Coord3D *getGoalPosition() const
	{
		return &m_goalPosition;
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

#pragma comment(linker, "/alternatename:?testStatus@Object@@QBE_NH@Z=?j_000016a4@@YAXXZ")
#pragma comment(linker, "/alternatename:?setStatusBit@Object@@QAEXH_N@Z=?j_00032dee@@YAXXZ")
#pragma comment(linker, "/alternatename:?preFireCurrentWeapon@Object@@QAEXPBV1@PBUCoord3D@@@Z=?j_0003960d@@YAXXZ")
#pragma comment(linker, "/alternatename:?getTeamTargetObject@Team@@QAEPAVObject@@XZ=?j_000296a9@@YAXXZ")
#pragma comment(linker, "/alternatename:?setTeamTargetObject@Team@@QAEXPBVObject@@@Z=?j_0002a88d@@YAXXZ")
#pragma comment(linker, "/alternatename:?isWithinAttackRange@Weapon@@QBE_NPBVObject@@0H@Z=?j_0002e85c@@YAXXZ")
#pragma comment(linker, "/alternatename:?isWithinAttackRange@Weapon@@QBE_NPBVObject@@PBUCoord3D@@H@Z=?j_0002e951@@YAXXZ")
#pragma comment(linker, "/alternatename:?getStatus@Weapon@@QBE?AW4WeaponStatus@@XZ=?j_0000978c@@YAXXZ")
#pragma comment(linker, "/alternatename:?setGoalPosition@StateMachine@@QAEXPBUCoord3D@@@Z=?j_000314d@@YAXXZ")
#pragma comment(linker, "/alternatename:?m@Gen_001e1790@@QAEDXZ=?j_00019349@@YAXXZ")
#pragma comment(linker, "/alternatename:?get@Rva001E1770ByteField@@QBEEXZ=?j_00028f74@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeCheckEQT@@YADPAVBfmeThingEQT@@PAXPAVBfmeHoldEQT@@@Z=?j_0003dc6c@@YAXXZ")

StateReturnType AIAttackFireWeaponState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	ObjectStatusMaskType firing(ObjectStatusMaskType::kInit, 81);
	m_28 = false;
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
				ai->friend_setGoalObject(0);
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
		Rva001E1770ByteField *templateB = (Rva001E1770ByteField *)weapon->m_template;
		if (!templateA->m() && !templateB->get() &&
			((BfmeHordeMember *)ai)->bfmeBlocksFormationRefresh())
			return STATE_FAILURE;
	}

	if (victim)
	{
		Team *team = obj->getTeam();
		TeamPrototype *prototype = team->getPrototype();
		if (*(const unsigned char *)((const char *)prototype + 0x1c2) &&
			team->getTeamTargetObject() == 0)
			obj->getTeam()->setTeamTargetObject(victim);
	}

	Bool inRange;
	if (victim)
		inRange = weapon->isWithinAttackRange(obj, victim, 0);
	else
		inRange = weapon->isWithinAttackRange(obj, m_machine->getGoalPosition(), 0);
	if (!inRange)
		return STATE_FAILURE;

	if (!bfmeCheckEQT((BfmeThingEQT *)obj, (void *)victim,
		(BfmeHoldEQT *)weapon))
		return STATE_FAILURE;
	if (weapon->getStatus() != WEAPON_STATUS_NONE)
		return STATE_SUCCESS;

	if (obj->testStatus(0x25) && (*(const unsigned char *)((const char *)TheGameLogic + 0x3c) & 1))
	{
		m_28 = true;
		return STATE_CONTINUE;
	}

	obj->setStatusBit(0xd, true);
	Object *currentVictim = m_machine->getGoalObject();
	obj->preFireCurrentWeapon(currentVictim, m_machine->getGoalPosition());
	if (*(const unsigned char *)((const char *)weapon->m_template + 0x533) && victim)
		m_machine->setGoalPosition((const Coord3D *)((const char *)victim + 0x38));

	return STATE_CONTINUE;
}
