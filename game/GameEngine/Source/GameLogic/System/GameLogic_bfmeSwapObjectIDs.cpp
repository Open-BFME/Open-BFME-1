// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// The BFME object lookup is a STLport hash_map at GameLogic+0xB0.  This
// two-object helper removes both old keys, exchanges the Object IDs, then
// restores the two map entries.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int ObjectMapID;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class GameLogic;

class Object
{
public:
	ObjectMapID getID(void) const { return m_id; }

	protected:
	void setID(ObjectID id);

	private:
	friend class GameLogic;
	char m_slice_pad[0x74];
	ObjectMapID m_id;
};

typedef _STL::hash_map<ObjectMapID, Object *, _STL::hash<ObjectMapID>,
	_STL::equal_to<ObjectMapID> > ObjectPtrHash;

class GameLogic
{
public:
	void bfmeSwapObjectIDs(Object *first, Object *second);

private:
	char m_slice_pad[0xB0];
	ObjectPtrHash m_objHash;
};

void GameLogic::bfmeSwapObjectIDs(Object *first, Object *second)
{
	if (first == 0)
		return;
	if (second == 0)
		return;

	m_objHash.erase(first->getID());
	m_objHash.erase(second->getID());
	ObjectID secondID = (ObjectID)second->getID();
	ObjectID firstID = (ObjectID)first->getID();
	first->setID(secondID);
	second->setID(firstID);
	m_objHash[first->getID()] = first;
	m_objHash[second->getID()] = second;
}
