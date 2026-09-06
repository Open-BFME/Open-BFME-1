// Byte-exact BFME overload of WeaponStore::createAndFireTempWeapon.
// The third parameter has type const Object*.
// MSVC gives this body a different decorated name from the nonconst-target
// overload at 0x001EAA40.

struct Coord3D
{
	float x;
	float y;
	float z;
};

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
	bool privateFireWeapon(const Object *source, const Coord3D *sourcePos,
		const Object *victim, int victimId, const Coord3D *victimPos,
		int a, int b, int c, int *projectileID);
	void deleteInstance() { delete this; }

	int m_pad04;
	int m_sourceId;
};

class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source,
		const Object *target);
};

extern WeaponStore *TheWeaponStore;

void WeaponStore::createAndFireTempWeapon(const WeaponTemplate *wt,
	const Object *source, const Object *target)
{
	if (wt == 0)
		return;
	Weapon *w = TheWeaponStore->allocateNewWeapon(wt, PRIMARY_WEAPON);
	if (source)
		w->m_sourceId = source->m_id;
	w->loadAmmoNow(source);
	w->privateFireWeapon(source, &source->m_position, target, target->m_id,
		0, 1, 1, 0, 0);
	w->deleteInstance();
}
