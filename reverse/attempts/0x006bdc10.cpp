// ?xfer@W3DGhostObjectManager@@MAEXPAVXfer@@@Z
// partial score=0.99 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /FAsc /Fabuild/luna5-006bdc10.cod /ICode/GameEngine/Source/Common/System
// stlport

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>

#include "xfer.h"
#include "snapshot.h"

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_LONG = 0x7fffffff
};

void friend_xferObjectID(Xfer *xfer, ObjectID *objectID);

// The CDE provider ABI of BfmeOwnerCDEUpdate.cpp: a leading vptr, a vbptr at
// +4 and a virtual base.
class CDEVirtualBase
{
public:
	virtual void f0();
};

class CDELeading
{
public:
	virtual void f0();
};

class CDEProvider : public CDELeading, public virtual CDEVirtualBase
{
public:
	virtual void f0();
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

	char m_pad00[0x64];
	CDEProvider m_provider;			// +0x64
	char m_pad70[0x74 - 0x70];
	ObjectID m_id;					// +0x74
};

typedef _STL::hash_map<UnsignedInt, Object *, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt> > BfmeObjectPtrHash;

class GameLogic
{
public:
	__forceinline Object *findObjectByID(ObjectID id)
	{
		if (id == INVALID_ID)
			return 0;

		BfmeObjectPtrHash::iterator it = m_objectHash.find(id);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_head[0xb0];
	BfmeObjectPtrHash m_objectHash;	// +0xb0
};

extern GameLogic *TheBfmeGameLogic;

class PartitionManager
{
public:
	// 0x008F73B0: forwards both providers to the CDE owner update at 0x008F8C70.
	void rva008F73B0(CDEProvider *objectProvider, CDEProvider *ghostProvider);
};

extern PartitionManager *TheShroudManager;

class GhostObject : public Snapshot, public CDEProvider
{
public:
	Object *m_parentObject;			// +0x0c
};

class W3DGhostObject : public GhostObject
{
public:
	char m_pad10[0x110 - 0x10];
	W3DGhostObject *m_nextSystem;	// +0x110
};

class GhostObjectManager
{
public:
	virtual ~GhostObjectManager();
	virtual void slot04();
	virtual void slot08();
	virtual void xfer(Xfer *xfer);
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual GhostObject *addGhostObject(Object *object);	// +0x1c

	void saveLockGhostObjects(bool enable) { m_saveLockGhostObjects = enable; }

	int m_localPlayerIndex;
	bool m_lockGhostObjects;
	bool m_saveLockGhostObjects;	// +0x09
};

extern GhostObjectManager *TheGhostObjectManager;

class W3DGhostObjectManager : public GhostObjectManager
{
public:
	protected:
	virtual void xfer(Xfer *xfer);

	public:
	virtual GhostObject *addGhostObject(Object *object);

	W3DGhostObject *m_freeModules;	// +0x0c
	W3DGhostObject *m_usedModules;	// +0x10
};

void W3DGhostObjectManager::xfer(Xfer *xfer)
{
	GhostObjectManager::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

		{
		Xfer::Version version;
		version.data[0] = 1;
		version.data[1] = 1;
		*xfer == version;
	}

	{
	UnsignedShort count = 0;
	W3DGhostObject *w3dGhostObject;
	for (w3dGhostObject = m_usedModules; w3dGhostObject; w3dGhostObject = w3dGhostObject->m_nextSystem)
		count++;

	*xfer == count;

	ObjectID objectID;
	if (xfer->IsStoring())
	{
		for (w3dGhostObject = m_usedModules; w3dGhostObject; w3dGhostObject = w3dGhostObject->m_nextSystem)
		{
			if (w3dGhostObject->m_parentObject)
				objectID = w3dGhostObject->m_parentObject->getID();
			else
				objectID = INVALID_ID;
			friend_xferObjectID(xfer, &objectID);

			*xfer == *w3dGhostObject;
		}
	}
	else
	{
		TheGhostObjectManager->saveLockGhostObjects(false);

		GhostObject *ghostObject;
		Object *object;
		for (UnsignedShort i = 0; i < count; ++i)
		{
			friend_xferObjectID(xfer, &objectID);

			object = TheBfmeGameLogic->findObjectByID(objectID);
			if (object)
			{
				ghostObject = addGhostObject(object);
				TheShroudManager->rva008F73B0(&object->m_provider, ghostObject);
			}
			else
			{
				ghostObject = addGhostObject(0);
			}

			*xfer == *ghostObject;
		}
	}

	}
}
