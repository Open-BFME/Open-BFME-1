// ?d_007b4940@@YAXXZ (carved, no proven caller/original name)
// partial score=0.68 date=2026-09-21
//
// Retail identity: a BFMEShadowManagerLayout member (see
// Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp,
// which already declares this shim class with getTexture()/addShadowCore() and
// the `BFMEShadowManagerLayout *manager = (BFMEShadowManagerLayout *)this;`
// idiom used by the real addDecal()/addShadow() methods right above the
// insertion point used here, after W3DProjectedShadowManager::addShadow()).
// This candidate should be spliced into THAT file (it needs its real
// RenderObjClass/AABoxClass/W3DShadowTexture/BFMEShadowTypeInfo declarations,
// all already present there) -- it is written standalone below only for
// portability of the stash.
//
// Semantics (all confirmed against retail through +0x135 of 0x2ce, i.e. the
// entire size-validation/box-fallback prologue matches byte-for-byte,
// including branch targets):
//   - two BFMEShadowTypeInfo* "decal info" params (left/right) double as the
//     `const char *name` passed to getTexture (name is their first field);
//     each also carries sizeX/sizeY/offsetX/offsetY at +0x88/+0x8c/+0x90/+0x94
//     (exactly BFMEShadowTypeInfo's existing layout).
//   - if a RenderObjClass *robj is given and any of the four size fields
//     equals BfmeZeroRange, robj->Get_Obj_Space_Bounding_Box(box) backfills
//     just the zero ones with box.Extent.X/.Y doubled (fadd st,st, not *2.0f).
//   - getTexture(left) then getTexture(right); on failure release what was
//     already acquired and return NULL (Release_Ref, per WWLib/refcount.h's
//     "Release_Ref is NOT virtual in retail" note -- vtable slot 0 is
//     Delete_This).
//   - the pair object (0x68 bytes, ctor at retail 0x007B3B80, its
//     BfmeB1159::initialize at 0x007B44E0) is normally allocated fresh, BUT
//     retail first checks a manager+0x18 singly-linked FREE LIST (next link
//     at the pair object's own +0x64) and reuses+resets (bfmeGo1159()) a
//     popped entry when one exists -- this whole free-list branch was the
//     one piece missing from the first probe and, once added, closed the
//     718 vs 693-byte gap exactly.
//   - fields set: +0x34=flags (first stack arg), +0x60=robj; the two
//     BfmeB1159 sub-resources (+0x58/+0x5c, each an already-landed
//     Rva007AED00Entry-shaped struct) get their +0x68 texture pointer and
//     their +0x58/+0x5c offset floats (lx/ly, rx/ry); then
//     Rva007AED00Table::updateOffsets(0, left->offsetX, left->offsetY) and
//     (1, right->...) -- both already-landed callees, matches exactly.
//   - insertion into manager+0x14's list mirrors the already-landed
//     addDecal() texture-grouped insert: walk with prev/cur, break when
//     cur's two sub-resources' +0x68 textures equal (texture1, texture2),
//     insert before cur (or at head if prev is null), else prepend at head
//     when the list is exhausted.
//
// Residue (score 0.68, 231 non-reloc bytes differ, size matches exactly at
// 718): from +0x135 onward (right after the FIRST getTexture call) retail
// keeps texture1 in esi and spills `this` to a stack slot for the free-list
// reload, where every shape tried here instead keeps `this`/`manager` in esi
// and spills texture1. This is a pure MSVC 7.1 register-allocation choice --
// instruction-for-instruction the same operations happen in the same order,
// just mirrored between a register and a stack slot, cascading through the
// rest of the function once the two paths pick different residents for esi.
// Tried and REJECTED as no improvement (all still 718/231, or worse):
//   - explicit `BFMEShadowManagerLayout *manager = this;` receiver for every
//     call/field access instead of bare `this`/implicit member calls
//   - naming the free-list local `freeHead` vs. reusing `pairObj` directly
//   - a shared `goto done;` epilogue merging both early-NULL returns with a
//     `result` local (made it WORSE: 740/399, extra frame slot)
//   - collapsing the list-walk temporaries (t1/t2) into inline conditionals
// NEXT: a family/register shape_family_levers.py pass scoped to just this
// function (not the whole 3400-line host TU) might find the missing
// register-preference lever; otherwise this may be the SIB/register-mirror
// dead end WORKER_RULES calls out -- bank and let a fresh probe re-look.

