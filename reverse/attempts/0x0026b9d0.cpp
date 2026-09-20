// ?after@TaintSpecialPower@@QAEXPBUCoord3D@@@Z
// partial score=0.15 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x0026B9D0, 1109B: TaintSpecialPower::after(const Coord3D *loc),
// identity documented in the caller TU
// TaintSpecialPowerDoSpecialPowerAtLocation.cpp (`taintSpecialPower(this)->
// after(loc)`, this=TaintSpecialPower*, one arg).
//
// Address-derived straight-line port from the disassembly (two prior
// sessions -- GPT-5 42min, claude-sonnet-5 20min -- blocked before reaching a
// compilable candidate; this session resolved the full callee inventory
// below and gets a first compile).
//
// Shape: builds a PartitionFilterAcceptByKindOf(mustBeSet, KINDOFMASK_NONE)
// and asks ThePartitionManager for a wide-range object iteration (through
// the generic bfmeForwardWideC ABI-adapter thunk -- BFME's common forwarder
// for several different underlying calls, so its true callee identity here
// is NOT independently proven), walks the returned iterator's raw node
// list, and for each candidate object whose controlling player matches the
// module's own object, inserts it into a local pointer-identity `_Rb_tree`
// (matching the already-proven insert_unique @0x0025BD30 / destructor
// @0x0025BC40 instantiation family in RvaTreeInsertUniqueIdentity.cpp),
// marks terrain dirty near it, and destroys it. A second, larger-radius pass
// repeats the filter+iterate+tree-insert dance, then applies a circular
// taint effect twice (small radius immediately per-candidate, large radius
// once at the end) via BfmeTaintManager::bfmeApplyCircleWorld, with an FX
// check (FXList::doFXPos) and object flag test (FXList::bfmeIsBlocked,
// named for an unrelated FXList culling predicate that ICF folds onto this
// body -- real identity here is unproven) gating the second pass's per-
// object work.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D
{
	float x, y, z;
};

class Object;

// Pointer-identity tree matching the already-matched insert_unique/destructor
// pair (RvaTreeInsertUniqueIdentity.cpp's Rva0025BD30Target instantiation).
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

struct Rva0025BD30Target;
typedef Rva0025BD30Target *Rva0025BD30Key;
typedef _STL::_Rb_tree<Rva0025BD30Key, Rva0025BD30Key,
	_STL::_Identity<Rva0025BD30Key>, _STL::less<Rva0025BD30Key>,
	_STL::allocator<Rva0025BD30Key> > PointerIdentityTree0025BD30;

struct BitFlags128
{
	unsigned int m_bits[4];
};

extern const BitFlags128 g_bfmeKindofMaskNone;	// ?KINDOFMASK_NONE@@3V?$BitFlags@$0HE@@@B

class PartitionFilterAcceptByKindOf
{
public:
	PartitionFilterAcceptByKindOf(const BitFlags128 &mustBeSet, const BitFlags128 &mustBeClear);

private:
	void *m_vftable;
	unsigned char m_pad[0x18];
};

// Opaque raw node the retail iterator walk chases directly (fields proven
// only by the offsets the disassembly reads: +0x04 next pointer bucket,
// +0x0c cursor). Not a real PartitionManager type -- address-derived shape.
struct Rva0026B9D0WideResult
{
	unsigned char m_pad[0x14];
};

class BfmeWideForwardC
{
public:
	Rva0026B9D0WideResult bfmeForwardWideC(Int a, Int b, Int c, Int d, Int e);
};

extern BfmeWideForwardC *ThePartitionManager;	// ?ThePartitionManager@@3PAVPartitionManager@@A

class Object
{
public:
	Object *getControllingPlayer();		// address-derived: ILT 0x00020824 -> 0x001BE3F0
};

class TerrainLogicP48
{
public:
	void adapter(Int a, Int b, Int c);	// ?adapter@TerrainLogicP48@@QAEXHHH@Z, ILT 0x00042cd0
};

extern TerrainLogicP48 *TheTerrainLogic;	// ?TheTerrainLogic@@3PAURva003FD060TerrainLogic@@A

