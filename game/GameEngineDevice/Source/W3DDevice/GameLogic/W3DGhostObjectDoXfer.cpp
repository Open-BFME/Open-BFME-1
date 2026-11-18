// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
//
// W3DGhostObject::DoXfer (ZH W3DGhostObject::xfer), retail RVA 0x006BD6E0,
// 840 bytes: the RET 4 at +0x305, then the two cold throw tails, the last
// ending with the noreturn _CxxThrowException call at +0x343 (INT3 padding
// follows).
// Identity: the W3DGhostObject vftable 0x0111CFB8 reaches this body from
// slot 3 (the BFME Snapshot DoXfer slot) through ILT 0x000268D7, and
// tools/ilt_oracle.py CONFIRMS ?DoXfer@W3DGhostObject@@MAEXAAVXfer@@@Z here
// (p_false 5.22e-04, exact). The ZH ?xfer@...@@MAEXPAVXfer@@@Z spelling and
// ?DoXfer@W3DGhostObjectManager@@... are contradicted at this address.
//
// Body: the GhostObject base transfer (0x001B3B70, ILT 0x0003C1CD), the light
// CRC early out, version 1, the DrawableInfo object ID, flags and drawable ID,
// then per player index the snapshot count, name/scale/colour and snapshot of
// each render object (save) or the rebuilt W3DRenderObjectSnapshot list added
// to W3DDisplay::m_3DScene (load), and finally removeParentObject for a loaded
// ghost the local player sees. BFME dropped ZH's trailing shroudedness block,
// creates the render object with the free Create_Render_Obj, and throws
// XferException(4, 0) (ThrowInfo VA 0x011DFE5C) on a stale list head or a
// failed render object.
//
// Frame: retail shares one slot for both XferException temporaries and the
// `new` cleanup pointer. VC7.1 gives that layout when the stale-head throw is
// the else arm of the loop body's guard; a separate `if (...) throw` ahead of
// the name string kept the two exception temporaries apart and grew the frame
// from 0x28 to 0x2C bytes.

#include <string.h>

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"



#include "ascii_string.h"
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

// The RTTI-proven eight-byte exception (variadic ctor 0x009D6220, copy ctor
// 0x00065C50, dtor 0x00065C70), as TeamFactory_xfer.cpp declares it.
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

#include "../../../../GameEngine/Include/Common/DrawableID.h"





// The ObjectID (0x0010C3C0, ILT 0x0000C9B4) and DrawableID (0x0010C3E0, ILT
// 0x00008CA1) transfers by their ledger names, with their cdecl ABI
// (MidVirtualSlot90Forwarders.cpp).
class MidVirtualSlot90Receiver;
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *context);
void Rva0010C3E0(MidVirtualSlot90Receiver *receiver, void *context);

class Drawable
{
public:
	DrawableID getID() const;
};

class GameClient
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28();
	virtual Drawable *findDrawableByID(DrawableID id);	// +0x2c
};

extern GameClient *TheGameClient;

struct DrawableInfo
{
	UnsignedInt m_shroudStatusObjectID;	// +0x00
	Drawable *m_drawable;				// +0x04
	void *m_ghostObject;				// +0x08
	int m_flags;						// +0x0c
};

class RenderObjClass
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual const char *Get_Name() const;	// +0x18
#define RENDER_PAD(n) virtual void slot##n();
	RENDER_PAD(1C) RENDER_PAD(20) RENDER_PAD(24) RENDER_PAD(28) RENDER_PAD(2C)
	RENDER_PAD(30) RENDER_PAD(34) RENDER_PAD(38) RENDER_PAD(3C) RENDER_PAD(40)
	RENDER_PAD(44) RENDER_PAD(48) RENDER_PAD(4C) RENDER_PAD(50) RENDER_PAD(54)
	RENDER_PAD(58) RENDER_PAD(5C) RENDER_PAD(60) RENDER_PAD(64) RENDER_PAD(68)
	RENDER_PAD(6C) RENDER_PAD(70) RENDER_PAD(74) RENDER_PAD(78) RENDER_PAD(7C)
	RENDER_PAD(80) RENDER_PAD(84) RENDER_PAD(88) RENDER_PAD(8C) RENDER_PAD(90)
	RENDER_PAD(94) RENDER_PAD(98) RENDER_PAD(9C) RENDER_PAD(A0) RENDER_PAD(A4)
	RENDER_PAD(A8) RENDER_PAD(AC) RENDER_PAD(B0) RENDER_PAD(B4) RENDER_PAD(B8)
	RENDER_PAD(BC) RENDER_PAD(C0) RENDER_PAD(C4) RENDER_PAD(C8) RENDER_PAD(CC)
	RENDER_PAD(D0) RENDER_PAD(D4) RENDER_PAD(D8) RENDER_PAD(DC) RENDER_PAD(E0)
	RENDER_PAD(E4) RENDER_PAD(E8) RENDER_PAD(EC) RENDER_PAD(F0) RENDER_PAD(F4)
	RENDER_PAD(F8) RENDER_PAD(FC) RENDER_PAD(100) RENDER_PAD(104) RENDER_PAD(108)
	RENDER_PAD(10C) RENDER_PAD(110) RENDER_PAD(114) RENDER_PAD(118) RENDER_PAD(11C)
	RENDER_PAD(120) RENDER_PAD(124) RENDER_PAD(128) RENDER_PAD(12C) RENDER_PAD(130)
	RENDER_PAD(134) RENDER_PAD(138) RENDER_PAD(13C) RENDER_PAD(140) RENDER_PAD(144)
	RENDER_PAD(148) RENDER_PAD(14C) RENDER_PAD(150)
