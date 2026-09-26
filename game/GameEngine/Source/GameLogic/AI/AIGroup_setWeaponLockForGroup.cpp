// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::setWeaponLockForGroup, retail 0x00151020, 163 bytes.
//
// The identity follows the method order after AIGroup::setAttitude, the
// matched GameLogic::logicMessageDispatcher caller, and the member-list walk.
// BFME also refreshes the current weapon after setting the lock when the
// selected weapon template carries the flag at +0x532 and its status is ready.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef bool Bool;
typedef int WeaponLockType;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

enum WeaponStatus
{
	WEAPON_STATUS_NOT_READY = 0
};

class WeaponTemplate
{
private:
	unsigned char m_unmodelled[0x532];

public:
	Bool m_bfmeFlag532;
};

class Rva001E1880
{
private:
	unsigned char m_unmodelled[0x10];

public:
	void set( unsigned value );
};

class Weapon
{
public:
	friend class AIGroup;

	unsigned char m_unmodelled00[4];
	WeaponTemplate *m_template;
	unsigned char m_unmodelled08[0x10];
	unsigned m_18;

private:
	WeaponStatus bfmeComputeStatus( Bool *valid ) const;
};

class Object
{
public:
	Weapon *getCurrentWeapon( WeaponSlotType *slot );
	Bool setWeaponLock( Int slot, Int lockType );
};

class AIGroup
{
public:
	Bool setWeaponLockForGroup( Int weaponSlot, Int lockType );

private:
	unsigned char m_unmodelled00[4];
	_STL::list<Object *> m_memberList;
};

Bool AIGroup::setWeaponLockForGroup( Int weaponSlot, Int lockType )
{
	Bool any = false;
	_STL::list<Object *>::iterator i;

	for ( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		Object *object = *i;
		if ( object )
		{
			Weapon *weapon = object->getCurrentWeapon( (WeaponSlotType *)0 );
			if ( object->setWeaponLock( weaponSlot, lockType ) )
				any = true;

			if ( weapon && weapon->m_template->m_bfmeFlag532 )
			{
				if ( weapon->bfmeComputeStatus( 0 ) )
				{
					Weapon *currentWeapon = object->getCurrentWeapon( (WeaponSlotType *)0 );
					currentWeapon->m_18 = weapon->m_18;
					reinterpret_cast<Rva001E1880 *>( currentWeapon )->set( 1 );
				}
			}
		}
	}

	return any;
}
