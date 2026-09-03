// ?chooseBestWeaponForTarget@WeaponSet@@QAE_NPBVObject@@0W4WeaponChoiceCriteria@@W4CommandSourceType@@@Z
// partial score=0.96 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::chooseBestWeaponForTarget, retail 0x001EC3F0 size 1011.
// Probe 980B / 41 diffs / score 0.96. Exact through +0x211 (lock, ret 0x10,
// frame 0x40, ebx=victim, push ebp only at has-victim, mov ebp,3,
// [ecx+ebp*4+8], slotAlways +0x2e, mov esi,ebx; call getVictimAntiMask,
// Coord3D copy-then-subtract, damage 1.0/0.0 after second canAffect,
// KindOf lea esi,[ebp+ebp*2]; shl 3, switch sub/dec/dec, or ebp,-1).
//
// Walls: two SIB bytes ([esi+ecx+disp] vs retail [ecx+esi+disp] at +0x88/+0x28)
// and a 31B-shorter epilogue -- found stays in al so the stores use ecx/edx
// and skip `mov al,[esp+6]`; backup does not stack-store found=1; none uses
// xor al instead of reloading the found byte. KindOf arrays recreate a 0x24
// induction and grow the frame to 0x44. Same-TU static helper is required
// for the esi private convention (pair with getAbleToAttack 0x001EBEB0).

enum WeaponStatus
{
	READY_TO_FIRE = 0,
	OUT_OF_AMMO = 1
};

enum WeaponChoiceCriteria
{
	PREFER_MOST_DAMAGE = 0,
	PREFER_LONGEST_RANGE = 1,
	PREFER_SPECIAL = 2
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum KindOfType
{
	KINDOF_NONE = 0
};

class Object;
class WeaponTemplate;
class AIUpdateInterface;
class WeaponSet;

struct Coord3D
{
	float x;
	float y;
	float z;
	float length() const;
};

struct KindOfMask
{
	int bits[6];
};

unsigned char __cdecl bfmeAnySix(int *slots);

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
	char m_pad_08[0xCC - 8];
	unsigned int m_kindBits;
};

class Thing
{
public:
	bool isKindOf(KindOfType t) const;
	bool isAnyKindOf(const KindOfMask &mask) const;

	int m_vptr;
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	char m_pad_08[0x38 - 8];
	float x;
	float y;
	float z;
	char m_pad_44[0x90 - 0x44];
	unsigned char m_flags90;
	char m_pad_91[0x204 - 0x91];
	AIUpdateInterface *m_ai;
};

class AIUpdateInterface
{
public:
	bool isWeaponSlotOnTurretAndAimingAtTarget(WeaponSlotType wslot, const Object *victim) const;
};

class WeaponTemplate
{
public:
	int m_pad_00[0x13];
	int m_damageType;
	char m_pad_50[0x68 - 0x50];
	int m_clipOrLimit;
	char m_pad_4d4_from_6c[0x4d4 - 0x6c];
	int m_antiMask;
	char m_pad_4d8[0x4f0 - 0x4d8];
	int m_autoReload;
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	bool isWithinTargetPitch(const Object *source, const Object *victim) const;
	bool bfmeCanAffect(const Object *source, const Object *victim) const;
	float bfmeEstimate(const Object *source, const Object *victim) const;
	float bfmeClampedRange() const;
	bool bfmeSpecialOk(const Object *source, const Object *victim) const;

	int m_vptr;
	WeaponTemplate *m_template;
};

class WeaponTemplateSet
{
public:
	char m_pad_00[0x18];
	unsigned int m_autoChooseMask[4];

	KindOfMask *nth88(int i)
	{
		return (KindOfMask *)((char *)this + 0x88 + ((i + i * 2) << 3));
	}

	KindOfMask *nth28(int i)
	{
		return (KindOfMask *)((char *)this + 0x28 + ((i + i * 2) << 3));
	}
};

class WeaponSet
{
public:
	bool chooseBestWeaponForTarget(const Object *obj, const Object *victim,
		WeaponChoiceCriteria criteria, CommandSourceType cmdSource);

private:
	int m_vptr;
	WeaponTemplateSet *m_curWeaponTemplateSet;
	Weapon *m_weapons[4];
	WeaponSlotType m_curWeapon;
	int m_curWeaponLockedStatus;
	char m_pad_20[0x2e - 0x20];
	unsigned char m_slotAlways[4];
};

static const ThingTemplate *effectiveTemplate(const Object *victim)
{
	ThingTemplate *tmpl = victim->m_template;
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
	if (tmpl->m_kindBits & 0x400000)
		return 0x12;

	tmpl = effectiveTemplate(victim);
	if (tmpl->m_kindBits & 0x80000)
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

	int ground = 2;
	if (victim->isKindOf((KindOfType)7))
		ground += 0x100;
	return ground;
}

