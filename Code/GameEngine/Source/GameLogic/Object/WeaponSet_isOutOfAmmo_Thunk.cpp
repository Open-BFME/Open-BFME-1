// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponSet::isOutOfAmmo, retail 0x001EAE70.
//
// The Zero Hour body unchanged. One constant differs and it is a structural
// one: the loop runs to 4, where ZH's WEAPONSLOT_COUNT is 3. BFME's weapon set
// has a fourth slot.
//
// That is why this is a focused TU rather than an edit to WeaponSet.cpp:
// correcting WEAPONSLOT_COUNT is a header change, and it widens
// m_weapons[WEAPONSLOT_COUNT] from twelve bytes to sixteen, moving everything
// the nine matched rows in that file read after it.
//
// m_weapons itself is at +0x08, which this tree already has right, and
// OUT_OF_AMMO compares as 1.

enum WeaponStatus
{
	READY_TO_FIRE,									///< 0
	OUT_OF_AMMO										///< retail compares against 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	WeaponStatus getStatus(void) const;				///< ILT 0x0000978C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponSet
{
public:
	bool isOutOfAmmo(void) const;

private:
	char m_unreconstructed_00[8];
	Weapon *m_weapons[4];							///< retail this+0x08; BFME has four slots
};

// ?isOutOfAmmo@WeaponSet@@QBE_NXZ
bool WeaponSet::isOutOfAmmo() const
{
	for( int i = 0; i < 4;	i++ )
	{
		const Weapon* weapon = m_weapons[i];
		if (weapon == 0)
			continue;
		if (weapon->getStatus() != OUT_OF_AMMO)
		{
			return false;
		}
	}
	return true;
}
