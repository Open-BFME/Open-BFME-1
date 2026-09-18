// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef int ObjectID;

class Object
{
};

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
	char m_pad[0xb0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class SpecialAbilityUpdate
{
public:
	void validateSpecialObjects();

private:
	char m_pad[0xcc];
	_STL::list<ObjectID> m_specialObjectIDList;
	unsigned int m_specialObjectEntries;
};

// ?validateSpecialObjects@SpecialAbilityUpdate@@QAEXXZ
void SpecialAbilityUpdate::validateSpecialObjects()
{
	Object *specialObject;
	_STL::list<ObjectID>::iterator i = m_specialObjectIDList.begin();
	while (i != m_specialObjectIDList.end())
	{
		_STL::list<ObjectID>::iterator prev = i;
		specialObject = TheGameLogic->findObjectByID(*i);
		++i;
		if (!specialObject)
		{
			m_specialObjectIDList.erase(prev);
			--m_specialObjectEntries;
		}
	}
}
