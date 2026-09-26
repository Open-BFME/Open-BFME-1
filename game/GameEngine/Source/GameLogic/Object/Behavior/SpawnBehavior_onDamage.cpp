// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef bool Bool;
typedef int ObjectID;

class DamageInfo;
class Object;
class SlavedUpdateInterface;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
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
	virtual ObjectID getSlaverID() const = 0;
	virtual void onEnslave(const Object *slaver) = 0;
	virtual void onSlaverDie(const DamageInfo *info) = 0;
	virtual void onSlaverDamage(DamageInfo *info) = 0;
};

class BehaviorModuleBase
{
	virtual void baseSlot() = 0;
	void *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual SlavedUpdateInterface *getSlavedUpdateInterface() = 0;
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleInterface
{
};

class Object
{
public:
	BehaviorModule **getBehaviorModules()
	{
		return *reinterpret_cast<BehaviorModule ***>(reinterpret_cast<char *>(this) + 0x1F0);
	}
};

class SpawnBehavior
{
private:
	void *m_vtable;
	char m_pad004[0x18];
	_STL::list<ObjectID> m_spawnIDs;

public:
	virtual void onDamage(DamageInfo *info);
};

// ?onDamage@SpawnBehavior@@UAEXPAVDamageInfo@@@Z
void SpawnBehavior::onDamage(DamageInfo *info)
{
	for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		Object *currentSpawn = TheGameLogic->findObjectByID((*iter));
		if (currentSpawn)
		{
			for (BehaviorModule **update = currentSpawn->getBehaviorModules(); *update; ++update)
			{
				SlavedUpdateInterface *sdu = (*update)->getSlavedUpdateInterface();
				if (sdu != NULL)
				{
					sdu->onSlaverDamage(info);
					break;
				}
			}
		}
	}
}
