// ?chooseBestWeaponForTarget@WeaponSet@@QAE_NPBVObject@@0W4WeaponChoiceCriteria@@W4CommandSourceType@@@Z
// partial score=0.58 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::chooseBestWeaponForTarget, retail 0x001EC3F0.
//
// Object.cpp calls this through m_weaponSet at +0x264 (already matched).
// Retail is a thiscall that returns via `ret 0x10` (obj, victim, criteria,
// cmdSource). BFME walks four weapon slots; the ZH body only had three, and
// the null-victim path here scans for a usable weapon instead of forcing
// PRIMARY. Kept as a focused TU so WEAPONSLOT_COUNT stays 3 in WeaponSet.cpp.
//
// Identity: pin + ret 0x10 + 4-slot walk + lock at +0x1c. Ghidra size 1002
// cuts mid `mov [this+0x18],0`; true ret-boundary is 1011 (0x1EC3F0..0x1EC7E3).
//
// Walls on the 1036B /O2 body (probe vs 1011): frame 0x48 vs 0x40; victim in
// ebp (push ebp before the null compare) vs ebx; KindOf stride becomes a
// standing 0x24 induction instead of `mov ebp,3` + `lea esi,[ebp+ebp*2];shl 3`;
// getVictimAntiMask is thiscall (ecx) vs same-TU `mov esi,ebx; call 0x001EBDA0`.
// Next lever: keep ebx=victim so ebp can be the 3..0 slot (retail pushes ebp
// only at the has-victim join) and drop 8 bytes of frame.

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

class Thing
{
public:
	bool isAnyKindOf(const KindOfMask &mask) const;

	int m_vptr;
};

class Object : public Thing
{
public:
	int getVictimAntiMask() const;

	char m_pad_04[0x34];
	float x;
	float y;
	float z;
	char m_pad_44[0x204 - 0x44];
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
	char m_pad_6c[0x4d4 - 0x6c];
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
	KindOfMask m_kindOf28[4];
	KindOfMask m_kindOf88[4];
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

		if ((weapon->m_template->m_antiMask & victim->getVictimAntiMask()) == 0)
			continue;

		if (!weapon->isWithinTargetPitch(obj, victim))
			continue;

		if (!weapon->bfmeCanAffect(obj, victim) && weapon->m_template->m_damageType != 8)
			continue;

		Coord3D delta;
		delta.x = obj->x - victim->x;
		delta.y = obj->y - victim->y;
		delta.z = obj->z - victim->z;
		float distance = delta.length();

		bool canAffect = weapon->bfmeCanAffect(obj, victim);
		float damage = 1.0f;
		if (!canAffect)
			damage = 0.0f;

		float attackRange = weapon->bfmeEstimate(obj, victim);
		float minRange = weapon->bfmeClampedRange();

		bool weaponIsReady = (status == READY_TO_FIRE || status == (WeaponStatus)4);
		if (obj->m_ai && obj->m_ai->isWeaponSlotOnTurretAndAimingAtTarget((WeaponSlotType)i, victim))
			weaponIsReady = false;
		else if (distance < minRange)
			weaponIsReady = false;

		if (bfmeAnySix(m_curWeaponTemplateSet->m_kindOf88[i].bits))
		{
			if (victim->isAnyKindOf(m_curWeaponTemplateSet->m_kindOf88[i]))
			{
				damage = 100000.0f;
				attackRange = 100000.0f;
				if (weapon->getStatus() == OUT_OF_AMMO)
					weaponIsReady = false;
				else if (distance < minRange)
					weaponIsReady = false;
				else
					weaponIsReady = true;
			}
			else
			{
				damage = -1.0f;
				attackRange = -1.0f;
				weaponIsReady = false;
			}
		}

		if (bfmeAnySix(m_curWeaponTemplateSet->m_kindOf28[i].bits) &&
			victim->isAnyKindOf(m_curWeaponTemplateSet->m_kindOf28[i]))
		{
			damage = 1.0e10f;
			attackRange = 1.0e10f;
			if (weapon->getStatus() == OUT_OF_AMMO)
				weaponIsReady = false;
			else if (distance < minRange)
				weaponIsReady = false;
			else
				weaponIsReady = true;
		}

		if (criteria == PREFER_SPECIAL)
		{
			if (weapon->bfmeSpecialOk(obj, victim))
			{
				currentDecision = i;
				bestDamage = damage;
				found = true;
				break;
			}
		}

		if (criteria == PREFER_LONGEST_RANGE)
		{
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
		}
		else
		{
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
