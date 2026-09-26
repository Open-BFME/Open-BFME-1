// ?bfmeAllocateCells@PathfindLayer@@QAEXPBUIRegion2D@@@Z
// cl: /O2 /DNDEBUG /MD /EHsc
// BFME PathfindLayer::allocateCells (retail 0x003FBED0, 767 bytes).
//
// Identity: the Zero Hour twin PathfindLayer::allocateCells
// (inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp:3371)
// reproduces this body statement for statement.  BFME added a fallback: with no
// m_bridge, the bounding box is unioned over the chain hanging off +0x3C through
// the same getBounds slot.
//
// +0x3C IS A Bridge*, AND SO IS ITS CHAIN.  The landed sibling
// game/GameEngine/Source/GameLogic/AI/PathfindLayer_bfmeContainsRegion.cpp:34-50
// (retail 0x003FBA10) types the same member `Bridge *m_bfmeOther` at the same
// +0x3C, calls the same getBounds on it, and walks the same `+4` link.  This TU
// used to call it a PolygonTrigger and cast to Bridge* at every call; there was
// never evidence for PolygonTrigger, so the claim is gone and the member now
// carries the sibling's spelling.
//
// Bridge::getBounds -- WHAT IS PROVEN AND WHAT IS NOT.  Upstream Bridge lives in
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h:203
// (there is no .../Include/Terrain/Bridge.h; an earlier revision of this comment
// cited that path and it does not exist), and this repo's own
// game/GameEngine/Include/GameLogic/TerrainLogic.h:207 declares the same thing:
//
//     const Region2D *getBounds(void) const {return &m_bounds;}
//
// That returns a pointer and takes nothing.  Retail here instead passes the
// address of a stack region and gets it filled, so the BFME signature is an
// out-parameter form and genuinely differs from ZH -- which is why that header is
// NOT included and the declaration below is TU-local.  The call resolves through
// the PRE-EXISTING pin
//
//     targets/game/reverse/symbols.csv  ?getBounds@Bridge@@QBEXPAURegion2D@@@Z,0x0000FEE8
//
// which predates this TU (it is the pin the sibling at 0x003FBA10 already links
// against).  0x0000FEE8 is an ILT stub; its body is 0x0018F830, and the
// targets/game/reverse/functions.csv row owning 0x0018F830 names it
// ?bfmeGoCMB@BfmeThingCMB@@QAEXPAUBfmeVec4CMB@@@Z -- an unrelated ICF-folded
// name.  So the identity "Bridge::getBounds" rests on the ZH twin and on the
// sibling's use of the same slot, NOT on any symbolic witness in the image, and
// the pin's mangled spelling is our own convention rather than a recovered
// string.  Two consequences: the parameter type must keep the name `Region2D`
// for the mangling to reach that pin, and the buffer retail actually fills is
// int-shaped (the `fild` conversions below, and the sibling, both witness ints),
// so the int buffer is handed over through one cast.  The byte gate cannot see
// either fact.
//
// THE CELL-SIZE CONSTANT.  Retail reads the subtrahend and the multiplier from
// ONE address, 0x01075C70, which lives in .rdata and holds cd cc cc 3d == 0.1f.
// Two facts, both true, neither one asserted over the other: the operand is
// shaped exactly like MSVC's pooled `__real@3dcccccd` for the two constants ZH
// spells as PATHFIND_CELL_SIZE_F/100 and 1/PATHFIND_CELL_SIZE_F (equal only
// because the cell size is 10), AND targets/game/reverse/symbols.csv separately names that
// same address g_bfmeScaleBK ("the scale the difference at 0x001B48B0 multiplies
// by").  What is measured is only the pooling behaviour: spelling it as an
// opaque `extern float` hides the value from the optimiser, which then cannot
// put it on the right of `fadd`, and the four floor/ceil expressions come out
// with their operands commuted (`fld const; fadd var` for retail's `fld var;
// fadd const`).  That single wrong spelling was the whole 40-byte residue that
// twelve earlier passes read as x87 scheduling.  Whether the address is also a
// real named global that happens to hold 0.1f is not settled here.
//
// ZH uses the INT macro here (PATHFIND_CELL_SIZE == 10), so its `/100` term is
// integer division and subtracts nothing; BFME uses the float macro, which is
// why retail really does subtract 0.1f.  AIPathfind.h:439-440 defines both.

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" __declspec(dllimport) double __cdecl ceil(double);

// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h:440
#define PATHFIND_CELL_SIZE_F 10.0f

// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h:271,307,314,322
struct Coord2D { Real x, y; };
struct ICoord2D { Int x, y; };

struct Region2D { Coord2D lo, hi; };
struct IRegion2D { ICoord2D lo, hi; };

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h:203
// (and this repo's game/GameEngine/Include/GameLogic/TerrainLogic.h:207), which
// declares `Bridge *getNext(void)` over a `Bridge *m_next` first data member and
// a POINTER-RETURNING `const Region2D *getBounds(void) const`.  BFME's getBounds
// is the out-parameter form instead, so this stays TU-local; see the header
// comment.  m_next at +4 is witnessed by the landed sibling
// PathfindLayer_bfmeContainsRegion.cpp:50, which walks the same chain.
class Bridge
{
public:
	// pin: targets/game/reverse/symbols.csv ?getBounds@Bridge@@QBEXPAURegion2D@@@Z -> ILT 0x0000FEE8
	void getBounds(Region2D *bounds) const;
	Bridge *getNext(void) const { return m_next; }
private:
	char m_bfmeHead[4];
	Bridge *m_next;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
// The ZH twin allocates PathfindCell[] and PathfindCellP[] here (AIPathfind.cpp:3399-3400),
// and that twin is the ONLY evidence for the name PathfindCell.  The two ??_L
// operands below are DIR32 relocation slots, which the byte gate masks and
// therefore cannot check: retail's +0x291 ctor operand is ILT 0x000211D9 ->
// 0x003F7350, a body targets/game/reverse/functions.csv owns as ??0Rva003F7350@@QAE@XZ, and
// the +0x28C dtor operand is ILT 0x00036AB1 -> 0x003F6EA0, owned as
// ??1FileInfoStruct@MixFileCreator@@QAE@XZ via ICF.  The ledger names those two
// addresses differently from the names spelled here; the ZH twin is the reason
// to keep PathfindCell anyway, and it is unverified by the gate.
class PathfindCell
{
public:
	PathfindCell();
	~PathfindCell();
private:
	unsigned char m_opaque[0x10];
};
typedef PathfindCell *PathfindCellP;

// Forward-declaring the array overload (as the sibling PathfindZoneManagerConstructor.cpp
// does) keeps the compiler from folding `new T[n]` into a call to scalar operator new;
// retail links both `new[]` expressions below to ??_U@YAPAXI@Z (mem_ops.cpp), not ??2@YAPAXI@Z.
void *operator new[](unsigned int size);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
// Witnessed prefix, then padded to the real stride: the verified caller
// 0x003F9310 strides an array of these by 0x44 (`add edi,0x44` at +0x0D1 and
// +0x0EC; `imul r,r,0x44` at +0x0FF, +0x112 and +0x146) and reads a field at
// +0x40 as an Int (`mov ecx,[edi+0x40]; fild` at +0x0B2).  This TU
// never touches +0x40, so it is carried under its offset rather than a guessed
// name, purely so sizeof(PathfindLayer) is the witnessed 0x44.
class PathfindLayer
{
public:
	void bfmeAllocateCells(const IRegion2D *extent);

private:
	PathfindCell *m_blockOfMapCells;
	PathfindCellP *m_layerCells;
	Int m_width;
	Int m_height;
	Int m_xOrigin;
	Int m_yOrigin;
	unsigned char m_middle[0x38 - 0x18];
	Bridge *m_bridge;
	Bridge *m_bfmeOther;
	Int m_bfme40;
};

// ?bfmeAllocateCells@PathfindLayer@@QAEXPBUIRegion2D@@@Z
void PathfindLayer::bfmeAllocateCells(const IRegion2D *extent)
{
	if (m_blockOfMapCells != 0)
		return;

	Region2D bridgeBounds;
	if (m_bridge != 0) {
		bridgeBounds = *(Region2D *)((char *)m_bridge + 0x78);
	} else if (m_bfmeOther != 0) {
		// The pin's mangled name fixes the parameter TYPE NAME (Region2D); the
		// buffer retail fills is int-shaped, which is why the members arrive as
		// ints and `fild` converts them.  See the header comment.
		IRegion2D rawBounds;
		m_bfmeOther->getBounds((Region2D *)&rawBounds);
		bridgeBounds.lo.x = (Real)rawBounds.lo.x;
		bridgeBounds.hi.x = (Real)rawBounds.hi.x;
		bridgeBounds.lo.y = (Real)rawBounds.lo.y;
		bridgeBounds.hi.y = (Real)rawBounds.hi.y;
		Bridge *other = m_bfmeOther->getNext();
		if (other != 0) {
			Real cand;
			do {
				other->getBounds((Region2D *)&rawBounds);
				cand = (Real)rawBounds.lo.x;
				bridgeBounds.lo.x = *(bridgeBounds.lo.x < cand ? &bridgeBounds.lo.x : &cand);
				cand = (Real)rawBounds.hi.x;
				bridgeBounds.hi.x = *(bridgeBounds.hi.x > cand ? &bridgeBounds.hi.x : &cand);
				cand = (Real)rawBounds.lo.y;
				bridgeBounds.lo.y = *(bridgeBounds.lo.y < cand ? &bridgeBounds.lo.y : &cand);
				cand = (Real)rawBounds.hi.y;
				bridgeBounds.hi.y = *(bridgeBounds.hi.y > cand ? &bridgeBounds.hi.y : &cand);
				other = other->getNext();
			} while (other != 0);
		}
	} else {
		return;
	}

	Int maxX, maxY;
	m_xOrigin = fast_float2long_round((float)floor((double)((bridgeBounds.lo.x - PATHFIND_CELL_SIZE_F/100) / PATHFIND_CELL_SIZE_F)));
	m_yOrigin = fast_float2long_round((float)floor((double)((bridgeBounds.lo.y - PATHFIND_CELL_SIZE_F/100) / PATHFIND_CELL_SIZE_F)));
	m_width = 0;
	m_height = 0;
	maxX = fast_float2long_round((float)ceil((double)((bridgeBounds.hi.x + PATHFIND_CELL_SIZE_F/100) / PATHFIND_CELL_SIZE_F)));
	maxY = fast_float2long_round((float)ceil((double)((bridgeBounds.hi.y + PATHFIND_CELL_SIZE_F/100) / PATHFIND_CELL_SIZE_F)));

	// Pad with 1 extra.
	m_xOrigin--;
	m_yOrigin--;
	maxX++;
	maxY++;

	if (m_xOrigin < extent->lo.x) m_xOrigin = extent->lo.x;
	if (m_yOrigin < extent->lo.y) m_yOrigin = extent->lo.y;
	if (maxX > extent->hi.x) maxX = extent->hi.x;
	if (maxY > extent->hi.y) maxY = extent->hi.y;
	if (maxX <= m_xOrigin) return;
	if (maxY <= m_yOrigin) return;
	m_width = maxX - m_xOrigin;
	m_height = maxY - m_yOrigin;

	m_blockOfMapCells = new PathfindCell[m_width * m_height];
	m_layerCells = new PathfindCellP[m_width];
	for (Int i = 0; i < m_width; i++)
		m_layerCells[i] = &m_blockOfMapCells[i * m_height];
}
