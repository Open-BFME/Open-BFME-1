// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include "../../../Common/Thing/GameLogicObjectLookup.h"

typedef bool Bool;

extern GameLogic *TheGameLogic;

static __forceinline Object *__fastcall findObjectByIDInline(GameLogic *logic, ObjectID id)
{
	if (id == 0)
		return 0;

	ObjectPtrHash *objHash = (ObjectPtrHash *)((char *)logic + 0xB0);
	ObjectPtrHash::iterator it = objHash->find(id);
	if (it == objHash->end())
		return 0;
	return (*it).second;
}

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
		Object *obj = findObjectByIDInline(TheGameLogic, *it);
		if (obj)
		{
			if (obj->isAbleToAttack())
				return true;
		}
	}
	return false;
}
