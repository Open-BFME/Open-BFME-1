// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// Retail 0x007B4940, 718 bytes. W3DProjectedShadowManager vtable 0x01128404
// slot 6 (+0x18) routes through ILT 0x0000FF65 to this body; nothing else
// reaches it. No caller, string or Zero Hour virtual names the slot, so the
// method keeps its address token.
//
// Takes two shadow-type records (their name is their first field, handed to
// the manager's texture lookup 0x007AFD10), backfills any size equal to
// BfmeZeroRange from the render object's box extent, acquires both textures,
// pops a pair object from the free list at +0x18 (reset by 0x007B02D0) or
// allocates a fresh 0x68-byte one (ctor 0x007B3B80, initialize 0x007B44E0),
// fills it, and links it into the list at +0x14 next to a pair that already
// uses the same two textures.

typedef int Int;
typedef float Real;
typedef char Char;
typedef bool Bool;
enum ShadowType { SHADOW_DYNAMIC_PROJECTION = 0x400, SHADOW_DIRECTIONAL_PROJECTION = 0x800 };

#include "vector3.h"
#include "aabox.h"
#include "refcount.h"

// Retail calls Get_Obj_Space_Bounding_Box through vtable slot +0x10C.
class RenderObjClass
{
public:
	virtual void renderObjSlot00(void) = 0;
	virtual void renderObjSlot04(void) = 0;
	virtual void renderObjSlot08(void) = 0;
	virtual void renderObjSlot0C(void) = 0;
	virtual void renderObjSlot10(void) = 0;
	virtual void renderObjSlot14(void) = 0;
	virtual void renderObjSlot18(void) = 0;
	virtual void renderObjSlot1C(void) = 0;
	virtual void renderObjSlot20(void) = 0;
	virtual void renderObjSlot24(void) = 0;
	virtual void renderObjSlot28(void) = 0;
	virtual void renderObjSlot2C(void) = 0;
	virtual void renderObjSlot30(void) = 0;
	virtual void renderObjSlot34(void) = 0;
	virtual void renderObjSlot38(void) = 0;
	virtual void renderObjSlot3C(void) = 0;
	virtual void renderObjSlot40(void) = 0;
	virtual void renderObjSlot44(void) = 0;
	virtual void renderObjSlot48(void) = 0;
	virtual void renderObjSlot4C(void) = 0;
	virtual void renderObjSlot50(void) = 0;
	virtual void renderObjSlot54(void) = 0;
	virtual void renderObjSlot58(void) = 0;
	virtual void renderObjSlot5C(void) = 0;
	virtual void renderObjSlot60(void) = 0;
	virtual void renderObjSlot64(void) = 0;
	virtual void renderObjSlot68(void) = 0;
	virtual void renderObjSlot6C(void) = 0;
	virtual void renderObjSlot70(void) = 0;
	virtual void renderObjSlot74(void) = 0;
	virtual void renderObjSlot78(void) = 0;
	virtual void renderObjSlot7C(void) = 0;
	virtual void renderObjSlot80(void) = 0;
	virtual void renderObjSlot84(void) = 0;
	virtual void renderObjSlot88(void) = 0;
	virtual void renderObjSlot8C(void) = 0;
	virtual void renderObjSlot90(void) = 0;
	virtual void renderObjSlot94(void) = 0;
	virtual void renderObjSlot98(void) = 0;
	virtual void renderObjSlot9C(void) = 0;
	virtual void renderObjSlotA0(void) = 0;
	virtual void renderObjSlotA4(void) = 0;
	virtual void renderObjSlotA8(void) = 0;
	virtual void renderObjSlotAC(void) = 0;
	virtual void renderObjSlotB0(void) = 0;
	virtual void renderObjSlotB4(void) = 0;
	virtual void renderObjSlotB8(void) = 0;
	virtual void renderObjSlotBC(void) = 0;
	virtual void renderObjSlotC0(void) = 0;
	virtual void renderObjSlotC4(void) = 0;
	virtual void renderObjSlotC8(void) = 0;
	virtual void renderObjSlotCC(void) = 0;
	virtual void renderObjSlotD0(void) = 0;
	virtual void renderObjSlotD4(void) = 0;
	virtual void renderObjSlotD8(void) = 0;
	virtual void renderObjSlotDC(void) = 0;
	virtual void renderObjSlotE0(void) = 0;
	virtual void renderObjSlotE4(void) = 0;
	virtual void renderObjSlotE8(void) = 0;
	virtual void renderObjSlotEC(void) = 0;
	virtual void renderObjSlotF0(void) = 0;
	virtual void renderObjSlotF4(void) = 0;
	virtual void renderObjSlotF8(void) = 0;
	virtual void renderObjSlotFC(void) = 0;
	virtual void renderObjSlot100(void) = 0;
	virtual void renderObjSlot104(void) = 0;
	virtual void renderObjSlot108(void) = 0;
	virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const = 0;
};

// Released with the inline RefCountClass::Release_Ref (Delete_This at slot 0).
class W3DShadowTexture : public RefCountClass
{
};

struct BFMEShadowTypeInfo
{
	Char name[128];
	ShadowType type;
	Bool allowUpdates;
	Bool allowWorldAlign;
	Char pad[2];
	Real sizeX;
	Real sizeY;
	Real offsetX;
	Real offsetY;
};

