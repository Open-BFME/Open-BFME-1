// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep
//
// Retail 0x007B3E70, 460 bytes (RET 0x34 at +0x1C9, int3 after). The matched
// W3DProjectedShadowManager::addDecal (0x007B4340, W3DProjectedShadow.cpp)
// reaches it through ILT 0x000193BC with the manager as `this` and thirteen
// arguments; nothing else calls it. No caller, string or Zero Hour method
// names it, so it keeps its address token.
//
// Pops a projected shadow from the manager's free list at +0x10 (reset in
// place with the same steps as its ctor 0x007B3C70: 0x007AF200, the
// +0x58..+0x64 defaults and 0x007AEB70) or allocates a fresh 0xD8-byte one, fills it from the
// arguments, links it into the caller's list next to a shadow that already
// uses the same texture and drawable, and counts decal-like types at +0x250.

typedef int Int;
typedef float Real;
typedef char Char;
typedef bool Bool;

#include "refcount.h"

class W3DShadowTexture;
class Drawable;

extern const Real g_rva01075350;

class BfmeB1050 { public: void bfmeBase1050(); };
class Rva007AEB70State { public: void initializeFields(); };

class BfmeThingSE
{
public:
	BfmeThingSE() throw();

	Char m_pad00[0x34];
	Int m_type;						//retail +0x34
	Char m_pad38[0x58 - 0x38];
	Real m_58;						//retail +0x58
	Real m_5c;						//retail +0x5c
	Real m_60;						//retail +0x60
	Bool m_64;						//retail +0x64
	Char m_pad65[3];
	W3DShadowTexture *m_texture;	//retail +0x68
	Drawable *m_drawable;			//retail +0x6c
	RefCountClass *m_robj;			//retail +0x70
	Bool m_allowWorldAlign;			//retail +0x74
	Char m_pad75[3];
	Real m_78;						//retail +0x78
	Real m_7c;						//retail +0x7c
	Int m_80;						//retail +0x80
	Bool m_84;						//retail +0x84
	Bool m_85;						//retail +0x85
	Char m_pad86[0xd4 - 0x86];
	BfmeThingSE *m_next;			//retail +0xd4
};

class W3DProjectedShadowManager
{
public:
	BfmeThingSE *rva007B3E70(
		W3DShadowTexture *texture,
		RefCountClass *robj,
		Int type,
		Bool allowWorldAlign,
		Real sizeX,
		Real sizeY,
		Real value60,
		Real numeratorX,
		Real numeratorY,
		BfmeThingSE **list,
		Bool flag84,
		Drawable *drawable,
		Bool flag85);

	Char m_pad00[0x10];
	BfmeThingSE *m_freeList;		//retail +0x10
	Char m_pad14[0x250 - 0x14];
	Int m_count;					//retail +0x250
};

BfmeThingSE *W3DProjectedShadowManager::rva007B3E70(
	W3DShadowTexture *texture,
	RefCountClass *robj,
	Int type,
	Bool allowWorldAlign,
	Real sizeX,
	Real sizeY,
	Real value60,
	Real numeratorX,
	Real numeratorY,
	BfmeThingSE **list,
	Bool flag84,
	Drawable *drawable,
	Bool flag85)
{
	if (!texture)
		return 0;

	if (flag85 && !drawable)
		return 0;

	BfmeThingSE *shadow = m_freeList;
	if (shadow)
	{
		m_freeList = shadow->m_next;
		reinterpret_cast<BfmeB1050 *>(shadow)->bfmeBase1050();
		shadow->m_58 = 0;
		shadow->m_5c = 0;
		shadow->m_60 = 20.0f;
		shadow->m_64 = 0;
		reinterpret_cast<Rva007AEB70State *>(shadow)->initializeFields();
	}
	else
	{
		BfmeThingSE *created = new BfmeThingSE;
		shadow = created;
	}

	if (!shadow)
		return 0;

	if (flag84)
		shadow->m_84 = 1;
	else if (flag85)
		shadow->m_85 = 1;

	RefCountClass *&slot = shadow->m_robj;
	REF_PTR_SET(slot, robj);
	shadow->m_texture = texture;
	Drawable *&dslot = shadow->m_drawable;
	dslot = drawable;
	shadow->m_80 = 0;
	shadow->m_type = type;
	shadow->m_allowWorldAlign = allowWorldAlign;
	shadow->m_58 = sizeX;
	shadow->m_5c = sizeY;
	shadow->m_60 = value60;

	if (sizeX == 0.0f)
		shadow->m_78 = 0;
	else
		shadow->m_78 = numeratorX / sizeX;

	if (sizeY == 0.0f)
		shadow->m_7c = 0;
	else
		shadow->m_7c = numeratorY / sizeY;

	BfmeThingSE *prev = 0;
	BfmeThingSE *cur = *list;
	for (; cur; prev = cur, cur = cur->m_next)
	{
		if (cur->m_texture == texture && cur->m_drawable == drawable)
			break;
	}

	if (cur)
	{
		shadow->m_next = cur;
		if (prev)
			prev->m_next = shadow;
		else
			*list = shadow;
	}
	else
	{
		shadow->m_next = *list;
		*list = shadow;
	}

	switch (shadow->m_type)
	{
	case 0x1:
	case 0x20:
	case 0x40:
	case 0x400:
	case 0x800:
	case 0x1000:
		m_count++;
		break;
	}

	return shadow;
}
