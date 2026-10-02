// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include "../../../Common/Thing/GameLogicObjectLookup.h"

class Object
{
public:
	ObjectID getID() const
	{
		return m_id;
	}

	ObjectID getProducerID() const
	{
		return m_producerID;
	}

private:
	char m_pad[0x74];
	ObjectID m_id;
	ObjectID m_producerID;
};

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

class SpecialAbilityUpdate
{
public:
	Object *findSpecialObjectWithProducerID(const Object *target);

private:
	char m_pad[0xcc];
	_STL::list<ObjectID> m_specialObjectIDList;
};

// ?findSpecialObjectWithProducerID@SpecialAbilityUpdate@@QAEPAVObject@@PBV2@@Z
Object *SpecialAbilityUpdate::findSpecialObjectWithProducerID(const Object *target)
{
	Object *specialObject;
	_STL::list<ObjectID>::iterator i;
	for (i = m_specialObjectIDList.begin();
		i != m_specialObjectIDList.end(); ++i)
	{
		specialObject = findObjectByIDInline(TheGameLogic, *i);
		if (specialObject)
		{
			if (specialObject->getProducerID() == target->getID())
				return specialObject;
		}
	}
	return 0;
}
