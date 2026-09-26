// ?update@AIAttackState@@UAE?AW4StateReturnType@@XZ
// partial score=0.22 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

enum KindOfType
{
	KINDOF_UNKNOWN = 0
};

enum Relationship
{
	RELATIONSHIP_ENEMIES = 0,
	RELATIONSHIP_NEUTRAL = 1
};

enum WeaponSlotType
{
	WEAPON_SLOT_TYPE_UNSPECIFIED = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

template <Int N>
class Rva0017CAE0VirtualSlots : public Rva0017CAE0VirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva0017CAE0VirtualSlots<0>
{
};

class Object;
class Team;
class AIUpdateInterface;
class AttackStateMachine;
class Weapon;

class StateMachine
{
public:
	virtual void slot00();
	unsigned char pad04[0x0C];
	Object *m_owner;
	Object *m_goalObject;
	UnsignedInt m_stateField18;
	Object *getGoalObject();
	UnsignedInt getCurrentStateID() const;
};

class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const = 0;
};

class Object
{
public:
	Bool isOutOfAmmo() const;
	WeaponSlotType getCurrentWeaponSlot() const;
	void notifyModelConditionChanged();
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Relationship getRelationship(const Object *other) const;
};

class BFMEActionObject
{
public:
	Bool testStatus(Int status) const;
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Team
{
public:
	Object *getTeamTargetObject();
	void setTeamTargetObject(const Object *target);
};

class AIUpdateInterface
{
public:
	void setCurrentVictim(const Object *victim);
	void friend_setGoalObject(Object *goal);
};

class Rva0017CAE0AIUpdateSlot128 : public Rva0017CAE0VirtualSlots<128>
{
public:
	virtual void invoke();
};

class Rva0017CAE0AIUpdateSlot129 : public Rva0017CAE0VirtualSlots<129>
{
public:
	virtual void notifyVictimIsDead();
};

class Rva0017CAE0AIUpdateSlot136 : public Rva0017CAE0VirtualSlots<136>
{
public:
	virtual Bool invoke();
};

class Rva0017CAE0ContainSlot2 : public Rva0017CAE0VirtualSlots<2>
{
public:
	virtual Bool isGarrisonable() const;
};

class Rva0017CAE0ContainSlot43 : public Rva0017CAE0VirtualSlots<43>
{
public:
	virtual Bool invoke(Object *source, Object *victim) const;
};

class Rva0017CAE0ContainSlot64 : public Rva0017CAE0VirtualSlots<64>
{
public:
	virtual UnsignedInt getContainCount() const;
};

class Rva0017CAE0AttackMachineSlot4 : public Rva0017CAE0VirtualSlots<4>
{
public:
	virtual Int invoke();
};

class Rva0017CAE0AttackMachineSlot8 : public Rva0017CAE0VirtualSlots<8>
{
public:
	virtual StateReturnType invoke(UnsignedInt state);
};

class Rva0017CAE0AttackMachineSlot14 : public Rva0017CAE0VirtualSlots<14>
{
public:
	virtual void setGoalObject(Object *goal);
};

class Rva0016F740StringAccessor
{
public:
	AsciiString getName() const;
};

class Rva001E1770ByteField
{
public:
	UnsignedByte get() const;
};

class Gen_0016A1B0
{
public:
	Bool bfmeQuery() const;
};

class Weapon
{
};

class AIAttackState : public Rva0017CAE0VirtualSlots<5>
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	Bool chooseWeapon();

	unsigned char pad04[0x18];
	StateMachine *m_machine;
	unsigned char pad20[8];
	AttackStateMachine *m_attackMachine;
	AttackExitConditionsInterface *m_attackParameters;
	Team *m_victimTeam;
	Coord3D m_originalVictimPos;
	AsciiString m_lockedWeaponOnEnter;
	Bool m_follow;
	Bool m_isAttackingObject;
	Bool m_isForceAttacking;
	UnsignedByte pad47;
	UnsignedInt m_bfmeAttackState48;
	Bool m_bfmeAttackState4C;
	Bool m_bfmeAttackState4D;
	UnsignedByte pad4E[2];
	UnsignedInt m_bfmeAttackState50;
};

static AIUpdateInterface *getAI(Object *object)
{
	return *(AIUpdateInterface **)((char *)object + 0x204);
}

static Team *getTeam(Object *object)
{
	return *(Team **)((char *)object + 0x23C);
}

static void *getContain(Object *object)
{
	return *(void **)((char *)object + 0x1FC);
}

static UnsignedInt &getConditionBits(Object *object)
{
	return *(UnsignedInt *)((char *)object + 0x114);
}

static Bool stringHasText(const AsciiString *string)
{
	const void *data = *(void * const *)string;
	return data != 0 && *(const unsigned short *)((const char *)data + 4) != 0;
}

