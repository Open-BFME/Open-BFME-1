// cl: /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME's SpawnBehavior interface passes this method a secondary-base pointer.
// The fields below use that adjusted pointer, so the spawn lists start at +0x24.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <algorithm>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class DamageInfo
{
	public:
	unsigned char m_pad00[8];
	ObjectID m_sourceID;
};

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);
};

class BFMEReportDamageSource
{
public:
	void report(Object *owner, int setting);
};

class SpawnBehaviorModuleData
{
public:
	unsigned char m_pad00[0xc];
	int m_spawnReplaceDelayData;
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	unsigned int m_frame;
	Object *findObjectByID(ObjectID id);
};

#define TheGameLogic (*(GameLogic **)0x012f0898)

class SpawnBehavior
{
public:
	virtual void onSpawnDeath(ObjectID deadSpawn, DamageInfo *damageInfo);

private:
	unsigned char m_pad00[0x20];
	_STL::list<int> m_replacementTimes;
	_STL::list<ObjectID> m_spawnIDs;
	unsigned char m_active;
	unsigned char m_aggregateHealth;
	unsigned char m_pad2e[2];
	unsigned int m_spawnCount;
};

// ?onSpawnDeath@SpawnBehavior@@UAEXW4ObjectID@@PAVDamageInfo@@@Z
void SpawnBehavior::onSpawnDeath(ObjectID deadSpawn, DamageInfo *damageInfo)
{
	_STL::list<ObjectID>::iterator it = _STL::find(m_spawnIDs.begin(), m_spawnIDs.end(), deadSpawn);

	if (it == m_spawnIDs.end())
		return;

	SpawnBehaviorModuleData *moduleData = *reinterpret_cast<SpawnBehaviorModuleData **>(
		reinterpret_cast<unsigned char *>(this) - 0x1c);
	int replacementTime = moduleData->m_spawnReplaceDelayData + TheGameLogic->m_frame;
	m_replacementTimes.push_back(replacementTime);
	m_spawnIDs.erase(it);
	--m_spawnCount;

	if (m_spawnCount == 0 && m_aggregateHealth)
	{
		Object *killer = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
		if (killer != 0)
		{
			Object *owner = *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 0x18);
			(reinterpret_cast<BFMEReportDamageSource *>(killer))->report(owner, 1);
		}
		Object *owner = *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 0x18);
		owner->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	}
}
