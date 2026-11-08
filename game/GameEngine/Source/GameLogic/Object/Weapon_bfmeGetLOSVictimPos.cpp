// cl: /DNDEBUG /MD /EHsc

class Object;
class WeaponTemplate;

struct Coord3D
{
	__forceinline Coord3D(WeaponTemplate *weaponTemplate, const Object *source,
		const Object *victim, int weaponSlot);

	float x, y, z;
};

class WeaponTemplate
{
public:
};

// Retail reaches WeaponTemplate::getAimPosition (0x001E65C0) through its ILT
// 0x00001C17, a defined ?j_ row.
extern void j_00001c17();

Coord3D::Coord3D(WeaponTemplate *weaponTemplate, const Object *source,
	const Object *victim, int weaponSlot)
{
	union {
		void (*raw)();
		Coord3D *(WeaponTemplate::*member)(Coord3D *, const Object *,
			const Object *, int);
	} aim;
	aim.raw = j_00001c17;
	(weaponTemplate->*aim.member)(this, source, victim, weaponSlot);
}

class Weapon
{
public:
	Coord3D bfmeGetLOSVictimPos(const Object *source, const Object *victim,
		int weaponSlot) const;

private:
	void *m_vtable;
	WeaponTemplate *m_template;
};

Coord3D Weapon::bfmeGetLOSVictimPos(const Object *source, const Object *victim,
	int weaponSlot) const
{
	return Coord3D(m_template, source, victim, weaponSlot);
}
