// cl: /DNDEBUG /MD /EHsc
// readable body of ?getStatus@Weapon@@QBE?AW4WeaponStatus@@XZ: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp

// Open-BFME5: Weapon::getStatus, retail 0x001E6EE0, 38 bytes. The body carried
// only a machine byte-dump row; reverse/reloc_names.csv holds the name with
// identity=real.
//
// A cached query. The helper takes a bool by pointer, pre-set to true, and
// returns the status; the cache at +0x10 is only rewritten when the helper
// leaves that flag set and the value actually changed. The returned status is
// the helper's, not the cache.
//
// The method is const in the mangled name and still writes +0x10, so the cache
// is written through in the original too.

typedef bool Bool;

enum WeaponStatus { BFME_WEAPON_STATUS_NONE = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	WeaponStatus getStatus(void) const;

private:
	WeaponStatus bfmeComputeStatus(Bool *valid) const;	// ILT 0x0001E6A0

	char m_bfmeHead[0x10];
	WeaponStatus m_bfmeCached;				// +0x10
};

// ?getStatus@Weapon@@QBE?AW4WeaponStatus@@XZ
WeaponStatus Weapon::getStatus(void) const
{
	Bool valid = true;
	WeaponStatus status = bfmeComputeStatus(&valid);

	if (valid && m_bfmeCached != status)
		((Weapon *)this)->m_bfmeCached = status;

	return status;
}
