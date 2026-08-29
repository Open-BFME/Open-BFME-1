// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Open-BFME5: BFME's WeaponSet has four weapon slots, placing its current
// lock state at WeaponSet+0x1c rather than Zero Hour's three-slot offset.

typedef bool Bool;

class BFMEWeaponSetLockShim
{
public:
	int getCurWeaponLockedStatus() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool isCurWeaponLocked() const;
};

// ?isCurWeaponLocked@Object@@QBE_NXZ
Bool Object::isCurWeaponLocked() const
{
	const BFMEWeaponSetLockShim *weaponSet =
		reinterpret_cast<const BFMEWeaponSetLockShim *>(
			reinterpret_cast<const char *>(this) + 0x264);

	if (weaponSet->getCurWeaponLockedStatus())
		return true;
	return false;
}
