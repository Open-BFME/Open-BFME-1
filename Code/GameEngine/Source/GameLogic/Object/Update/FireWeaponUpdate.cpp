// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FireWeaponUpdateModuleData default ctor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponUpdate.h
class FireWeaponUpdateModuleData
{
public:
	FireWeaponUpdateModuleData();
	virtual ~FireWeaponUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned char m_0c;
	unsigned char m_0d;
	unsigned char m_0e;
};

// ??0FireWeaponUpdateModuleData@@QAE@XZ
FireWeaponUpdateModuleData::FireWeaponUpdateModuleData()
{
	m_08 = 0;
	m_0c = 0;
	m_0d = 0;
	m_0e = 0;
}

// FireWeaponUpdate::update, retail 0x00292F00.
//
// The retail entry is the third update-interface subobject at complete-object
// offset +0x10.  Its direct vtable slot points at this body, so `this` is the
// interface address: the module-data and ObjectModule pointers are therefore
// at this-0x0c and this-0x08, while the Weapon member is at this+0x10.  Those
// signed displacements are also why this view deliberately stays a narrow
// interface class instead of inventing the complete multiple-inheritance
// hierarchy already represented by FireWeaponUpdateCtorThunk.cpp.

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum WeaponStatus
{
	READY_TO_FIRE = 0,
	OUT_OF_AMMO = 1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
};

class Weapon
{
public:
	WeaponStatus getStatus(void) const;
	Object *forceFireWeapon(const Object *source, const Coord3D *pos);
};

class FireWeaponUpdate
{
public:
	virtual UpdateSleepTime update();
};

typedef char FWUModuleDataSize[(sizeof(FireWeaponUpdateModuleData) == 0x10) ? 1 : -1];
typedef char FWUPositionSize[(sizeof(Coord3D) == 12) ? 1 : -1];

// ?update@FireWeaponUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime FireWeaponUpdate::update()
{
	unsigned char *self = (unsigned char *)this;
	unsigned char *moduleData = *(unsigned char **)(self - 0x0c);

	if (moduleData[0x0c] != 0 &&
		(*(unsigned int *)((unsigned char *)*(void **)(self - 0x08) + 0x128) & 0x00020000) == 0)
		return UPDATE_SLEEP_NONE;

	if (moduleData[0x0d] != 0 &&
		(*(unsigned int *)((unsigned char *)*(void **)(self - 0x08) + 0x11c) & 0x10000000) == 0)
		return UPDATE_SLEEP_NONE;

	if (moduleData[0x0e] != 0 &&
		(*(unsigned char *)((unsigned char *)*(void **)(self - 0x08) + 0x344) & 1) != 0)
		return UPDATE_SLEEP_NONE;

	if (*(Weapon **)(self + 0x10) != 0 &&
		(*(Weapon **)(self + 0x10))->getStatus() == READY_TO_FIRE)
	{
		Object *object = *(Object **)(self - 0x08);
		(*(Weapon **)(self + 0x10))->forceFireWeapon(object, &object->m_position);
	}

	return UPDATE_SLEEP_NONE;
}
