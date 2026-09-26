// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef bool Bool;
typedef int ObjectID;

class Object;

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

class Object
{
public:
	Bool isAbleToAttack() const;
};

// The vtable entry is the SpawnBehaviorInterface secondary slot at object+0x20.
// Its this pointer therefore addresses the secondary subobject, while the real
// SpawnBehavior::m_spawnIDs sentinel is at secondary-this+0x28 (object+0x48).
class SpawnBehavior
{
public:
	virtual Bool canAnySlavesAttack();

private:
	char m_pad004[0x24];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?canAnySlavesAttack@SpawnBehavior@@UAE_NXZ
Bool SpawnBehavior::canAnySlavesAttack()
{
	SpawnBehavior *self = this;
	for (_STL::list<ObjectID>::iterator it = self->m_spawnIDs.begin(); it != self->m_spawnIDs.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			if (obj->isAbleToAttack())
				return true;
		}
	}
	return false;
}
