// Byte-exact BFME overload of WeaponStore::createAndFireTempWeapon.
// The third parameter has type const Object*.
// MSVC gives this body a different decorated name from the nonconst-target
// overload at 0x001EAA40.

extern "C" void __cdecl __identifier("?d_001e9fd0@@YAXXZ")();
#include "../../../../Libraries/Include/Lib/Coord3D.h"


class Object
{
public:
	char m_pad[0x38];
	Coord3D m_position;
	char m_pad44[0x74 - 0x44];
	int m_id;
};

class WeaponTemplate;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class Weapon
{
public:
	virtual ~Weapon();
	void loadAmmoNow(const Object *source);
	bool privateFireWeapon(const Object * a0,const Coord3D * a1,const Object * a2,int a3,const Coord3D * a4,int a5,int a6,int a7,int * a8) {
	 // retail body is still the gen-dump row ?d_001e9fd0@@YAXXZ (no C++ row yet); call it by that defined name
	 union { void (__cdecl *symbol)(); bool (Weapon::*member)(const Object *,const Coord3D *,const Object *,int,const Coord3D *,int,int,int,int *); } c;
	 c.symbol = &__identifier("?d_001e9fd0@@YAXXZ");
	 return (this->*c.member)(a0,a1,a2,a3,a4,a5,a6,a7,a8);
	}
	void deleteInstance() { delete this; }

	int m_pad04;
	int m_sourceId;
};

class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
	void createAndFireTempWeapon(const WeaponTemplate *weaponTemplate, const Object *source,
		const Object *target);
};

extern WeaponStore *TheWeaponStore;

void WeaponStore::createAndFireTempWeapon(const WeaponTemplate *weaponTemplate,
	const Object *source, const Object *target)
{
	if (weaponTemplate == 0)
		return;
	Weapon *temporaryWeapon = TheWeaponStore->allocateNewWeapon(weaponTemplate, PRIMARY_WEAPON);
	if (source)
		temporaryWeapon->m_sourceId = source->m_id;
	temporaryWeapon->loadAmmoNow(source);
	temporaryWeapon->privateFireWeapon(source, &source->m_position, target, target->m_id,
		0, 1, 1, 0, 0);
	temporaryWeapon->deleteInstance();
}
