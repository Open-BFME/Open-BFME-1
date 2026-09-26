// cl: /DNDEBUG /MD /EHsc
// stlport

// Retail 0x0018BB10, 282 bytes. Shape-twin of Zero Hour's Squad::getAllObjects
// (zh_fuzzy_twins 0.85): clear a cached Object* vector at +0x10, then walk an
// ObjectID vector at +0x04, resolving each id through TheGameLogic's object hash
// and erasing ids that no longer resolve. The +0x04 id vector is the same claim
// the re-homed 0x0018B520 sibling makes, and matched Squad rows put Squad's
// m_objectIDs at +0x08, so the owner keeps its address token rather than a
// guessed class name.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>

// An enum, as in the game: STLport then copies ids element by element on
// erase instead of memmove, which is what retail does.
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_32 = 0x7fffffff
};

class Object;

typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == INVALID_ID)
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

typedef _STL::vector<ObjectID> VecObjectID;
typedef _STL::vector<Object *> VecObjectPtr;

class Rva0018BB10Roster
{
public:
	const VecObjectPtr &liveObjects();

private:
	void *m_unmodelled_00;				// +0x00
	VecObjectID m_objectIDs;			// +0x04
	VecObjectPtr m_objectsCached;		// +0x10
};

const VecObjectPtr &Rva0018BB10Roster::liveObjects()
{
	m_objectsCached.clear();
	for (VecObjectID::iterator it = m_objectIDs.begin(); it != m_objectIDs.end(); )
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			m_objectsCached.push_back(obj);
			++it;
		}
		else
		{
			it = m_objectIDs.erase(it);
		}
	}

	return m_objectsCached;
}
