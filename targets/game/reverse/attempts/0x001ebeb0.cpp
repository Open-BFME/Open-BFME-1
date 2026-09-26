// ?getAbleToAttackSpecificObject@WeaponSet@@QBE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@1W4CommandSourceType@@W4WeaponSlotType@@@Z
// partial score=0.48 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::getAbleToAttackSpecificObject, retail 0x001EBEB0 size 1065.
// Focused TU: same-TU esi-convention getVictimAntiMask (sibling of chooseBest).
// Body is the BFME 4-slot UseWeaponAgainstTarget merge: anti-mask, garrison
// range, kind abort, pitch, canAffect + KindOf-88, passenger and spawn.

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

enum KindOfType
{
	KINDOF_NONE = 0
};

class Object;
class WeaponSet;

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct KindOfMask
{
	int bits[6];
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
	unsigned int m_kindOf[5];
};

class Thing
{
public:
	bool isKindOf(KindOfType t) const;
	bool isAnyKindOf(const KindOfMask &mask) const;

	int m_vptr;
	ThingTemplate *m_template;
};

class BfmeContainInterface
{
public:
	virtual void slot00();
	virtual bool isGarrisonable() const;
	virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual bool isPassengerAllowedToFire() const;
	virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49();
	virtual bool bfmeQueryOwner(const Object *source, Object **out);
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62(); virtual void slot63(); virtual void slot64();
	virtual void *getContainedItemsList();
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual bool calcBestGarrisonPosition(Coord3D *goalPos, const Coord3D *targetPos) const;
};

class BfmeAIRoot
{
public:
	char m_pad[0x1CC];
	class BfmeAIRange *m_range;
};

class BfmeAIRange
{
public:
	float bfmeRangeAgainst(const Object *source);
};

class SpawnBehaviorInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual CanAttackResult getCanAnySlavesUseWeaponAgainstTarget(
		AbleToAttackType attackType, const Object *victim, const Coord3D *pos,
		WeaponSlotType specificSlot);
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

class Object : public Thing
{
public:
	bool isAbleToAttack() const;
	void *bfmeResolve(int unused) const;
	SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType,
		const Object *target, const Coord3D *pos, WeaponSlotType specificSlot) const;

	char m_pad_08[0x38 - 8];
	Coord3D m_position;
	char m_pad_44[0x90 - 0x44];
	unsigned char m_flags90;
	char m_pad_91[0x94 - 0x91];
	unsigned char m_flags94;
	char m_pad_95[0x1FC - 0x95];
	BfmeContainInterface *m_contain;
	char m_pad_200[0x204 - 0x200];
	BfmeAIRoot *m_ai;
	char m_pad_208[0x214 - 0x208];
	Object *m_containedBy;
};

class WeaponSet
{
public:
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType,
		const Object *source, const Object *victim, CommandSourceType commandSource,
		WeaponSlotType specificSlot) const;

private:
	bool isAnyWithinTargetPitch(const Object *source, const Object *victim) const;

	int m_vptr;
	WeaponTemplateSet *m_curWeaponTemplateSet;
	Weapon *m_weapons[4];
	WeaponSlotType m_curWeapon;
	int m_curWeaponLockedStatus;
	char m_pad_20[0x24 - 0x20];
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