#undef RENDER_PAD
	virtual void Set_User_Data(void *data, bool recursive);	// +0x154

	Real Get_ObjectScale() const { return m_objectScale; }
	UnsignedInt Get_ObjectColor() const { return m_objectColor; }

	char m_pad04[0x44];
	Real m_objectScale;				// +0x48
	UnsignedInt m_objectColor;		// +0x4c
};

RenderObjClass *Create_Render_Obj(const char *name, float scale, int color);
void disableUVAnimations(RenderObjClass *renderObj);

// Retail inlines the constructor: vftable 0x0111D024, m_next, m_robj, then
// Set_User_Data through slot +0x154.
class W3DRenderObjectSnapshot : public Snapshot
{
public:
	W3DRenderObjectSnapshot(RenderObjClass *robj, DrawableInfo *drawInfo, bool cloneParentRobj)
	{
		m_next = 0;
		m_robj = robj;
		robj->Set_User_Data(drawInfo, cloneParentRobj);
	}

	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

	RenderObjClass *m_robj;				// +0x04
	W3DRenderObjectSnapshot *m_next;	// +0x08
};

class SceneClass
{
public:
	virtual ~SceneClass();
	virtual void Delete_This();
	virtual void Add_Render_Object(RenderObjClass *obj);	// +0x08
};

class RTS3DScene : public SceneClass
{
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }

	char m_pad00[0x24];
	int m_playerIndex;				// +0x24
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }

	char m_pad00[0x0c];
	Player *m_local;				// +0x0c
};

extern PlayerList *ThePlayerList;

class Object;

// Layout as in W3DGhostObjectAdd.cpp: the secondary base's vptr at +4 and the
// vbptr at +8 ahead of m_parentObject, 0x80 bytes in all.
class GhostObject : public Snapshot
{
protected:
	virtual void DoXfer(Xfer &xfer);

	char m_secondaryBase[8];		// +0x04
	Object *m_parentObject;			// +0x0c
	char m_pad10[0x70];
};

class W3DGhostObject : public GhostObject
{
protected:
	virtual void DoXfer(Xfer &xfer);
	void removeParentObject();

	W3DRenderObjectSnapshot *m_parentSnapshots[32];	// +0x80
	DrawableInfo m_drawableInfo;					// +0x100
};

// AsciiString::set(const char *) as retail inlines it here: strlen in line,
// then StringBase<char>::set(const char *, int).
static inline void setName(AsciiString &name, const char *s)
{
	name.StringBase<char>::set(s, s ? strlen(s) : 0);
}

// ?DoXfer@W3DGhostObject@@MAEXAAVXfer@@@Z
void W3DGhostObject::DoXfer(Xfer &xfer)
{
	GhostObject::DoXfer(xfer);

	if (xfer.IsLightCRC())
		return;

	{
		XferVersion version(1);
		xfer == version;
	}

	Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &m_drawableInfo.m_shroudStatusObjectID);
	xfer == m_drawableInfo.m_flags;

	DrawableID drawableID = m_drawableInfo.m_drawable ? m_drawableInfo.m_drawable->getID() : INVALID_DRAWABLE_ID;
	Rva0010C3E0((MidVirtualSlot90Receiver *)&xfer, &drawableID);
	if (xfer.IsLoading())
		m_drawableInfo.m_drawable = TheGameClient->findDrawableByID(drawableID);

	UnsignedByte snapshotCount;
	for (int i = 0; i < 32; ++i)
	{
		snapshotCount = 0;
		W3DRenderObjectSnapshot *objectSnapshot = m_parentSnapshots[i];
		while (objectSnapshot)
		{
			snapshotCount++;
			objectSnapshot = objectSnapshot->m_next;
		}

		xfer == snapshotCount;

		// a loaded count of zero must not meet an already allocated list
		if (snapshotCount != 0 || m_parentSnapshots[i] == 0)
		{
			Real scale;
			UnsignedInt color;
			AsciiString name;
			if (xfer.IsStoring())
			{
				objectSnapshot = m_parentSnapshots[i];
				while (objectSnapshot)
				{
					setName(name, objectSnapshot->m_robj->Get_Name());
					xfer == name;
					scale = objectSnapshot->m_robj->Get_ObjectScale();
					xfer == scale;
					color = objectSnapshot->m_robj->Get_ObjectColor();
					xfer == color;
					xfer == *objectSnapshot;
					objectSnapshot = objectSnapshot->m_next;
				}
			}
			else
			{
				RenderObjClass *renderObject;
				W3DRenderObjectSnapshot *prevObjectSnapshot = 0;
				for (UnsignedByte j = 0; j < snapshotCount; ++j)
				{
					xfer == name;
					xfer == scale;
					xfer == color;
					renderObject = Create_Render_Obj(name.str(), scale, color);
					if (renderObject == 0)
						throw XferException(4, 0);
					disableUVAnimations(renderObject);
					objectSnapshot = new W3DRenderObjectSnapshot(renderObject, &m_drawableInfo, false);
					if (prevObjectSnapshot)
						prevObjectSnapshot->m_next = objectSnapshot;
					else
						m_parentSnapshots[i] = objectSnapshot;
					prevObjectSnapshot = objectSnapshot;
					xfer == *objectSnapshot;
					W3DDisplay::m_3DScene->Add_Render_Object(objectSnapshot->m_robj);
				}
			}
		}
		else
			throw XferException(4, 0);
	}

	if (m_parentObject &&
		m_parentSnapshots[ThePlayerList->getLocalPlayer()->getPlayerIndex()] != 0 &&
		xfer.IsLoading())
		removeParentObject();
}
