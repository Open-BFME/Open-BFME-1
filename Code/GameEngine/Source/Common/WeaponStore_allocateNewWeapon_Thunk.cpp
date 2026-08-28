// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WeaponStore::allocateNewWeapon factory.

class Weapon;
class WeaponTemplate;
enum WeaponSlotType { WEAPON_SLOT_PLACEHOLDER };

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	Weapon(const WeaponTemplate *, WeaponSlotType);
private:
	unsigned char m_pad[0x5c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *, WeaponSlotType) const;
};

// ?allocateNewWeapon@WeaponStore@@QBEPAVWeapon@@PBVWeaponTemplate@@W4WeaponSlotType@@@Z
Weapon *WeaponStore::allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const
{
	return new Weapon(tmpl, slot);
}