// ?getAbleToAttackSpecificObject@WeaponSet@@QBE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@1W4CommandSourceType@@W4WeaponSlotType@@@Z present-unmatched
CanAttackResult WeaponSet::getAbleToAttackSpecificObject(AbleToAttackType attackType,
	const Object *source, const Object *victim, CommandSourceType commandSource,
	WeaponSlotType specificSlot) const
{
	const Object *v = victim;
	const WeaponSet *self = this;
	int targetAntiMask;
	const Coord3D *pos;
	if (v != 0)
	{
		targetAntiMask = getVictimAntiMask(v);
		pos = &v->m_position;
	}
	else
	{
		targetAntiMask = 2;
		pos = (const Coord3D *)commandSource;
	}

	Object *containedBy = source->m_containedBy;
	BfmeContainInterface *contain;
	if (containedBy != 0)
		contain = containedBy->m_contain;
	else
		contain = 0;

	if ((source->m_flags94 & 0x10) != 0 && ((int)attackType & 8) == 0)
	{
		if (containedBy == 0)
			return ATTACKRESULT_INVALID_SHOT;
		if (contain != 0)
		{
			Object *out = 0;
			if (contain->bfmeQueryOwner(source, &out))
			{
				if (out == 0 || (out != v && out->bfmeResolve(0) != v->bfmeResolve(0)))
					return ATTACKRESULT_NOT_POSSIBLE;
			}
		}
	}

	unsigned char withinAttackRange = 0;
	unsigned char hasAWeaponInRange = 0;
	unsigned char hasAWeapon = 0;
	Weapon **slot = (Weapon **)self->m_weapons;
	for (int i = 0; i < 4; ++i, ++slot)
	{
		Weapon *weapon = *slot;
		if (weapon == 0)
			continue;
		hasAWeapon = 1;
		if ((self->m_totalAntiMask & targetAntiMask) == 0)
			continue;
		if ((source->m_flags94 & 0x10) != 0)
		{
			withinAttackRange = 1;
			hasAWeaponInRange = 1;
			break;
		}
		if (contain != 0 && contain->isGarrisonable())
		{
			Coord3D targetPos;
			targetPos.x = pos->x;
			targetPos.y = pos->y;
			targetPos.z = pos->z;
			Coord3D goalPos;
			if (contain->calcBestGarrisonPosition(&goalPos, &targetPos))
				withinAttackRange = (unsigned char)weapon->isSourceObjectWithGoalPositionWithinAttackRange(
					source, &goalPos, v, &targetPos);
		}
		else if (v != 0)
			withinAttackRange = (unsigned char)weapon->isWithinAttackRange(source, v, 0);
		else
			withinAttackRange = (unsigned char)weapon->isWithinAttackRange(source, pos, 0);
		if (withinAttackRange)
		{
			hasAWeaponInRange = 1;
			break;
		}
	}

	const ThingTemplate *srcTmpl = effectiveTemplate(source);
	if ((srcTmpl->m_kindOf[0] & 4) == 0)
	{
		srcTmpl = effectiveTemplate(source);
		if ((srcTmpl->m_kindOf[2] & 0x80000) == 0)
		{
			int allowAbort = 1;
			if (containedBy != 0)
			{
				const ThingTemplate *ct = effectiveTemplate(containedBy);
				if ((ct->m_kindOf[3] & 0x1000) == 0)
					allowAbort = 0;
			}
			if (allowAbort)
			{
				if (source->m_ai == 0 || source->m_ai->m_range == 0
					|| !(source->m_ai->m_range->bfmeRangeAgainst(source) > 0.0f))
				{
					if (hasAWeapon && !hasAWeaponInRange && attackType != (AbleToAttackType)4)
						return ATTACKRESULT_INVALID_SHOT;
				}
			}
		}
		else if (hasAWeapon && !hasAWeaponInRange && attackType != (AbleToAttackType)4)
			return ATTACKRESULT_INVALID_SHOT;
	}
	else if (hasAWeapon && !hasAWeaponInRange && attackType != (AbleToAttackType)4)
		return ATTACKRESULT_INVALID_SHOT;

	CanAttackResult okResult = (CanAttackResult)(2 + (withinAttackRange ? 1 : 0));
	if ((self->m_totalAntiMask & targetAntiMask) == 0)
		return ATTACKRESULT_INVALID_SHOT;
	if (v == 0)
		return okResult;
	if (!self->isAnyWithinTargetPitch(source, v))
		return ATTACKRESULT_INVALID_SHOT;

	int first;
	int last;
	if (self->m_curWeaponLockedStatus != 0)
	{
		first = (int)self->m_curWeapon;
		last = (int)self->m_curWeapon;
	}
	else
	{
		first = 3;
		last = 0;
	}

	for (int i = first; i >= last; --i)
	{
		Weapon *weapon = self->m_weapons[i];
		if (weapon == 0)
			continue;
		if (!weapon->bfmeCanAffect(source, v))
			continue;
		int kindOff = (i + i * 2) << 3;
		KindOfMask *mask = (KindOfMask *)((char *)self->m_curWeaponTemplateSet + 0x88 + kindOff);
		int b = 0;
		for (; b < 6; ++b)
		{
			if (mask->bits[b] != 0)
				break;
		}
		if (b == 6 || v->isAnyKindOf(*mask))
			return okResult;
	}

	contain = source->m_contain;
	if (contain != 0 && contain->isPassengerAllowedToFire())
	{
		void *list = contain->getContainedItemsList();
		if (list != 0)
		{
			void **sentinel = (void **)list;
			for (void **node = (void **)*sentinel; node != sentinel; node = (void **)*node)
			{
				Object *member = (Object *)node[2];
				if (member->isAbleToAttack())
				{
					CanAttackResult result = member->getAbleToAttackSpecificObject(
						attackType, v, pos, specificSlot);
					if (result == ATTACKRESULT_POSSIBLE || result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
						return result;
				}
			}
		}
	}

	SpawnBehaviorInterface *spawn = source->getSpawnBehaviorInterface();
	if (spawn != 0)
	{
		CanAttackResult result = spawn->getCanAnySlavesUseWeaponAgainstTarget(
			attackType, v, pos, specificSlot);
		if (result == ATTACKRESULT_POSSIBLE)
		{
			srcTmpl = effectiveTemplate(source);
			if ((srcTmpl->m_kindOf[0] & 4) != 0)
			{
				srcTmpl = effectiveTemplate(source);
				if ((srcTmpl->m_kindOf[2] & 0x80000) != 0)
				{
					if (okResult == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
						return ATTACKRESULT_POSSIBLE;
					return okResult;
				}
			}
			return okResult;
		}
	}

	return ATTACKRESULT_INVALID_SHOT;
}
