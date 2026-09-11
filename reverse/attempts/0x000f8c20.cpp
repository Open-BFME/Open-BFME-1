// ?onTunnelDestroyed@TunnelTracker@@QAEXPBVObject@@@Z
// partial score=0.99 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body: Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp
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

#pragma comment(linker, "/alternatename:?TheGameLogic@@3PAVGameLogic@@A=?TheBfmeGameLogic@@3PAVGameLogic@@A")

#pragma comment(linker, "/alternatename:?onContainedBy@Object@@QAEXPAV1@@Z=?j_000020a9@@YAXXZ")

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
		ObjectID firstID = m_tunnelIDs.front();
		Object *validTunnel = TheGameLogic->findObjectByID(firstID);
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
