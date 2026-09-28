// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: WeaponSet::getAbleToUseWeaponAgainstTarget, retail 0x001EBEB0, 1065 bytes.
// Zero Hour twin: GeneralsMD WeaponSet.cpp getAbleToUseWeaponAgainstTarget.
// BFME drops the specificSlot argument (ret 0x14) and walks four slots.

#include <list>

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

#include "../command_source_type.h"

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0,
	ATTACK_TUNNEL_NETWORK_GUARD = 4
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

class Object;
typedef _STL::list<Object *> ContainedItemsList;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct KindOfMask
{
	int bits[6];

	bool any() const
	{
		for (unsigned int i = 0; i < 6; ++i)
			if (bits[i] != 0)
				return true;
		return false;
	}
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	char m_pad_08[0xC8 - 8];
	unsigned int m_kindOf[4];
};

enum KindOfType
{
	KINDOF_NONE = 0
};

class Thing
{
public:
	bool isKindOf(KindOfType t) const;
	bool isAnyKindOf(const KindOfMask &mask) const;

	int m_vptr;
	ThingTemplate *m_template;
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual bool isGarrisonable() const;
	virtual void slot03(); virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39();
	virtual bool isPassengerAllowedToFire() const;
	virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48();
	virtual void slot49();
	virtual bool slot50(const Object *source, Object **owner);
	virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58();
	virtual void slot59(); virtual void slot60(); virtual void slot61(); virtual void slot62();
	virtual void slot63(); virtual void slot64();
	virtual const ContainedItemsList *getContainedItemsList() const;
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual void slot70();
	virtual bool calcBestGarrisonPosition(Coord3D *goalPos, const Coord3D *targetPos);
};

class BfmeSub1CC_EC3
{
public:
	float queryDivMin40(void *source);
};

class AIUpdateInterface
{
public:
	char m_pad_00[0x1CC];
	BfmeSub1CC_EC3 *m_curLocomotor;
	BfmeSub1CC_EC3 *getCurLocomotor() const { return m_curLocomotor; }
};

class SpawnBehaviorInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual CanAttackResult getCanAnySlavesUseWeaponAgainstTarget(AbleToAttackType attackType,
		const Object *victim, const Coord3D *pos, CommandSourceType commandSource);
};

struct RvaC4390First;

class RvaC4390Second
{
public:
	RvaC4390First *resolve(int unused);
};

class Object : public Thing
{
public:
	bool isAbleToAttack() const;
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
	// Ledger name of the 35-byte wrapper at 0x001BE310; its third argument is the
	// target position and its fourth the command source (see the WeaponSet call).
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType,
		const Object *victim, CommandSourceType pos, WeaponSlotType commandSource) const;

	const Coord3D *getPosition() const { return &m_position; }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }
	const Object *getContainedBy() const { return m_containedBy; }

	char m_pad_08[0x38 - 8];
	Coord3D m_position;
	char m_pad_44[0x90 - 0x44];
	unsigned char m_flags90;
	char m_pad_91[0x94 - 0x91];
	unsigned char m_flags94;
	char m_pad_95[0x1FC - 0x95];
	ContainModuleInterface *m_contain;
	char m_pad_200[0x204 - 0x200];
	AIUpdateInterface *m_ai;
	char m_pad_208[0x214 - 0x208];
	Object *m_containedBy;
};

class Weapon
{
public:
	bool isSourceObjectWithGoalPositionWithinAttackRange(const Object *source,
		const Coord3D *goalPos, const Object *victim, const Coord3D *targetPos) const;
	bool isWithinAttackRange(const Object *source, const Object *target, int extra) const;
	bool isWithinAttackRange(const Object *source, const Coord3D *pos, int extra) const;
	bool bfmeCanAffect(const Object *source, const Object *victim) const;
};

class WeaponTemplateSet
{
public:
	char m_pad_00[0x88];
	KindOfMask m_kindOf88[4];
};

class WeaponSet
{
public:
	CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType attackType,
		const Object *source, const Object *victim, const Coord3D *pos,
		CommandSourceType commandSource) const;

private:
	bool isAnyWithinTargetPitch(const Object *source, const Object *victim) const;

	int m_vptr;
	WeaponTemplateSet *m_curWeaponTemplateSet;
	Weapon *m_weapons[4];
	WeaponSlotType m_curWeapon;
	int m_curWeaponLockedStatus;
	int m_filledWeaponSlotMask;
	int m_totalAntiMask;
};

static const ThingTemplate *effectiveTemplate(const Object *obj)
{
	ThingTemplate *tmpl = obj->m_template;
	if (tmpl != 0)
	{
		Overridable *next = tmpl->m_nextOverride;
		if (next != 0)
			tmpl = (ThingTemplate *)next->getFinalOverride();
	}
	return tmpl;
}

static int getVictimAntiMask(const Object *victim)
{
	const ThingTemplate *tmpl = effectiveTemplate(victim);
	if (tmpl->m_kindOf[1] & 0x400000)
		return 0x12;

	tmpl = effectiveTemplate(victim);
	if (tmpl->m_kindOf[1] & 0x80000)
		return 8;

	if (victim->isKindOf((KindOfType)0x4A))
		return 0x40;
	if (victim->isKindOf((KindOfType)0x19))
		return 4;

	if (victim->m_flags90 & 0x40)
	{
		if (victim->isKindOf((KindOfType)9))
			return 1;
		if (victim->isKindOf((KindOfType)8))
			return 0x20;
		if (victim->isKindOf((KindOfType)0xA))
			return 0x200;
		if (victim->isKindOf((KindOfType)0x4D))
			return 0x80;
		return 0;
	}

	return 2 + (victim->isKindOf((KindOfType)7) ? 0x100 : 0);
}

