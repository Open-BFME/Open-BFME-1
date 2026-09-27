// ?onDie@Rva0020B340SpawnDie@@QAEXPBVDamageInfo@@@Z
// partial score=0.6 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
// stlport

// Retail 0x0020B340, 298 bytes. Shape-twin of Zero Hour's SpawnBehavior::onDie
// (zh_fuzzy_twins 0.81): gate on the module data's DieMuxData, tell every live
// spawn's slaved-update interface its slaver died and clear its producer, then
// kill the spawns when the module data requires a spawner. Entered through a
// die-interface subobject (module data at this-0x20, object at this-0x1c, the
// spawn id list at this+0x24). No named caller or vtable owner proves the
// class, so the owner keeps its address token.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef bool Bool;
typedef int ObjectID;

class Object;
class DamageInfo;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);			// out of line, 0x0009A510

	Object *findObjectByIDInline(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;
		return (*it).second;
	}

private:
	char m_pad000[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class SlavedUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void onSlaverDie(const DamageInfo *damageInfo);
};

#define BFME_SLOT(n) virtual void slot##n();
class BehaviorModuleInterface
{
public:
	BFME_SLOT(00) BFME_SLOT(01) BFME_SLOT(02) BFME_SLOT(03) BFME_SLOT(04)
	BFME_SLOT(05) BFME_SLOT(06) BFME_SLOT(07) BFME_SLOT(08) BFME_SLOT(09)
	BFME_SLOT(10) BFME_SLOT(11) BFME_SLOT(12) BFME_SLOT(13) BFME_SLOT(14)
	BFME_SLOT(15) BFME_SLOT(16) BFME_SLOT(17) BFME_SLOT(18) BFME_SLOT(19)
	BFME_SLOT(20) BFME_SLOT(21) BFME_SLOT(22) BFME_SLOT(23) BFME_SLOT(24)
	virtual SlavedUpdateInterface *getSlavedUpdateInterface();	// +0x64
};
#undef BFME_SLOT

class BehaviorModule
{
public:
	BehaviorModuleInterface *iface() { return &m_iface; }

private:
	char m_pad000[0x0C];
	BehaviorModuleInterface m_iface;				// +0x0C
};

enum DamageType { DAMAGE_TYPE_8 = 8 };
enum DeathType { DEATH_TYPE_0 = 0 };

class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	void setProducer(const Object *obj);
	void kill(DamageType damageType, DeathType deathType);
	Bool isEffectivelyDead() const { return (m_effectivelyDead & 1) != 0; }

private:
	char m_pad000[0x1F0];
	BehaviorModule **m_behaviors;					// +0x1F0
	char m_pad1F4[0x344 - 0x1F4];
	unsigned char m_effectivelyDead;				// +0x344
};

class DieMuxData
{
public:
	Bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;
};

struct Rva0020B340SpawnDieData
{
	char m_pad000[0x18];
	Bool m_spawnedRequireSpawner;					// +0x18
	char m_pad019[0x2C - 0x19];
	DieMuxData m_dieMuxData;						// +0x2C
};

class Rva0020B340SpawnDie
{
public:
	void onDie(const DamageInfo *damageInfo);

private:
	const Rva0020B340SpawnDieData *getData() const
	{
		return *(const Rva0020B340SpawnDieData *const *)((const char *)this - 0x20);
	}
	Object *getObject() const
	{
		return *(Object *const *)((const char *)this - 0x1C);
	}

	char m_pad000[0x24];
	_STL::list<ObjectID> m_spawnIDs;				// +0x24
};

void Rva0020B340SpawnDie::onDie(const DamageInfo *damageInfo)
{
	const Rva0020B340SpawnDieData *modData = getData();

	if (modData->m_dieMuxData.isDieApplicable(getObject(), damageInfo) == false)
		return;

	GameLogic *logic = TheGameLogic;
	for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		Object *currentSpawn = logic->findObjectByID(*iter);
		if (currentSpawn)
		{
			for (BehaviorModule **update = currentSpawn->getBehaviorModules(); *update; ++update)
			{
				SlavedUpdateInterface *sdu = (*update)->iface()->getSlavedUpdateInterface();
				if (sdu != 0)
				{
					sdu->onSlaverDie(damageInfo);
					break;
				}
			}

			currentSpawn->setProducer(0);
		}
		logic = TheGameLogic;
	}

	if (modData->m_spawnedRequireSpawner)
	{
		Object *obj;

		for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); )
		{
			obj = TheGameLogic->findObjectByIDInline(*it);

			++it;

			if (obj && obj->isEffectivelyDead() == false)
				obj->kill(DAMAGE_TYPE_8, DEATH_TYPE_0);
		}
	}
}
