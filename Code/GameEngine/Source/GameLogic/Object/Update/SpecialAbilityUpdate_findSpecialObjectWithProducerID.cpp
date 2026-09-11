// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef int ObjectID;

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

typedef _STL::hash_map<ObjectID, Object *> ObjectPtrHash;

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
	char m_pad[0xb0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

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
		specialObject = TheGameLogic->findObjectByID(*i);
		if (specialObject)
		{
			if (specialObject->getProducerID() == target->getID())
				return specialObject;
		}
	}
	return 0;
}