// ?chooseBestWeaponForTarget@WeaponSet@@QAE_NPBVObject@@0W4WeaponChoiceCriteria@@W4CommandSourceType@@@Z
bool WeaponSet::chooseBestWeaponForTarget(const Object *obj, const Object *victim,
	WeaponChoiceCriteria criteria, CommandSourceType cmdSource)
{
	if (m_curWeaponLockedStatus != 0)
		return true;

	if (victim == 0)
	{
		Weapon **slot = m_weapons;
		for (int i = 0; i < 4; ++i, ++slot)
		{
			Weapon *weapon = *slot;
			if (weapon == 0)
				continue;
			if (weapon->getStatus() != OUT_OF_AMMO || weapon->m_template->m_autoReload == 0)
			{
				m_curWeapon = (WeaponSlotType)i;
				return true;
			}
		}
		m_curWeapon = PRIMARY_WEAPON;
		return false;
	}

	bool found = false;
	bool foundBackup = false;
	float longestRange = 0.0f;
	float bestDamage = 0.0f;
	float longestRangeBackup = 0.0f;
	float bestDamageBackup = 0.0f;
	int currentDecision = 0;
	int currentDecisionBackup = 0;

	for (int i = 3; i >= 0; --i)
	{
		Weapon *weapon = m_weapons[i];
		if (weapon == 0)
			continue;

		if (m_slotAlways[i] == 0)
		{
			if ((m_curWeaponTemplateSet->m_autoChooseMask[i] & (1u << (int)cmdSource)) == 0)
				continue;
		}

		WeaponStatus status = weapon->getStatus();
		if (status == OUT_OF_AMMO)
		{
			if (weapon->m_template->m_autoReload != 0)
				continue;
			if (weapon->m_template->m_clipOrLimit >= 0)
				continue;
		}

		if ((weapon->m_template->m_antiMask & getVictimAntiMask(victim)) == 0)
			continue;

		if (!weapon->isWithinTargetPitch(obj, victim))
			continue;

		if (!weapon->bfmeCanAffect(obj, victim) && weapon->m_template->m_damageType != 8)
			continue;

		Coord3D delta;
		delta.x = obj->x;
		delta.y = obj->y;
		delta.z = obj->z;
		delta.x -= victim->x;
		delta.y -= victim->y;
		delta.z -= victim->z;
		float distance = delta.length();

		float damage;
		if (weapon->bfmeCanAffect(obj, victim))
			damage = 1.0f;
		else
			damage = 0.0f;

		float attackRange = weapon->bfmeEstimate(obj, victim);
		float minRange = weapon->bfmeClampedRange();

		bool weaponIsReady = (status == READY_TO_FIRE || status == (WeaponStatus)4);
		if (obj->m_ai && obj->m_ai->isWeaponSlotOnTurretAndAimingAtTarget((WeaponSlotType)i, victim))
			weaponIsReady = false;
		else if (distance < minRange)
			weaponIsReady = false;

		KindOfMask *mask88 = m_curWeaponTemplateSet->nth88(i);
		if (bfmeAnySix(mask88->bits))
		{
			if (victim->isAnyKindOf(*mask88))
			{
				damage = 100000.0f;
				attackRange = 100000.0f;
				weaponIsReady = (weapon->getStatus() != OUT_OF_AMMO && distance >= minRange);
			}
			else
			{
				damage = -1.0f;
				attackRange = -1.0f;
				weaponIsReady = false;
			}
		}

		KindOfMask *mask28 = m_curWeaponTemplateSet->nth28(i);
		if (bfmeAnySix(mask28->bits) && victim->isAnyKindOf(*mask28))
		{
			damage = 1.0e10f;
			attackRange = 1.0e10f;
			weaponIsReady = (weapon->getStatus() != OUT_OF_AMMO && distance >= minRange);
		}

		switch (criteria)
		{
		case PREFER_SPECIAL:
			if (weapon->bfmeSpecialOk(obj, victim))
			{
				currentDecision = i;
				bestDamage = damage;
				found = true;
				i = -1;
				break;
			}
		case PREFER_MOST_DAMAGE:
			if (!weaponIsReady)
			{
				if (damage >= bestDamageBackup)
				{
					bestDamageBackup = damage;
					currentDecisionBackup = i;
					foundBackup = true;
				}
			}
			else if (damage >= bestDamage)
			{
				bestDamage = damage;
				currentDecision = i;
				found = true;
			}
			break;
		case PREFER_LONGEST_RANGE:
			if (!weaponIsReady)
			{
				if (attackRange > longestRangeBackup)
				{
					longestRangeBackup = attackRange;
					currentDecisionBackup = i;
					foundBackup = true;
				}
			}
			else if (attackRange > longestRange)
			{
				longestRange = attackRange;
				currentDecision = i;
				found = true;
			}
			break;
		}
	}

	if (found)
	{
		m_curWeapon = (WeaponSlotType)currentDecision;
		return found;
	}
	if (foundBackup)
	{
		m_curWeapon = (WeaponSlotType)currentDecisionBackup;
		found = true;
		return found;
	}
	m_curWeapon = PRIMARY_WEAPON;
	return found;
}
