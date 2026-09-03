// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?createAndFireTempWeapon@WeaponStore@@: Code/GameEngine/Source/GameLogic/Object/Weapon.cpp
//
// BFME WeaponStore::createAndFireTempWeapon overloads. allocateNewWeapon and
// loadAmmoNow are already matched; privateFireWeapon is the nine-arg body at
// 0x001E9FD0. Named like the Zero Hour store methods: they reload TheWeaponStore
// rather than using this.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
	virtual ~Weapon();
	void loadAmmoNow(const Object *source);
	bool privateFireWeapon(const Object *source, const Coord3D *sourcePos,
		const Object *victim, int victimId, const Coord3D *victimPos,
		int a, int b, int c, int *projectileID);
	void deleteInstance() { delete this; }

	int m_pad04; // +0x04
	int m_sourceId; // +0x08
	char m_pad0C[0x50 - 0x0C];
	int m_when; // +0x50
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	int getFrame() const { return m_frame; }
	char m_pad[0x3c];
	int m_frame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Coord3D *sourcePos,
		const Object *source, const Coord3D *pos, int extra);
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos);
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, Object *target);
};

extern WeaponStore *TheWeaponStore;
extern GameLogic *TheGameLogic;

void WeaponStore::createAndFireTempWeapon(const WeaponTemplate *wt, const Coord3D *sourcePos,
	const Object *source, const Coord3D *pos, int extra)
{
	Weapon *w = TheWeaponStore->allocateNewWeapon(wt, PRIMARY_WEAPON);
	if (source)
		w->m_sourceId = source->m_id;
	w->loadAmmoNow(source);
	w->privateFireWeapon(source, sourcePos, 0, 0, pos, 1, 0, extra, 0);
	if (w)
		w->deleteInstance();
}

void WeaponStore::createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos)
{
	if (wt == 0)
		return;
	Weapon *w = TheWeaponStore->allocateNewWeapon(wt, PRIMARY_WEAPON);
	if (source)
		w->m_sourceId = source->m_id;
	w->loadAmmoNow(source);
	w->m_when = TheGameLogic->getFrame() + 1;
	w->privateFireWeapon(source, &source->m_position, 0, 0, pos, 0, 0, 0, 0);
	w->deleteInstance();
}

void WeaponStore::createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, Object *target)
{
	if (wt == 0)
		return;
	Weapon *w = TheWeaponStore->allocateNewWeapon(wt, PRIMARY_WEAPON);
	if (source)
		w->m_sourceId = source->m_id;
	w->loadAmmoNow(source);
	w->m_when = TheGameLogic->getFrame() + 1;
	w->privateFireWeapon(source, &source->m_position, target, target->m_id, 0, 0, 0, 0, 0);
	w->deleteInstance();
}
