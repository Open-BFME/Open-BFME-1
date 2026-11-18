// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Igame/GameEngine/Source/Common/System
// stlport
//
// W3DGhostObjectManager::DoXfer (ZH W3DGhostObjectManager::xfer), retail RVA
// 0x006BDC10, 395 bytes: two RET 4 exits, then the hash-hit block that ends
// with the backward JMP at +0x189 (INT3 padding from +0x18B).
// Identity: the matched constructor 0x006BC8C0 installs vftable 0x0111CFE0,
// whose slot 2 is the "W3DGhostObjectManager" name getter 0x006BC8E0 and whose
// slot 3 (the BFME Snapshot DoXfer slot) reaches this body through ILT
// 0x0000D12A. tools/ilt_oracle.py CONFIRMS
// ?DoXfer@W3DGhostObjectManager@@MAEXAAVXfer@@@Z here (p_false 1.96e-04,
// exact) and contradicts the ZH ?xfer@...@@MAEXPAVXfer@@@Z spelling.
//
// Body: base transfer, light-CRC early out, version 1, the used-module count,
// then per ghost the parent ObjectID and the ghost snapshot (save) or the
// ObjectID, an inline GameLogic hash lookup, addGhostObject and the shroud
// manager's provider bind (load). BFME's addGhostObject takes only the Object
// (W3DGhostObjectAdd.cpp), and the ZH partition-data link became the
// TheShroudManager forwarder 0x008F73B0, which hands both CDE providers
// (Object +0x64 and the ghost's secondary base at +4) to 0x008F8C70.
//
// Frame: retail keeps count in the dead xfer argument slot and the version
// pair in the frame beside the loop counter. VC7.1 gives that layout when
// count is declared ahead of the version block in one enclosing block and the
// version is the constructed XferVersion record; a plain Xfer::Version
// aggregate always took the argument slot instead (3 bytes at +0x26/+0x2A/+0x2F).

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"


#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>

#include "xfer.h"
#include "snapshot.h"

// BFME's two-byte version record (version, current version) built in place,
// as LivingWorldEyeTowerDoXfer.cpp spells it.
struct XferVersion : Xfer::Version
{
	XferVersion(unsigned char version)
	{
		data[0] = version;
		data[1] = version;
	}
};

#include "../../../../GameEngine/Include/Common/ObjectID.h"





// The ObjectID transfer at 0x0010C3C0 (called through ILT 0x0000C9B4) by its
// ledger name, with its proven cdecl ABI and Xfer reference result
// (identity_evidence/0010c3c0-objectid-return.md), as TunnelTracker_xfer.cpp
// calls it.
class MidVirtualSlot90Receiver;
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *context);

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
	_STL::equal_to<UnsignedInt> > ObjectPtrHash;

// Retail inlines the ID lookup over the object hash at GameLogic +0xB0.
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == INVALID_ID)
			return 0;

		ObjectPtrHash::iterator it = m_objectHash.find(id);
		if (it == m_objectHash.end())
			return 0;
		return (*it).second;
	}

	char m_head[0xb0];
	ObjectPtrHash m_objectHash;		// +0xb0
};

extern GameLogic *TheGameLogic;

class ShroudManagerImpl
{
public:
	void rva008F8C70(CDEProvider *first, CDEProvider *second);
};

class ShroudManager
{
public:
	// 0x008F73B0: mov ecx,[ecx+0Ch]; jmp 0x008F8C70, the matched
	// ShroudManagerImpl::rva008F8C70(CDEProvider *, CDEProvider *) (RET 8).
	__declspec(noinline) void rva008F73B0(CDEProvider *objectProvider, CDEProvider *ghostProvider);
};

// Retail 0x008F73B0: mov ecx,[ecx+0x0c]; jmp 0x008F8C70.
// DoXfer supplies two provider pointers, preserved by the tail jump.
// The matched implementation returns with ret 8. Keep the forwarder out
// of line so this TU's DoXfer retains its retail call rather than inlining it.
void ShroudManager::rva008F73B0(CDEProvider *objectProvider, CDEProvider *ghostProvider)
{
	ShroudManagerImpl *implementation =
		*reinterpret_cast<ShroudManagerImpl **>(reinterpret_cast<char *>(this) + 0x0c);
	implementation->rva008F8C70(objectProvider, ghostProvider);
}

extern ShroudManager *TheShroudManager;

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

class GhostObjectManager : public Snapshot
{
public:
	virtual ~GhostObjectManager();
	virtual void slot4();			// 0x006BDB00
	virtual void setLocalPlayerIndex(int index);
	virtual void slot6();			// 0x006BC9F0
	virtual GhostObject *addGhostObject(Object *object);	// +0x1c

	void saveLockGhostObjects(bool enable) { m_saveLockGhostObjects = enable; }

protected:
	// The base transfer 0x001B3B00 (ILT 0x00024230) keeps its ledger
	// spelling ?xfer@GhostObjectManager@@MAEXPAVXfer@@@Z here; it is the base
	// Snapshot slot 3 body, which this body calls directly. Declared last so
	// it adds no slot ahead of addGhostObject.
	virtual void xfer(Xfer *xfer);

	int m_localPlayerIndex;
	bool m_lockGhostObjects;
	bool m_saveLockGhostObjects;	// +0x09
};

extern GhostObjectManager *TheGhostObjectManager;

class W3DGhostObjectManager : public GhostObjectManager
{
public:
	virtual GhostObject *addGhostObject(Object *object);

protected:
	virtual void DoXfer(Xfer &xfer);

	W3DGhostObject *m_freeModules;	// +0x0c
	W3DGhostObject *m_usedModules;	// +0x10
};

// ?DoXfer@W3DGhostObjectManager@@MAEXAAVXfer@@@Z
void W3DGhostObjectManager::DoXfer(Xfer &xfer)
{
	GhostObjectManager::xfer(&xfer);

	if (xfer.IsLightCRC())
		return;

	{
		UnsignedShort count;

		{
			XferVersion version(1);
			xfer == version;
		}

		count = 0;
		W3DGhostObject *w3dGhostObject;
		for (w3dGhostObject = m_usedModules; w3dGhostObject; w3dGhostObject = w3dGhostObject->m_nextSystem)
			count++;

		xfer == count;

		ObjectID objectID;
		if (xfer.IsStoring())
		{
			for (w3dGhostObject = m_usedModules; w3dGhostObject; w3dGhostObject = w3dGhostObject->m_nextSystem)
			{
				if (w3dGhostObject->m_parentObject)
					objectID = w3dGhostObject->m_parentObject->getID();
				else
					objectID = INVALID_ID;
				Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &objectID);

				xfer == *w3dGhostObject;
			}
		}
		else
		{
			TheGhostObjectManager->saveLockGhostObjects(false);

			GhostObject *ghostObject;
			Object *object;
			for (UnsignedShort i = 0; i < count; ++i)
			{
				Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &objectID);

				object = TheGameLogic->findObjectByID(objectID);
				if (object)
				{
					ghostObject = addGhostObject(object);
					TheShroudManager->rva008F73B0(&object->m_provider, ghostObject);
				}
				else
				{
					ghostObject = addGhostObject(0);
				}

				xfer == *ghostObject;
			}
		}
	}
}
