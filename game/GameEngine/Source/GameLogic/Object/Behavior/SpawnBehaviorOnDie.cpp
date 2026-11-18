// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <hash_map>
#include "../../../Common/Thing/GameLogicObjectLookup.h"

// SpawnBehavior::onDie, retail 0x0020B340 (298 bytes), ilt_oracle CONFIRMED;
// table VA 0x010A6BCC slot 0 through ILT 0x000102B7.  The receiver is the
// DieModuleInterface subobject at +0x24.  The Zero Hour body as written: VC7.1
// keeps the first GameLogic::findObjectByID call out of line and inlines the
// second hash-map lookup, exactly as retail does.

#include "../../../../Include/Common/ScalarTypes.h"

// Zero Hour GameLogic.h preserves this older BFME hash-map body in a comment.
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == 0)
		return 0;
	ObjectPtrHash::iterator it = m_objHash.find(id);
	if (it == m_objHash.end())
		return 0;
	return (*it).second;
}
extern GameLogic *TheGameLogic;

class DamageInfo;
enum DamageType { DAMAGE_UNRESISTABLE = 8 };
#include "../../../../Include/Common/Enums/DeathType.h"

class SlavedUpdateInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void onSlaverDie(const DamageInfo *damageInfo);
};

class BehaviorModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
	virtual void s18();
	virtual SlavedUpdateInterface *getSlavedUpdateInterface();
};

class ModuleFront
{
public:
	virtual ~ModuleFront();
private:
	unsigned char m_pad04[8];
};

class BehaviorModule : public ModuleFront, public BehaviorModuleInterface
{
};

class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	void setProducer(const Object *obj);
	void kill(DamageType damageType, DeathType deathType);

private:
	unsigned char m_pad00[0x1f0];
	BehaviorModule **m_behaviors;
	unsigned char m_pad1f4[0x150];
	unsigned char m_privateStatus;
};

class DieMuxData
{
public:
	Bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;
};

class SpawnBehaviorModuleData
{
public:
	unsigned char m_pad00[0x18];
	Bool m_spawnedRequireSpawner;
	unsigned char m_pad19[0x13];
	DieMuxData m_dieMuxData;
};

class SpawnBehaviorFront
{
public:
	virtual ~SpawnBehaviorFront();
	const SpawnBehaviorModuleData *getSpawnBehaviorModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	const SpawnBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0c[0x18];
};

class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

typedef _STL::list<ObjectID> objectIDList;
typedef objectIDList::iterator objectIDListIterator;

class SpawnBehavior : public SpawnBehaviorFront, public DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo);

private:
	unsigned char m_pad28[0x20];
	objectIDList m_spawnIDs;
};

// ?onDie@SpawnBehavior@@UAEXPBVDamageInfo@@@Z
void SpawnBehavior::onDie(const DamageInfo *damageInfo)
{
	const SpawnBehaviorModuleData *modData = getSpawnBehaviorModuleData();

	if (modData->m_dieMuxData.isDieApplicable(getObject(), damageInfo) == false)
		return;

	for (objectIDListIterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		Object *currentSpawn = TheGameLogic->findObjectByID(*iter);
		if (currentSpawn)
		{
			for (BehaviorModule **update = currentSpawn->getBehaviorModules(); *update; ++update)
			{
				SlavedUpdateInterface *sdu = (*update)->getSlavedUpdateInterface();
				if (sdu != NULL)
				{
					sdu->onSlaverDie(damageInfo);
					break;
				}
			}
			currentSpawn->setProducer(NULL);
		}
	}

	if (modData->m_spawnedRequireSpawner)
	{
		Object *obj;
		for (objectIDListIterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); )
		{
			obj = TheGameLogic->findObjectByID(*it);
			++it;
			if (obj && !obj->isEffectivelyDead())
				obj->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
		}
	}
}
