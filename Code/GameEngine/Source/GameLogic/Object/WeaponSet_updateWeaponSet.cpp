// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::updateWeaponSet, retail 0x001EBBC0 size 379; BFME walks 4 slots,
// re-looks each template up by name key, drops locks via TheGameLogic and stores the owner id at +0x34.

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
	virtual ~ThingTemplate();

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
	Int m_id;
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
	NameKeyType getNameKey() const { return m_nameKey; }
	NameKeyType m_nameKey;
	char m_pad_10[0x4C - 0x10];
	Int m_damageType;
	char m_pad_50[0x4D4 - 0x50];
	Int m_antiMask;
	char m_pad_4d8[0x4DC - 0x4D8];
	Bool m_isDamageWeapon;
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
	Bool m_pitchLimited;
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
	Bool m_isWeaponLockSharedAcrossSets;
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
	Bool m_hasPitchLimit;
	Bool m_hasDamageWeapon;
	unsigned char m_pad_2e[0x34 - 0x2E];
	Int m_objectId;
};

// ?updateWeaponSet@WeaponSet@@QAEXPBVObject@@@Z
void WeaponSet::updateWeaponSet(const Object *obj)
{
	ThingTemplate *tmpl = obj->m_template;
	const ThingTemplate *finalTmpl;
	if (tmpl == 0)
		finalTmpl = 0;
	else
	{
		Overridable *next = tmpl->m_nextOverride;
		if (next != 0)
			tmpl = (ThingTemplate *)((BfmeOverridable *)next)->getFinalOverride();
		finalTmpl = tmpl;
	}

	const WeaponTemplateSet *set = ((const BfmeThingTemplate *)finalTmpl)->findWeaponTemplateSet(obj->getWeaponSetFlags());
	if (set && set != m_curWeaponTemplateSet)
	{
		if (!set->m_isWeaponLockSharedAcrossSets)
		{
			Object *owner = TheGameLogic->findObjectByID(m_objectId);
			if (m_curWeaponLockedStatus != 0)
			{
				m_curWeaponLockedStatus = 0;
				if (owner)
					owner->clearModelConditionFlags(ModelConditionFlags(ModelConditionFlags::kInit, 0x88, 0x89, 0x8A));
			}
			m_curWeapon = PRIMARY_WEAPON;
		}
		m_filledWeaponSlotMask = 0;
		m_totalAntiMask = 0;
		m_totalDamageTypeMask = 0;
		m_hasPitchLimit = false;
		m_hasDamageWeapon = false;
		for (Int i = 4 - 1; i >= PRIMARY_WEAPON; --i)
		{
			if (m_weapons[i] != 0)
			{
				delete m_weapons[i];
				m_weapons[i] = 0;
			}

			if (set->m_template[i])
			{
				WeaponTemplate *found = TheWeaponStore->findWeaponTemplatePrivate(set->m_template[i]->getNameKey());
				if (found)
				{
					m_weapons[i] = TheWeaponStore->allocateNewWeapon(found, (WeaponSlotType)i);
					m_weapons[i]->m_ownerId = obj->m_id;
					((BfmeWeapon *)m_weapons[i])->loadAmmoNow(obj);
					m_filledWeaponSlotMask |= (1 << i);
					m_totalAntiMask |= m_weapons[i]->m_template->m_antiMask;
					m_totalDamageTypeMask |= (1 << m_weapons[i]->m_template->m_damageType);
					if (m_weapons[i]->m_pitchLimited)
						m_hasPitchLimit = true;
					if (m_weapons[i]->m_template->m_isDamageWeapon)
						m_hasDamageWeapon = true;
				}
			}
		}
		m_curWeaponTemplateSet = set;
		m_objectId = obj->m_id;
	}
}