StateReturnType AIAttackState::update()
{
	StateMachine *machine = m_machine;
	Object *source = machine->m_owner;
	Object *victim = machine->getGoalObject();

	if (m_attackParameters && m_attackParameters->shouldExit(machine))
		return STATE_SUCCESS;

	AIUpdateInterface *ai = getAI(source);
	if (ai && ((Rva0017CAE0AIUpdateSlot136 *)ai)->invoke())
		return STATE_CONTINUE;

	if (source->isOutOfAmmo() && !((Thing *)source)->isKindOf((KindOfType)0x19))
		return STATE_FAILURE;

	if (m_isAttackingObject)
	{
		if (!victim || (*(UnsignedInt *)((char *)victim + 0x344) & 1) ||
			((BFMEActionObject *)victim)->testStatus(0x31))
		{
			if (ai)
				((Rva0017CAE0AIUpdateSlot129 *)ai)->notifyVictimIsDead();
			if (((Thing *)source)->isKindOf((KindOfType)0x96))
				return STATE_SUCCESS;
			Int state = ((Rva0017CAE0AttackMachineSlot4 *)m_attackMachine)->invoke();
			return state > 0 ? (StateReturnType)state : STATE_CONTINUE;
		}

		if (ai)
			((Rva0017CAE0AIUpdateSlot128 *)ai)->invoke();

		Bool sourceFlag = ((BFMEActionObject *)source)->testStatus(0x1C);
		Relationship relationship = source->getRelationship(victim);
		if (m_bfmeAttackState4D && sourceFlag && relationship == RELATIONSHIP_ENEMIES &&
			!((Thing *)victim)->isKindOf((KindOfType)0x5D))
		{
			relationship = RELATIONSHIP_NEUTRAL;
		}
		if (ai)
			ai->setCurrentVictim(victim);

		if (getTeam(victim) != m_victimTeam)
		{
			void *contain = getContain(victim);
			if (ai && !((BFMEActionObject *)victim)->testStatus(1) && contain &&
				((Rva0017CAE0ContainSlot2 *)contain)->isGarrisonable() &&
				((Rva0017CAE0ContainSlot64 *)contain)->getContainCount() == 0 &&
				source->getRelationship(victim) == RELATIONSHIP_NEUTRAL)
			{
				ai->friend_setGoalObject(0);
				Team *team = getTeam(source);
				if (victim == team->getTeamTargetObject())
					team->setTeamTargetObject(0);
				((Rva0017CAE0AIUpdateSlot129 *)ai)->notifyVictimIsDead();
				return STATE_FAILURE;
			}

			if (relationship != RELATIONSHIP_ENEMIES)
			{
				ai->friend_setGoalObject(0);
				Team *team = getTeam(source);
				if (victim == team->getTeamTargetObject())
					team->setTeamTargetObject(0);
				((Rva0017CAE0AIUpdateSlot129 *)ai)->notifyVictimIsDead();
				return STATE_FAILURE;
			}
		}

		StateMachine *attackMachine = (StateMachine *)m_attackMachine;
		if (victim != attackMachine->getGoalObject())
			((Rva0017CAE0AttackMachineSlot14 *)m_attackMachine)->setGoalObject(victim);

		Object *related = *(Object **)((char *)source + 0x214);
		if (related && getContain(related) &&
			((Rva0017CAE0ContainSlot43 *)getContain(related))->invoke(source, victim))
			return STATE_FAILURE;
	}

	if (!chooseWeapon())
		return STATE_FAILURE;

	Weapon *weapon = source->getCurrentWeapon(0);
	if (stringHasText(&m_lockedWeaponOnEnter) && weapon)
	{
		AsciiString weaponName = ((Rva0016F740StringAccessor *)weapon)->getName();
		if (((const StringBase<char> *)&m_lockedWeaponOnEnter)->compare(weaponName.str()) != 0)
			return STATE_FAILURE;
	}

	if (!weapon || *(Int *)((char *)weapon + 0x34) <= 0)
		return STATE_FAILURE;

	UnsignedByte *weaponType = *(UnsignedByte **)((char *)weapon + 4);
	if (((Rva001E1770ByteField *)weaponType)->get() != m_bfmeAttackState4C)
	{
		onExit(STATE_EXIT_NORMAL);
		ai = getAI(source);
		if (ai)
		{
			ai->setCurrentVictim(victim);
			ai->friend_setGoalObject(victim);
		}
		Int state = ((Rva0017CAE0AttackMachineSlot4 *)m_attackMachine)->invoke();
		return state > 0 ? (StateReturnType)state : STATE_CONTINUE;
	}

	Int currentState = ((StateMachine *)m_attackMachine)->getCurrentStateID();
	UnsignedInt &condition = getConditionBits(source);
	if (currentState == 0xE4)
	{
		if (condition & 0x20)
		{
			condition &= ~0x20u;
			source->notifyModelConditionChanged();
		}
		if (condition & 0x40)
			condition &= ~0x40u;
	}
	else
	{
		if (!(condition & 0x20))
		{
			condition |= 0x20;
			source->notifyModelConditionChanged();
		}
		if (victim && ((Thing *)victim)->isKindOf((KindOfType)7) && !(condition & 0x40))
		{
			condition |= 0x40;
			source->notifyModelConditionChanged();
		}
	}

	if (((Gen_0016A1B0 *)m_attackMachine)->bfmeQuery())
	{
		UnsignedInt state = *(UnsignedInt *)((char *)m_attackMachine + 0x18);
		if (((Rva0017CAE0AttackMachineSlot8 *)m_attackMachine)->invoke(state) == STATE_FAILURE)
			return STATE_FAILURE;
	}

	Int state = ((Rva0017CAE0AttackMachineSlot4 *)m_attackMachine)->invoke();
	return state > 0 ? (StateReturnType)state : STATE_CONTINUE;
}
