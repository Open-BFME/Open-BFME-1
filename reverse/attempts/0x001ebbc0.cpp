// ?updateWeaponSet@WeaponSet@@QAEXPBVObject@@@Z
// partial score=0.78 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::updateWeaponSet, retail 0x001EBBC0 size 379.
// Focused TU: WeaponSet.cpp keeps ZH WEAPONSLOT_COUNT==3. BFME walks 4 slots,
// looks up the owner via TheGameLogic when dropping a lock, and stores the
// owner id at +0x34. Template slots sit at the same +8 as WeaponSet::m_weapons,
// so the rebuild walk is a pointer-difference induction.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Weapon;
class WeaponTemplate;
class WeaponTemplateSet;
class Object;
class GameLogic;

class WeaponSetFlags
{
};

class BfmeOverridable
{
public:
	const BfmeOverridable *getFinalOverride() const;
};

class Overridable
{
public:
	Overridable *m_nextOverride;
};

class BfmeThingTemplate
{
public:
	const WeaponTemplateSet *findWeaponTemplateSet(const WeaponSetFlags &flags) const;
};

class ThingTemplate
{
public:
	int m_vptr;
	Overridable *m_nextOverride;
};

template <size_t NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, Int idx1, Int idx2, Int idx3);

private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<304> ModelConditionFlags;

class Object
{
public:
	const WeaponSetFlags &getWeaponSetFlags() const;
	void clearModelConditionFlags(const ModelConditionFlags &clr);

	int m_vptr;
	ThingTemplate *m_template;
	unsigned char m_pad_08[0x74 - 8];
	Int m_objectId;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;

class WeaponTemplate
{
public:
	int m_vptr;
	char m_pad_04[0x0C - 4];
	NameKeyType m_nameKey;
	char m_pad_10[0x4C - 0x10];
	Int m_damageType;
	char m_pad_50[0x4D4 - 0x50];
	Int m_antiMask;
	char m_pad_4d8[0x4DC - 0x4D8];
	unsigned char m_isDamageWeapon;
};

class BfmeWeapon
{
public:
	void loadAmmoNow(const Object *obj);
};

class Weapon
{
public:
	virtual ~Weapon();

	WeaponTemplate *m_template;
	Int m_ownerId;
	char m_pad_0c[0x4C - 0x0C];
	unsigned char m_pitchLimited;
};

class BfmeWeaponStore
{
public:
	WeaponTemplate *findWeaponTemplatePrivate(NameKeyType key) const;
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
};

extern BfmeWeaponStore *TheWeaponStore;

class WeaponTemplateSet
{
public:
	char m_pad_00[8];
	const WeaponTemplate *m_template[4];
	char m_pad_18[0xE9 - 0x18];
	unsigned char m_isWeaponLockSharedAcrossSets;
};

class WeaponSet
{
public:
	void updateWeaponSet(const Object *obj);

private:
	int m_vptr;
	const WeaponTemplateSet *m_curWeaponTemplateSet;
	Weapon *m_weapons[4];
	Int m_curWeapon;
	Int m_curWeaponLockedStatus;
	UnsignedInt m_filledWeaponSlotMask;
	Int m_totalAntiMask;
	Int m_totalDamageTypeMask;
	unsigned char m_hasPitchLimit;
	unsigned char m_hasDamageWeapon;
	unsigned char m_pad_2e[0x34 - 0x2E];
	Int m_objectId;
};

// ?updateWeaponSet@WeaponSet@@QAEXPBVObject@@@Z
void WeaponSet::updateWeaponSet(const Object *obj)
{
	Int none = 0;
	const Object *o = obj;
	ThingTemplate *tmpl = o->m_template;
	const ThingTemplate *finalTmpl;
	if (tmpl == (ThingTemplate *)none)
		finalTmpl = 0;
	else
	{
		Overridable *next = tmpl->m_nextOverride;
		if (next != (Overridable *)none)
			tmpl = (ThingTemplate *)((BfmeOverridable *)next)->getFinalOverride();
		finalTmpl = tmpl;
	}

	const WeaponTemplateSet *set = ((const BfmeThingTemplate *)finalTmpl)->findWeaponTemplateSet(o->getWeaponSetFlags());
	if (set == (WeaponTemplateSet *)none)
		return;
	if (set == m_curWeaponTemplateSet)
		return;

	if (set->m_isWeaponLockSharedAcrossSets == (unsigned char)none)
	{
		Object *owner = TheGameLogic->findObjectByID(m_objectId);
		if (m_curWeaponLockedStatus != none)
		{
			m_curWeaponLockedStatus = none;
			if (owner != (Object *)none)
				owner->clearModelConditionFlags(ModelConditionFlags(ModelConditionFlags::kInit, 0x88, 0x89, 0x8A));
		}
		m_curWeapon = PRIMARY_WEAPON;
	}

	m_filledWeaponSlotMask = none;
	m_totalAntiMask = none;
	m_totalDamageTypeMask = none;
	m_hasPitchLimit = (unsigned char)none;
	m_hasDamageWeapon = (unsigned char)none;

	int rel = (int)((const char *)set - (const char *)this);
	Weapon **slot = &m_weapons[3];
	int i = 3;
	do
	{
		Weapon *weapon = *slot;
		if (weapon != (Weapon *)none)
		{
			delete weapon;
			*slot = (Weapon *)none;
		}

		const WeaponTemplate *wt = *(const WeaponTemplate **)((const char *)slot + rel);
		if (wt != (const WeaponTemplate *)none)
		{
			WeaponTemplate *found = TheWeaponStore->findWeaponTemplatePrivate(wt->m_nameKey);
			if (found != (WeaponTemplate *)none)
			{
				weapon = TheWeaponStore->allocateNewWeapon(found, (WeaponSlotType)i);
				*slot = weapon;
				weapon->m_ownerId = o->m_objectId;
				((BfmeWeapon *)weapon)->loadAmmoNow(o);

				m_filledWeaponSlotMask |= (1 << i);
				m_totalAntiMask |= weapon->m_template->m_antiMask;
				m_totalDamageTypeMask |= (1 << weapon->m_template->m_damageType);
				if (weapon->m_pitchLimited != (unsigned char)none)
					m_hasPitchLimit = 1;
				if (weapon->m_template->m_isDamageWeapon != (unsigned char)none)
					m_hasDamageWeapon = 1;
			}
		}
		--i;
		--slot;
	} while (i >= none);

	m_curWeaponTemplateSet = set;
	m_objectId = o->m_objectId;
}
