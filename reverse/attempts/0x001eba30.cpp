// ?setWeaponLock@WeaponSet@@QAE_NW4WeaponSlotType@@W4WeaponLockType@@@Z
// partial score=0.92 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: WeaponSet::setWeaponLock, retail 0x001EBA30, 214 bytes.
//
// The BFME WeaponSet keeps four weapon pointers and the owning ObjectID at
// +0x34.  The owner lookup, 304-bit clear mask, and condition-word update are
// kept in this focused TU because the shared ZH WeaponSet header has a
// different model-condition ABI.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
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

template <int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, Int idx1, Int idx2, Int idx3);

private:
	UnsignedInt m_bits[10];
};

class Object
{
public:
	void clearModelConditionFlags(const BitFlags<304> &clear);
	void notifyModelConditionChanged();
	unsigned char m_pad_00[0x120];
	UnsignedInt m_conditionWord4;
};

extern void j_0002191d();
typedef void (Object::*NotifyModelConditionChangedCall)();

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
extern void j_0001f253();
typedef Object *(GameLogic::*FindObjectByIDCall)(ObjectID);

class Weapon
{
};

class Snapshot
{
public:
	virtual void crc();
	virtual void xfer();
	virtual void loadPostProcess();
};

class WeaponTemplateSet
{
};

class WeaponSet : public Snapshot
{
public:
	Bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);

public:
	const WeaponTemplateSet *m_curWeaponTemplateSet;
	Weapon *m_weapons[4];
	WeaponSlotType m_curWeapon;
	WeaponLockType m_curWeaponLockedStatus;
	UnsignedInt m_filledWeaponSlotMask;
	Int m_totalAntiMask;
	UnsignedInt m_totalDamageTypeMask;
	Bool m_hasPitchLimit;
	Bool m_hasDamageWeapon;
	unsigned char m_pad_2e[0x34 - 0x2e];
	ObjectID m_objectId;
};

Bool WeaponSet::setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType)
{
	ObjectID objectID = *reinterpret_cast<const ObjectID *>(
		reinterpret_cast<const char *>(this) + 0x34);
	union
	{
		void (*asVoid)();
		FindObjectByIDCall asMember;
	} findObjectCast;
	findObjectCast.asVoid = j_0001f253;
	Object *owner = (TheBfmeGameLogic->*findObjectCast.asMember)(objectID);

	if (lockType != NOT_LOCKED)
	{
		Weapon *weapon = m_weapons[weaponSlot];
		if (weapon != (Weapon *)0)
		{
			WeaponLockType permanent = LOCKED_PERMANENTLY;
			if (lockType == permanent)
			{
				m_curWeaponLockedStatus = permanent;
			}
			else if (lockType == LOCKED_TEMPORARILY &&
				m_curWeaponLockedStatus != permanent)
			{
				m_curWeaponLockedStatus = LOCKED_TEMPORARILY;
				m_curWeapon = weaponSlot;
			}

			if (owner != (Object *)0)
			{
				owner->clearModelConditionFlags(BitFlags<304>(
					(BitFlags<304>::BogusInitType)0, 0x88, 0x89, 0x8A));
			}

			UnsignedInt mask;
			switch (m_curWeapon - PRIMARY_WEAPON)
			{
			case 0:
				if (owner != (Object *)0)
				{
					mask = 0x100;
					goto applyMask;
				}
				break;
			case 1:
				if (owner != (Object *)0)
				{
					mask = 0x200;
					goto applyMask;
				}
				break;
			case 2:
				if (owner != (Object *)0)
				{
					mask = 0x400;
					goto applyMask;
				}
				break;
			}
			return true;

		applyMask:
			UnsignedInt current = owner->m_conditionWord4;
			if ((current & mask) == 0)
			{
				owner->m_conditionWord4 = current | mask;
				union
				{
					void (*asVoid)();
					NotifyModelConditionChangedCall asMember;
				} notifyCast;
				notifyCast.asVoid = j_0002191d;
				(owner->*notifyCast.asMember)();
			}
			return true;
		}
	}
	return false;
}