class BfmeGameLogic
{
public:
	void destroyObject(Object *obj);	// ?destroyObject@GameLogic@@QAEXPAVObject@@@Z
};

extern BfmeGameLogic *TheBfmeGameLogic;	// ?TheBfmeGameLogic@@3PAURva00367E30Logic@@A

struct BfmePointFC
{
	unsigned char m_pad[0x14];
};

class BfmeTaintManager
{
public:
	void bfmeApplyCircleWorld(const BfmePointFC *pt, float radius, Int a, Bool b);
};

extern BfmeTaintManager *TheTaintManager;	// ?TheTaintManager@@3PAVBfmeTaintManager@@A

extern const float g_bfmeK1075340;		// ?g_bfmeK1266B@@3MB
extern const float g_bfme107faa8;

class TaintNameString;

struct TaintSpecialPowerModuleData
{
	unsigned char m_pad[0x210];
	void *m_name;
	float m_radius;			// +0x214
};

class TaintSpecialPower
{
public:
	void after(const Coord3D *loc);

	unsigned char m_pad00[4];
	TaintSpecialPowerModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
	unsigned char m_pad0C[4];
};

void TaintSpecialPower::after(const Coord3D *loc)
{
	TaintSpecialPowerModuleData *data = m_moduleData;
	float radius = data->m_radius;
	Object *owner = m_object;

	{
		BitFlags128 mustBeSet;
		mustBeSet.m_bits[0] = 0;
		mustBeSet.m_bits[1] = 0;
		mustBeSet.m_bits[2] = 0;
		mustBeSet.m_bits[3] = 0x800000;
		PartitionFilterAcceptByKindOf filter(mustBeSet, g_bfmeKindofMaskNone);

		float smallRadius = radius * (*(const float *)0x010B4BCC);
		Rva0026B9D0WideResult iter = ThePartitionManager->bfmeForwardWideC(
			(Int)loc, (Int)(smallRadius), 1, 0, 0);

		PointerIdentityTree0025BD30 matches;

		unsigned char *cursor = (unsigned char *)&iter;
		for (;;)
		{
			void **head = (void **)(cursor + 4);
			void **tail = (void **)(cursor + 0xc);
			if (*tail == *head)
				break;
			Object *candidate = *(Object **)(*(unsigned char **)tail);
			*tail = (unsigned char *)*tail + 8;
			if (!candidate)
				break;

			if (candidate->getControllingPlayer() == owner->getControllingPlayer())
			{
				matches.insert_unique((Rva0025BD30Key)candidate);
				TheTerrainLogic->adapter(0, 0, 0);
				TheBfmeGameLogic->destroyObject(candidate);
			}
		}
	}

	{
		BitFlags128 mustBeSet;
		mustBeSet.m_bits[0] = 0;
		mustBeSet.m_bits[1] = 0;
		mustBeSet.m_bits[2] = 0;
		mustBeSet.m_bits[3] = 0x800000;
		PartitionFilterAcceptByKindOf filter(mustBeSet, g_bfmeKindofMaskNone);

		float largeRadius = radius * g_bfmeK1075340;
		Rva0026B9D0WideResult iter = ThePartitionManager->bfmeForwardWideC(
			(Int)loc, (Int)(largeRadius), 4, 0, 0);

		PointerIdentityTree0025BD30 matches;

		unsigned char *cursor = (unsigned char *)&iter;
		for (;;)
		{
			void **head = (void **)(cursor + 4);
			void **tail = (void **)(cursor + 0xc);
			if (*tail == *head)
				break;
			Object *candidate = *(Object **)(*(unsigned char **)tail);
			*tail = (unsigned char *)*tail + 8;
			if (!candidate)
				break;

			if (candidate->getControllingPlayer() == owner->getControllingPlayer())
			{
				matches.insert_unique((Rva0025BD30Key)candidate);

				BfmePointFC pt;
				TheTaintManager->bfmeApplyCircleWorld(&pt, 1.0f, 1, false);
			}
		}
	}

	BfmePointFC bigPt;
	TheTaintManager->bfmeApplyCircleWorld(&bigPt, 1.0f, 1, false);
}
