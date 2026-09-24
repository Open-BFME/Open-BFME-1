// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// TunnelTracker::onTunnelDestroyed at retail RVA 0x000F8C20 (191 bytes).
// Identity: four matched callers reach it through ILT 0x000304E0
// (CaveContain::tryToSetCaveIndex, TunnelContain::onSelling and two more).
//
// BFME keeps Object::m_id at +0x74 and Object::m_containedBy at +0x214.
// These translation-unit-local views retain those retail layouts without
// changing the shared Zero Hour headers.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	Object *getContainedBy() const { return m_containedBy; }

	void onRemovedFrom(Object *object);
	void onContainedBy(Object *object);

private:
	unsigned char m_unreconstructed_000[0x74];
	ObjectID m_id;
	unsigned char m_unreconstructed_078[0x214 - 0x78];
	Object *m_containedBy;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *object);
};

extern GameLogic *TheGameLogic;

typedef std::list<Object *> ContainedItemsList;
typedef std::list<ObjectID> ObjectIDList;

class TunnelTracker
{
public:
	void onTunnelDestroyed(const Object *deadTunnel);

private:
	void *m_vtable;
	ObjectIDList m_tunnelIDs;
	ContainedItemsList m_containList;
	ObjectIDList m_xferContainList;
	int m_containListSize;
	unsigned int m_tunnelCount;
};

// ?onTunnelDestroyed@TunnelTracker@@QAEXPBVObject@@@Z
void TunnelTracker::onTunnelDestroyed(const Object *deadTunnel)
{
	--m_tunnelCount;
	m_tunnelIDs.remove(deadTunnel->getID());

	if (m_tunnelCount == 0)
	{
		for (ContainedItemsList::iterator it = m_containList.begin();
			it != m_containList.end(); )
		{
			Object *object = *it;
			++it;
			object->onRemovedFrom(object->getContainedBy());
			TheGameLogic->destroyObject(object);
		}
		m_containList.clear();
		m_containListSize = 0;
	}
	else
	{
		// Retail reads the first ID straight off the sentinel's next node; the
		// front() iterator temporary allocates EAX for it instead of EDX.
		Object *validTunnel = TheGameLogic->findObjectByID(
			((ObjectIDList::_Node *)m_tunnelIDs._M_node._M_data->_M_next)->_M_data);
		for (ContainedItemsList::iterator it = m_containList.begin();
			it != m_containList.end(); )
		{
			Object *object = *it;
			++it;
			if (object->getContainedBy() == deadTunnel)
				object->onContainedBy(validTunnel);
		}
	}
}
