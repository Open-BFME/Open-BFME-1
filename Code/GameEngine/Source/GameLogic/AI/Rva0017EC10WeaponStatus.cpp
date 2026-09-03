// cl: /DNDEBUG /MD /EHsc

enum WeaponStatus
{
	WEAPON_STATUS_ZERO = 0,
	WEAPON_STATUS_READY = 4,
	WEAPON_STATUS_DONE = 5
};

enum WeaponSlotType
{
	RVA_0017EC10_PRIMARY
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Weapon;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Weapon *getCurrentWeapon( WeaponSlotType *slot );

	char m_objectFields[ 0x38 ];
	Coord3D m_position;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	WeaponStatus getStatus() const;
};

class BfmeObj1004
{
public:
	void bfmeSetA1004( int status, int value );
};

extern void j_00023e0c();
extern void j_0003ca65();

class Rva0017EC10State
{
public:
	virtual void process( Object *object );

	char m_stateFields[ 0x20 ];
	bool m_weaponActive;
};

void Rva0017EC10State::process( Object *object )
{
	WeaponSlotType slot = RVA_0017EC10_PRIMARY;
	Weapon *weapon = object->getCurrentWeapon( &slot );
	if (!weapon)
		return;

	WeaponStatus status = weapon->getStatus();
	if (m_weaponActive)
	{
		if (status == WEAPON_STATUS_READY)
			return;
		if (status == WEAPON_STATUS_ZERO)
		{
			typedef void (BfmeObj1004::*NoArgCall)();
			union { void *asVoid; NoArgCall asMember; } noArgCast;
			noArgCast.asVoid = (void *)j_00023e0c;
			(reinterpret_cast<BfmeObj1004 *>(object)->*noArgCast.asMember)();

			typedef void (BfmeObj1004::*PositionCall)( Coord3D * );
			union { void *asVoid; PositionCall asMember; } positionCast;
			positionCast.asVoid = (void *)j_0003ca65;
			(reinterpret_cast<BfmeObj1004 *>(object)->*positionCast.asMember)(
				&object->m_position);
			return;
		}
		if (status == WEAPON_STATUS_DONE)
			m_weaponActive = false;
	}
	else if (status == WEAPON_STATUS_ZERO)
	{
		m_weaponActive = true;
		reinterpret_cast<BfmeObj1004 *>(object)->bfmeSetA1004( 0xD, 1 );
	}
}
