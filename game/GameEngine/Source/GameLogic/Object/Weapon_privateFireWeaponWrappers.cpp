// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?fireWeapon@Weapon@@: game/GameEngine/Source/GameLogic/Object/Weapon.cpp
// readable body of ?forceFireWeapon@Weapon@@QAEPAVObject@@PBV2@PBUCoord3D@@@Z: game/GameEngine/Source/GameLogic/Object/Weapon.cpp
//
// Thin Weapon thiscall wrappers around the nine-argument privateFireWeapon
// body at 0x001E9FD0 (ILT 0x00030A8A). ecx is the weapon and is not reloaded
// before the inner call.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_pad[0x38];
	Coord3D m_position; // +0x38
	char m_pad44[0x74 - 0x44];
	int m_id; // +0x74
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	bool rva001EA6D0(const Object *source, const Object *target);
	bool fireWeapon(const Object *source, const Coord3D *pos, int *projectileID);
	bool rva001EA5F0(const Object *source, int targetID, const Object *target, int *projectileID);
	Object *forceFireWeapon(const Object *source, const Coord3D *pos);
};

// Retail's Weapon::privateFireWeapon reaches the 0x00030A8A ILT thunk, which
// the ledger owns as ?j_00030a8a@@YAXXZ (game/gen_small/thunks_023.cpp). Call
// it by its defining name instead of through an undefined member.
extern void j_00030a8a();
typedef bool (Weapon::*PrivateFireWeaponCall)(
	const Object *, const Coord3D *, const Object *, int, const Coord3D *,
	int, int, int, int *);

static __forceinline bool callPrivateFireWeapon(
	Weapon *weapon, const Object *source, const Coord3D *sourcePos,
	const Object *victim, int victimId, const Coord3D *victimPos,
	int a, int b, int c, int *projectileID)
{
	union { void (*raw)(); PrivateFireWeaponCall member; } call;
	call.raw = j_00030a8a;
	return (weapon->*call.member)( source, sourcePos, victim, victimId,
		victimPos, a, b, c, projectileID );
}

bool Weapon::rva001EA6D0(const Object *source, const Object *target)
{
	return callPrivateFireWeapon(this, source, &source->m_position, target, target->m_id, 0, 1, 1, 0, 0);
}

bool Weapon::fireWeapon(const Object *source, const Coord3D *pos, int *projectileID)
{
	return callPrivateFireWeapon(this, source, &source->m_position, 0, 0, pos, 0, 0, 0, projectileID);
}

bool Weapon::rva001EA5F0(const Object *source, int targetID, const Object *target, int *projectileID)
{
	return callPrivateFireWeapon(this, source, &source->m_position, target, targetID, 0, 0, 0, 0, projectileID);
}

Object *Weapon::forceFireWeapon(const Object *source, const Coord3D *pos)
{
	int id = 0;
	callPrivateFireWeapon(this, source, &source->m_position, 0, 0, pos, 1, 0, 0, &id);
	return TheGameLogic->findObjectByID(id);
}
