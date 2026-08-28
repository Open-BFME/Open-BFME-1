// cl: /DNDEBUG /MD /EHsc
// readable body of ?getCurrentWeapon@Object@@: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// FILE: Object_getCurrentWeapon.cpp //////////////////////////////////////////
//
// Object::getCurrentWeapon, retail 0x001BE230. No calls at all, so the whole
// body is layout: the weapon table is four pointers at +0x26C, the index of the
// one in hand is the dword at +0x27C, and the guard the body opens with is
// +0x284 - whatever that word is, a zero there means no weapon and the slot the
// caller passed is left untouched.
//
///////////////////////////////////////////////////////////////////////////////

class Weapon;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	SECONDARY_WEAPON,
	TERTIARY_WEAPON,

	WEAPONSLOT_COUNT
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Weapon *getCurrentWeapon( WeaponSlotType *slot );

private:
	unsigned char m_unmodelled_00[ 0x26C ];
	Weapon *m_weapons[ 4 ];					// +0x26C
	WeaponSlotType m_curWeapon;				// +0x27C
	unsigned char m_unmodelled_280[ 4 ];
	void *m_weaponSet;						// +0x284
};

// ?getCurrentWeapon@Object@@QAEPAVWeapon@@PAW4WeaponSlotType@@@Z
Weapon *Object::getCurrentWeapon( WeaponSlotType *slot )
{
	if( m_weaponSet == 0 )
		return 0;

	if( slot )
		*slot = m_curWeapon;

	return m_weapons[ m_curWeapon ];
}
