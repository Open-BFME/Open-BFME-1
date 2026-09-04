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
	Coord3D *getAimPosition(Coord3D *result, const Object *source,
		const Object *victim, int weaponSlot);
};

Coord3D::Coord3D(WeaponTemplate *weaponTemplate, const Object *source,
	const Object *victim, int weaponSlot)
{
	weaponTemplate->getAimPosition(this, source, victim, weaponSlot);
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
