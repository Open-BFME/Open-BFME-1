// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// Retail 0x001CD990 (129 bytes).  This is the BFME Object firing path that
// accepts both the target object and its already-known ObjectID.  The
// address-derived owner is intentional: the retail caller/source surface in
// this checkout has only the one-argument Object::fireCurrentWeapon overload,
// while this body has a two-argument thiscall ABI (ret 8).
//
// The weapon array/index and private-status offsets are independently shared
// by Object's landed weapon-set conversions.  The fire wrappers are the
// existing Weapon bodies at 0x001EA6D0/0x001EA5F0.  The tracker call is the
// complete four-argument retail body at 0x001B3510 (ret 0x10), not the
// two-argument Zero Hour declaration.

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef int ObjectID;
typedef int Int;

class Object;
class Weapon;

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

class WeaponTemplate
{
private:
	unsigned char m_pad00[0x68];

public:
	int m_statusSentinel;
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	bool rva001EA6D0(const Object *source, const Object *target);
	bool rva001EA5F0(const Object *source, ObjectID targetID,
		const Object *target, ObjectID *projectileID);

	void *m_vtable;
	WeaponTemplate *m_template;
};

class Rva001CD990FiringTracker
{
public:
	void rva001B3510(const Weapon *weapon, ObjectID targetID,
		const void *optionalTarget, Bool optionalFlag);
};

class BfmeItem1005
{
public:
	void bfmeDoD1005(Int value);
};

// The retail ILT is the source-of-truth symbol for the incomplete tracker
// declaration.  The identity is pinned locally because the complete retail
// body has four stack arguments while the old Zero Hour declaration has two.

class Rva001CD990Object
{
public:
	void fireCurrentWeapon(const Object *target, ObjectID targetID);

private:
	unsigned char m_before94[0x94];
	unsigned char m_fireMode;
	unsigned char m_gap95[0x1ec - 0x95];
	Rva001CD990FiringTracker *m_firingTracker;
	unsigned char m_gap1f0[0x26c - 0x1f0];
	Weapon *m_weapons[4];
	UnsignedInt m_currentWeapon;
	unsigned char m_gap280[0x344 - 0x280];
	unsigned char m_privateStatus;
};

void Rva001CD990Object::fireCurrentWeapon(const Object *target,
	ObjectID targetID)
{
	if (target == 0)
		return;

	Weapon *weapon = m_weapons[m_currentWeapon];
	if (weapon == 0 || weapon->getStatus() != READY_TO_FIRE)
		return;

	if ((m_fireMode & 0x10) != 0)
		weapon->rva001EA6D0((const Object *)this, target);
	else
		weapon->rva001EA5F0((const Object *)this, targetID, target, 0);

	if (m_firingTracker != 0)
		m_firingTracker->rva001B3510(weapon, targetID, 0, 0);

	if (weapon->m_template->m_statusSentinel == -1)
		((BfmeItem1005 *)this)->bfmeDoD1005(1);

	m_privateStatus &= (unsigned char)~2;
}
