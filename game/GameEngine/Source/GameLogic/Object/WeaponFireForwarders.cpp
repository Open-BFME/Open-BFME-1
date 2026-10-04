struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	unsigned char m_bfmeHeadYB[0x74];
	int m_id;
};

class Weapon
{
public:

	bool bfmeFireYB(const Object *src, const Coord3D *pos, const Coord3D *alt, int n);
	bool bfmeFireYC(const Object *src, const Coord3D *pos, const Object *tgt, int n);
};

// Retail reaches the nine-argument body through ILT 0x00030A8A, owned by the
// ledger as ?j_00030a8a@@YAXXZ; ecx (the weapon) is not reloaded.
extern void j_00030a8a();
typedef bool (Weapon::*PrivateFireWeaponCall)(const Object *, const Coord3D *, const Object *, int, const Coord3D *, int, int, int, int *);

union PrivateFireWeaponRoute
{
	void (*raw)();
	PrivateFireWeaponCall member;
};

bool Weapon::bfmeFireYB(const Object *src, const Coord3D *pos, const Coord3D *alt, int n)
{
	PrivateFireWeaponRoute call;
	call.raw = j_00030a8a;
	return (this->*call.member)(src, pos, 0, 0, alt, 1, 0, n, 0);
}

bool Weapon::bfmeFireYC(const Object *src, const Coord3D *pos, const Object *tgt, int n)
{
	PrivateFireWeaponRoute call;
	call.raw = j_00030a8a;
	return (this->*call.member)(src, pos, tgt, tgt->m_id, 0, 1, 0, n, 0);
}