extern const Real BfmeZeroRange;

class BfmeB1159
{
public:
	Bool initialize(void);
	void bfmeGo1159(void);
};

class Rva007AED00Table
{
public:
	void updateOffsets(Int index, Real first, Real second);
};

struct Rva007B4940Sub
{
	Char m_pad[0x58];
	Real m_offsetX;					//retail +0x58
	Real m_offsetY;					//retail +0x5c
	Char m_pad2[8];
	W3DShadowTexture *m_texture;	//retail +0x68
};

class Rva007B3B80
{
public:
	Rva007B3B80() throw();

	Char m_pad00[0x34];
	Int m_flags;				//retail +0x34
	Char m_pad38[0x58 - 0x38];
	Rva007B4940Sub *m_first;	//retail +0x58
	Rva007B4940Sub *m_second;	//retail +0x5c
	void *m_owner;				//retail +0x60
	Rva007B3B80 *m_next;		//retail +0x64
};

// Layout view of the manager used by W3DProjectedShadow.cpp; owns the
// texture lookup pinned at ILT 0x0004088B.
class BFMEShadowManagerLayout
{
public:
	W3DShadowTexture *getTexture(const Char *name);
};

class W3DProjectedShadowManager
{
public:
	virtual ~W3DProjectedShadowManager();
	virtual Rva007B3B80 *createShadowPairRva007B4940(
		Int flags,
		RenderObjClass *robj,
		BFMEShadowTypeInfo *left,
		BFMEShadowTypeInfo *right);
};

Rva007B3B80 *W3DProjectedShadowManager::createShadowPairRva007B4940(
	Int flags,
	RenderObjClass *robj,
	BFMEShadowTypeInfo *left,
	BFMEShadowTypeInfo *right)
{
	BFMEShadowManagerLayout *manager = (BFMEShadowManagerLayout *)this;

	if (!left || !right)
		return 0;

	Real lx = left->sizeX;
	Real ly = left->sizeY;
	Real rx = right->sizeX;
	Real ry = right->sizeY;

	if (robj)
	{
		if (lx == BfmeZeroRange || ly == BfmeZeroRange || rx == BfmeZeroRange || ry == BfmeZeroRange)
		{
			AABoxClass box;
			robj->Get_Obj_Space_Bounding_Box(box);

			if (lx == BfmeZeroRange)
				lx = box.Extent.X + box.Extent.X;
			if (ly == BfmeZeroRange)
				ly = box.Extent.Y + box.Extent.Y;
			if (rx == BfmeZeroRange)
				rx = box.Extent.X + box.Extent.X;
			if (ry == BfmeZeroRange)
				ry = box.Extent.Y + box.Extent.Y;
		}
	}

	W3DShadowTexture *texture1 = manager->getTexture((const Char *)left);
	if (!texture1)
		return 0;

	W3DShadowTexture *texture2 = manager->getTexture((const Char *)right);
	if (!texture2)
	{
		texture1->Release_Ref();
		return 0;
	}

	Rva007B3B80 *pairObj = *(Rva007B3B80 **)((Char *)this + 0x18);
	if (pairObj)
	{
		*(Rva007B3B80 **)((Char *)this + 0x18) = pairObj->m_next;
		((BfmeB1159 *)pairObj)->bfmeGo1159();
	}
	else
	{
		Rva007B3B80 *created = new Rva007B3B80;
		pairObj = created;
		if (!created || !((BfmeB1159 *)created)->initialize())
		{
			texture1->Release_Ref();
			texture2->Release_Ref();
			return 0;
		}
	}

	pairObj->m_flags = flags;
	void *&owner = pairObj->m_owner;
	owner = robj;

	if (pairObj->m_first)
		pairObj->m_first->m_texture = texture1;
	if (pairObj->m_second)
		pairObj->m_second->m_texture = texture2;

	Rva007B4940Sub *first = pairObj->m_first;
	first->m_offsetX = lx;
	first->m_offsetY = ly;
	Rva007B4940Sub *second = pairObj->m_second;
	second->m_offsetX = rx;
	second->m_offsetY = ry;

	((Rva007AED00Table *)pairObj)->updateOffsets(0, left->offsetX, left->offsetY);
	((Rva007AED00Table *)pairObj)->updateOffsets(1, right->offsetX, right->offsetY);

	Rva007B3B80 *prev = 0;
	Rva007B3B80 *cur = *(Rva007B3B80 **)((Char *)this + 0x14);

	for (; cur; prev = cur, cur = cur->m_next)
	{
		if ((cur->m_first ? cur->m_first->m_texture : 0) != texture1)
			continue;
		if ((cur->m_second ? cur->m_second->m_texture : 0) != texture2)
			continue;
		break;
	}

	if (cur)
	{
		pairObj->m_next = cur;
		if (prev)
			prev->m_next = pairObj;
		else
			*(Rva007B3B80 **)((Char *)this + 0x14) = pairObj;
	}
	else
	{
		pairObj->m_next = *(Rva007B3B80 **)((Char *)this + 0x14);
		*(Rva007B3B80 **)((Char *)this + 0x14) = pairObj;
	}

	return pairObj;
}