typedef int Int;
typedef float Real;
typedef char Char;
typedef bool Bool;
typedef unsigned int UnsignedInt;
enum ShadowType { SHADOW_DYNAMIC_PROJECTION = 0x400, SHADOW_DIRECTIONAL_PROJECTION = 0x800 };

class Vector3 { public: Real X, Y, Z; };
class AABoxClass { public: Vector3 Center; Vector3 Extent; };

// Minimal reach to vtable slot 0x10c (offset 0x10c / 4 = 67th virtual);
// the real declaration already exists as RenderObjClass::Get_Obj_Space_Bounding_Box
// in Code/Libraries/Source/WWVegas/WW3D2/rendobj.h -- reuse that, not this stub,
// when splicing into W3DProjectedShadow.cpp.
class RenderObjClass { public: virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const; };

class RefCountedStub { public: void Release_Ref(void); };
typedef RefCountedStub W3DShadowTexture;

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
	Real m_offsetX;		//retail +0x58
	Real m_offsetY;		//retail +0x5c
	Char m_pad2[8];
	void *m_texture;	//retail +0x68
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

class BFMEShadowManagerLayout
{
public:
	W3DShadowTexture *getTexture(const Char *name);
	Rva007B3B80 *createShadowPairRva007B4940(
		Int flags,
		RenderObjClass *robj,
		BFMEShadowTypeInfo *left,
		BFMEShadowTypeInfo *right);
};

Rva007B3B80 *BFMEShadowManagerLayout::createShadowPairRva007B4940(
	Int flags,
	RenderObjClass *robj,
	BFMEShadowTypeInfo *left,
	BFMEShadowTypeInfo *right)
{
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

	BFMEShadowManagerLayout *manager = this;

	W3DShadowTexture *texture1 = manager->getTexture((const Char *)left);
	if (!texture1)
		return 0;

	W3DShadowTexture *texture2 = manager->getTexture((const Char *)right);
	if (!texture2)
	{
		texture1->Release_Ref();
		return 0;
	}

	Rva007B3B80 *pairObj;
	Rva007B3B80 *freeHead = *(Rva007B3B80 **)((Char *)manager + 0x18);
	if (freeHead)
	{
		*(Rva007B3B80 **)((Char *)manager + 0x18) = freeHead->m_next;
		pairObj = freeHead;
		((BfmeB1159 *)pairObj)->bfmeGo1159();
	}
	else
	{
		pairObj = new Rva007B3B80;
		if (!pairObj || !((BfmeB1159 *)pairObj)->initialize())
		{
			texture1->Release_Ref();
			texture2->Release_Ref();
			return 0;
		}
	}

	pairObj->m_flags = flags;
	pairObj->m_owner = robj;

	if (pairObj->m_first)
		pairObj->m_first->m_texture = texture1;
	if (pairObj->m_second)
		pairObj->m_second->m_texture = texture2;

	pairObj->m_first->m_offsetX = lx;
	pairObj->m_first->m_offsetY = ly;
	pairObj->m_second->m_offsetX = rx;
	pairObj->m_second->m_offsetY = ry;

	((Rva007AED00Table *)pairObj)->updateOffsets(0, left->offsetX, left->offsetY);
	((Rva007AED00Table *)pairObj)->updateOffsets(1, right->offsetX, right->offsetY);

	Rva007B3B80 *prev = 0;
	Rva007B3B80 *cur = *(Rva007B3B80 **)((Char *)manager + 0x14);

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
			*(Rva007B3B80 **)((Char *)manager + 0x14) = pairObj;
	}
	else
	{
		pairObj->m_next = *(Rva007B3B80 **)((Char *)manager + 0x14);
		*(Rva007B3B80 **)((Char *)manager + 0x14) = pairObj;
	}

	return pairObj;
}
