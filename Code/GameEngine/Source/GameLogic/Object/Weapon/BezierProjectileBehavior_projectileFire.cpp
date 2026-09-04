// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
// stlport
// BezierProjectileBehavior one-shot fire, retail 0x001F00A0 size 236.
// Module this (not the +0x20 iface). Flag at +0x80; WeaponTemplate* at +0x40;
// Object* at +8; victim id at +0x38; source pos at +0x2C; extra at +0x74.
// Producer id is Object+0x78. ModuleData+0x4A chooses kill vs destroyObject.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef int ObjectID;

enum DamageType
{
	DAMAGE_8 = 8
};

enum DeathType
{
	DEATH_A = 0xA
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BIT_4 = 4
};

template<int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

	BitFlags() { }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Gen_00411DD0
{
public:
	void bfmeSet(Bool value);
};

class Object
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual Gen_00411DD0 *getDrawable();

	void kill(DamageType damage, DeathType death);
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);

	char m_pad04[0x38 - 4];
	Coord3D m_position;
	char m_pad44[0x78 - 0x44];
	ObjectID m_producerID;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class WeaponTemplate
{
public:
	char m_pad[0x4F9];
	unsigned char m_objectFire;
};

class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Coord3D *sourcePos,
		const Object *source, const Coord3D *pos, int extra);
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, Object *target);
};

extern WeaponStore *TheWeaponStore;

class BezierProjectileBehaviorModuleData
{
public:
	char m_pad[0x4A];
	unsigned char m_killInsteadOfDestroy;
};

class BezierProjectileBehavior
{
public:
	void projectileFire();

	char m_pad00[0x04];
	const BezierProjectileBehaviorModuleData *m_moduleData;
	Object *m_object;
	char m_pad0C[0x2C - 0x0C];
	Coord3D m_sourcePos;
	ObjectID m_victimId;
	char m_pad3C[0x40 - 0x3C];
	WeaponTemplate *m_template;
	char m_pad44[0x74 - 0x44];
	int m_extra;
	char m_pad78[0x80 - 0x78];
	unsigned char m_fired;
};

// ?projectileFire@BezierProjectileBehavior@@QAEXXZ
void BezierProjectileBehavior::projectileFire()
{
	if (m_fired)
		return;

	WeaponTemplate *wt = m_template;
	Object *obj = m_object;
	if (wt)
	{
		Object *src = obj;
		Object *found = TheGameLogic->findObjectByID(obj->m_producerID);
		if (found)
			src = found;

		Object *vic = TheGameLogic->findObjectByID(m_victimId);
		if (vic && wt->m_objectFire)
			TheWeaponStore->createAndFireTempWeapon(wt, src, vic);
		else
			TheWeaponStore->createAndFireTempWeapon(wt, &m_sourcePos, src, &obj->m_position, m_extra);

		if (!m_moduleData->m_killInsteadOfDestroy)
			TheGameLogic->destroyObject(obj);
		else
			obj->kill(DAMAGE_8, DEATH_A);
	}
	else
	{
		obj->kill(DAMAGE_8, DEATH_A);
	}

	if (obj->getDrawable())
		obj->getDrawable()->bfmeSet(true);

	m_fired = true;
	obj->setStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_BIT_4), true);
}