CanAttackResult WeaponSet::getAbleToUseWeaponAgainstTarget(AbleToAttackType attackType,
	const Object *source, const Object *victim, const Coord3D *pos,
	CommandSourceType commandSource) const
{
	int targetAntiMask;
	if (victim)
	{
		targetAntiMask = getVictimAntiMask(victim);
		pos = victim->getPosition();
	}
	else
	{
		targetAntiMask = 2;
	}

	const Object *containedBy = source->getContainedBy();
	ContainModuleInterface *contain = containedBy ? containedBy->getContain() : 0;

	if ((source->m_flags94 & 0x10) && !((int)attackType & 8))
	{
		if (!containedBy)
			return ATTACKRESULT_INVALID_SHOT;
		if (contain)
		{
			Object *owner = 0;
			if (contain->slot50(source, &owner))
			{
				if (!owner)
					return ATTACKRESULT_NOT_POSSIBLE;
				if (owner != victim
					&& ((RvaC4390Second *)owner)->resolve(0) != ((RvaC4390Second *)victim)->resolve(0))
					return ATTACKRESULT_NOT_POSSIBLE;
			}
		}
	}

	bool withinAttackRange = false;
	bool hasAWeaponInRange = false;
	bool hasAWeapon = false;
	for (int slot = 0; slot < 4; ++slot)
	{
		Weapon *weaponToTestForRange = m_weapons[slot];
		if (weaponToTestForRange)
		{
			hasAWeapon = true;
			if ((m_totalAntiMask & targetAntiMask) == 0)
				continue;

			if (source->m_flags94 & 0x10)
				withinAttackRange = true;
			else if (contain && contain->isGarrisonable())
			{
				Coord3D targetPos = *pos;
				Coord3D goalPos;
				if (contain->calcBestGarrisonPosition(&goalPos, &targetPos))
					withinAttackRange = weaponToTestForRange->isSourceObjectWithGoalPositionWithinAttackRange(
						source, &goalPos, victim, &targetPos);
				else if (victim)
					withinAttackRange = weaponToTestForRange->isWithinAttackRange(source, victim, 0);
			}
			else if (victim)
				withinAttackRange = weaponToTestForRange->isWithinAttackRange(source, victim, 0);
			else
				withinAttackRange = weaponToTestForRange->isWithinAttackRange(source, pos, 0);

			if (withinAttackRange)
			{
				hasAWeaponInRange = true;
				break;
			}
		}
	}

	if ((effectiveTemplate(source)->m_kindOf[0] & 4)
		|| (effectiveTemplate(source)->m_kindOf[2] & 0x80000)
		|| (containedBy && !(effectiveTemplate(containedBy)->m_kindOf[3] & 0x1000))
		|| (source->getAI() && source->getAI()->getCurLocomotor()
			&& source->getAI()->getCurLocomotor()->queryDivMin40((void *)source) <= 0.0f))
	{
		if (hasAWeapon && !hasAWeaponInRange && attackType != ATTACK_TUNNEL_NETWORK_GUARD)
			return ATTACKRESULT_INVALID_SHOT;
	}

	CanAttackResult okResult = withinAttackRange ? ATTACKRESULT_POSSIBLE : ATTACKRESULT_POSSIBLE_AFTER_MOVING;

	if ((m_totalAntiMask & targetAntiMask) == 0)
		return ATTACKRESULT_INVALID_SHOT;

	if (!victim)
		return okResult;

	if (!isAnyWithinTargetPitch(source, victim))
		return ATTACKRESULT_INVALID_SHOT;

	int first, last;
	if (m_curWeaponLockedStatus)
	{
		first = m_curWeapon;
		last = m_curWeapon;
	}
	else
	{
		first = 3;
		last = PRIMARY_WEAPON;
	}

	for (int i = first; i >= last; --i)
	{
		Weapon *weapon = m_weapons[i];
		if (weapon && weapon->bfmeCanAffect(source, victim))
		{
			const KindOfMask &mask = m_curWeaponTemplateSet->m_kindOf88[i];
			if (!mask.any() || victim->isAnyKindOf(mask))
				return okResult;
		}
	}

	ContainModuleInterface *passengerContain = source->getContain();
	if (passengerContain && passengerContain->isPassengerAllowedToFire())
	{
		const ContainedItemsList *items = passengerContain->getContainedItemsList();
		if (items)
		{
			for (ContainedItemsList::const_iterator it = items->begin(); it != items->end(); ++it)
			{
				Object *garrisonedMember = *it;
				if (garrisonedMember->isAbleToAttack())
				{
					CanAttackResult result = garrisonedMember->getAbleToAttackSpecificObject(
						attackType, victim, (CommandSourceType)(int)pos, (WeaponSlotType)commandSource);
					if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
						return result;
				}
			}
		}
	}

	SpawnBehaviorInterface *spawnInterface = source->getSpawnBehaviorInterface();
	if (spawnInterface
		&& spawnInterface->getCanAnySlavesUseWeaponAgainstTarget(attackType, victim, pos, commandSource) == ATTACKRESULT_POSSIBLE)
	{
		if ((effectiveTemplate(source)->m_kindOf[0] & 4)
			&& (effectiveTemplate(source)->m_kindOf[2] & 0x80000)
			&& okResult == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
			okResult = ATTACKRESULT_POSSIBLE;
		return okResult;
	}

	return ATTACKRESULT_INVALID_SHOT;
}
