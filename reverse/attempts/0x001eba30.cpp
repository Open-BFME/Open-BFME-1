// ?setWeaponLock@WeaponSet@@QAE_NW4WeaponSlotType@@W4WeaponLockType@@@Z
// partial score=0.9 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::setWeaponLock, retail 0x001EBA30 size 214.
// Focused TU: WeaponSet.cpp keeps ZH WEAPONSLOT_COUNT==3 and no owner
// lookup. BFME finds the owner via TheGameLogic, clears USING_WEAPON_A/B/C
// (0x88/0x89/0x8A) through BitFlags<304>'s three-index ctor, then sets the
// current-slot bit at Object+0x120 and notifies.

typedef int Int;
typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	SECONDARY_WEAPON = 1,
	TERTIARY_WEAPON = 2
};

enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
};

class Weapon;
class Object;
class WeaponTemplateSet;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

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
	void clearModelConditionFlags(const ModelConditionFlags &clr);
	void notifyModelConditionChanged();

	unsigned char m_pad_00[0x120];
	unsigned int m_conditionWord4;
};

class Snapshot
{
public:
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class WeaponSet : public Snapshot
{
public:
	Bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);

private:
	const WeaponTemplateSet *m_curWeaponTemplateSet;
	Weapon *m_weapons[4];
	WeaponSlotType m_curWeapon;
	WeaponLockType m_curWeaponLockedStatus;
	unsigned int m_filledWeaponSlotMask;
	Int m_totalAntiMask;
	unsigned int m_totalDamageTypeMask;
	Bool m_hasPitchLimit;
	Bool m_hasDamageWeapon;
	unsigned char m_pad_2e[0x34 - 0x2e];
	ObjectID m_objectId;
};

// ?setWeaponLock@WeaponSet@@QAE_NW4WeaponSlotType@@W4WeaponLockType@@@Z
Bool WeaponSet::setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType)
{
	const Object *obj = TheGameLogic->findObjectByID(m_objectId);

	if (lockType != NOT_LOCKED)
	{
		weapon = m_weapons[weaponSlot];
		if (weapon != 0)
		{
			WeaponLockType permanent = LOCKED_PERMANENTLY;
			if (lockType == permanent)
			{
				m_curWeaponLockedStatus = permanent;
				m_curWeapon = weaponSlot;
			}
			else if (lockType == LOCKED_TEMPORARILY && m_curWeaponLockedStatus != permanent)
			{
				m_curWeaponLockedStatus = LOCKED_TEMPORARILY;
				m_curWeapon = weaponSlot;
			}

			if (obj)
				const_cast<Object *>(obj)->clearModelConditionFlags(ModelConditionFlags(ModelConditionFlags::kInit, 0x88, 0x89, 0x8A));

			unsigned int mask;
			switch (m_curWeapon - PRIMARY_WEAPON)
			{
			case 2:
				if (obj)
				{
					mask = 0x400;
					goto applyMask;
				}
				break;
			case 1:
				if (obj)
				{
					mask = 0x200;
					goto applyMask;
				}
				break;
			case 0:
				if (obj)
				{
					mask = 0x100;
					goto applyMask;
				}
				break;
			}
			return true;
		applyMask:
			unsigned int cur = obj->m_conditionWord4;
			if ((cur & mask) == 0)
			{
				const_cast<Object *>(obj)->m_conditionWord4 = cur | mask;
				const_cast<Object *>(obj)->notifyModelConditionChanged();
			}
			return true;
		}
	}
	return false;
}
