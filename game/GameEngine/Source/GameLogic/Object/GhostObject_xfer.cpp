// stlport
// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/Common/Thing /Igame/Libraries/Source/WWVegas/WWMath
// GhostObject::DoXfer (ZH GhostObject::xfer), retail RVA 0x001B3B70, 185
// bytes (ret 4 at +0xB6).
// Identity: the GhostObject constructor 0x001B3CF0 installs vftable
// 0x0109CE94 at +0. Its slot 0 is ??_GGhostObject (0x001B3EF0), slot 1
// loadPostProcess (0x001B3DD0), and slot 3, the BFME Snapshot DoXfer slot,
// reaches this body through ILT 0x0003C1CD. tools/ilt_oracle.py check
// confirms ?DoXfer@GhostObject@@MAEXAAVXfer@@@Z (exact). The body is
// GeneralsMD GhostObject.cpp GhostObject::xfer: version 1, the parent object
// ID through the ObjectID hand-over helper 0x0010C3C0, the load-side
// TheGameLogic->findObjectByID relink, then the parent angle and position.
// BFME skips everything on a light-CRC pass and throws XferException(5, 0)
// (ThrowInfo VA 0x011DFE5C, variadic constructor 0x009D6220) where ZH throws
// SC_INVALID_DATA. Layout from the constructor: parent object at +0x0C,
// position at +0x10, angle at +0x1C.
// Shape: the visible GameLogic::findObjectByID (GameLogicObjectLookup.h)
// lets VC7.1 keep the ID in EBX across the lookup, and the block-scoped
// version record shares its frame slot with the throw temporary while the
// ID takes the dead xfer argument slot, as in retail.

#include "../../Common/System/xfer.h"

#define BFME_GAMELOGIC_LOOKUP_VISIBLE
#include "GameLogicObjectLookup.h"
#include "coord3d.h"

#include "../../../Include/Common/ScalarTypes.h"


enum { INVALID_ID = 0 };

class XferException
{
public:
	XferException(Int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	Int tag;
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

private:
	unsigned char m_beforeId[0x74];
	ObjectID m_id;
};

extern GameLogic *TheGameLogic;

class MidVirtualSlot90Receiver;
// 0x0010C3C0 (through ILT 0x0000C9B4): the cdecl ObjectID hand-over helper.
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *context);

class GhostObject
{
protected:
	virtual void DoXfer(Xfer &xfer);

private:
	unsigned char m_bases[8];
	Object *m_parentObject;
	Coord3DBase m_parentPosition;
	Real m_parentAngle;
};

struct XferVersion : public Xfer::Version
{
	XferVersion(unsigned char v)
	{
		data[0] = v;
		data[1] = v;
	}
};

// ?DoXfer@GhostObject@@MAEXAAVXfer@@@Z
void GhostObject::DoXfer(Xfer &xfer)
{
	if (xfer.IsLightCRC())
		return;

	{
		XferVersion version(1);
		xfer == version;
	}

	ObjectID parentObjectID = INVALID_ID;
	if (m_parentObject)
		parentObjectID = m_parentObject->getID();
	Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &parentObjectID);
	if (xfer.IsLoading())
	{
		m_parentObject = TheGameLogic->findObjectByID(parentObjectID);
		if (parentObjectID != INVALID_ID && m_parentObject == 0)
			throw XferException(5, 0);
	}

	xfer.xferReal(&m_parentAngle);
	xfer == m_parentPosition;
}
