// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DBFME_STLP_NODE_ALLOC /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// BFME DemoTrapUpdate uses the landed wide-result, module-data and helper ABIs.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum WeaponSlotType
{
	WEAPON_SLOT_UNKNOWN = 0
};

enum Relationship
{
	RELATIONSHIP_ENEMIES = 0
};

struct KindOfMask
{
	unsigned int bits[6];
};

class Weapon
{
	unsigned char m_pad00[0x0c];

public:
	WeaponSlotType m_slot;
};

class Thing
{
public:
	bool isAnyKindOf(const KindOfMask &) const;
	bool isAboveTerrainOrWater() const;
};

#pragma comment(linker, "/alternatename:?isAboveTerrainOrWater@Thing@@QBE_NXZ=?j_00004386@@YAXXZ")

class Object : public Thing
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *);
	Relationship getRelationship(const Object *) const;

	unsigned int getStatusFlags() const
	{
		return *(const unsigned int *)((const char *)this + 0x90);
	}

	bool isEffectivelyDead() const
	{
		return (*(const unsigned char *)((const char *)this + 0x344) & 1) != 0;
	}
};

class BfmeSpotCN;

class Gen_0016E370
{
public:
	float bfmeDistanceSquared(const BfmeSpotCN *) const;
};

class Gen_0028CA70
{
public:
	void bfmeKill();
};

struct BfmeWideResultEntry
{
	Object *object;
	unsigned int unknown04;
};

struct BfmeWideResultData
{
	BfmeWideResultEntry *begin;
	BfmeWideResultEntry *finish;
	BfmeWideResultEntry *end;
	BfmeWideResultEntry *current;
	int references;

	BfmeWideResultEntry *endPointer() const
	{
		return finish;
	}
};

struct Gen_uw_0002c471
{
	BfmeWideResultData *value;
	~Gen_uw_0002c471();
};

struct BfmeWideResult : Gen_uw_0002c471
{
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);

	Object *next(Object *&object)
	{
		if (value->current == value->endPointer())
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

class BfmeWideForwardA
{
	char m_pad00[0x0c];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideA(int, int, int, int);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

class DemoTrapUpdateModuleData
{
	virtual ~DemoTrapUpdateModuleData();

public:
	unsigned int m_pad04;
	unsigned int m_detonationWeaponTemplate;
	KindOfMask m_ignoreKindOf;

	int m_manualModeWeaponSlot;
	int m_detonationWeaponSlot;
	int m_proximityModeWeaponSlot;
	float m_triggerDetonationRange;
	int m_scanFrames;
	bool m_defaultsToProximityMode;
	bool m_friendlyDetonation;
	bool m_detonateWhenKilled;
};

class DemoTrapUpdate
{
public:
	virtual UpdateSleepTime update();

	const DemoTrapUpdateModuleData *getDemoTrapUpdateModuleData() const
	{
		return *(const DemoTrapUpdateModuleData **)((const char *)this - 0x0c);
	}

	Object *getObject() const
	{
		return *(Object **)((const char *)this - 0x08);
	}

private:
	unsigned char m_pad04[0x0c];
	int m_nextScanFrames;
	bool m_detonated;
};

// ?update@DemoTrapUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime DemoTrapUpdate::update()
{
	register DemoTrapUpdate *self = this;
	const DemoTrapUpdateModuleData *data = self->getDemoTrapUpdateModuleData();

	if (self->m_detonated)
		return UPDATE_SLEEP_NONE;
	Object *me = self->getObject();
	if ((me->getStatusFlags() & 4) != 0)
		return UPDATE_SLEEP_NONE;
	if ((me->getStatusFlags() & 0x00080000) != 0)
		return UPDATE_SLEEP_NONE;
	if (me->isEffectivelyDead())
	{
		if (data->m_detonateWhenKilled)
			((Gen_0028CA70 *)((char *)self - 0x10))->bfmeKill();
		return UPDATE_SLEEP_NONE;
	}

	Weapon *weapon = me->getCurrentWeapon(0);
	WeaponSlotType weaponSlot = weapon->m_slot;
	if (weaponSlot == data->m_detonationWeaponSlot)
	{
		((Gen_0028CA70 *)((char *)this - 0x10))->bfmeKill();
		return UPDATE_SLEEP_NONE;
	}
	if (self->m_nextScanFrames > 0)
	{
		--self->m_nextScanFrames;
		return UPDATE_SLEEP_NONE;
	}
	if (weaponSlot == data->m_manualModeWeaponSlot)
		return UPDATE_SLEEP_NONE;

	self->m_nextScanFrames = data->m_scanFrames;
	bool shallDetonate = false;
	BfmeWideResult iterator = ((BfmeWideForwardA *)ThePartitionManager)->bfmeForwardWideA(
		(int)((char *)me + 0x38), *(const int *)&data->m_triggerDetonationRange, 0, 0);
	Object *other;
	while (iterator.next(other))
	{
		if (other->isAnyKindOf(data->m_ignoreKindOf))
			continue;
		if (other->isEffectivelyDead())
			continue;
		if (self->getObject()->getRelationship(other) != RELATIONSHIP_ENEMIES)
		{
			if (!data->m_friendlyDetonation)
				return UPDATE_SLEEP_NONE;
			continue;
		}
		if (other->isAboveTerrainOrWater())
			continue;
		float distance = ((Gen_0016E370 *)me)->bfmeDistanceSquared((const BfmeSpotCN *)other);
		if (distance <= data->m_triggerDetonationRange * data->m_triggerDetonationRange)
		{
			shallDetonate = true;
			if (data->m_friendlyDetonation)
				break;
		}
	}
	if (shallDetonate)
		((Gen_0028CA70 *)((char *)self - 0x10))->bfmeKill();
	return UPDATE_SLEEP_NONE;
}
