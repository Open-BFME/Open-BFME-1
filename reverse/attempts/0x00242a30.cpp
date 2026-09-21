// ?d_00242a30@@YAXXZ
// partial score=0.24 date=2026-09-21
// ?d_00242a30@@YAXXZ
// partial score~0.24 date=2026-09-21
// Retail 0x00242A30: HordeContain member formation-position lookup.
// Same class as the already-landed
// Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainMemberNameMatches.cpp
// (retail 0x00242630): the member's id at Object+0x74 goes through the same
// index map at this+0x120 (BfmeSubDSU::bfmeTwoDSU, pinned at 0x0001F91F),
// and the result indexes the same sixteen-byte roster slot table whose
// begin/end pointers sit at this+0x12c/this+0x130 (used here only for a
// bounds check via (end-begin)>>4). A SEPARATE, wider (0x1c-byte) formation
// slot table lives at this+0x1d8, parallel-indexed by the same id; a ready
// flag sits at this+0x1fc. member+0x38 is treated as the member's own
// current Coord3D position (address-derived -- no ZH/BFME field name
// proven from this body alone).
//
// Three exits: (a) id out of bounds -> member's own position, unchanged;
// (b) this+0x1fc set AND the formation slot not itself busy -> the
// formation slot's stored Coord3D, verbatim; (c) otherwise, a per-axis
// blend of a helper's result (thunk at 0x00019736, still a dump) with the
// member's own position, whose exact FPU scheduling (which axis gets which
// source) is transcribed straight-line from the disassembly, not derived
// from any named formation-offset concept.
//
// Identity and the two data structures are solid (confirmed against the
// landed sibling's field offsets and the bfmeTwoDSU pin), but the codegen
// shape is not: ours compiles to 221B against retail's 273B (208 non-reloc
// bytes differ) -- retail keeps a live `edi = (char*)member + 0x38` pointer
// across the whole function and copies the member's x/y/z fallback through
// mixed float/raw-int stores (x via fld/fstp, y/z via plain mov) that this
// attempt only partially reproduces; the bounds check (signed <0, then
// unsigned > count) and the final three-way axis blend both still diverge
// structurally, not just by register choice. A future attempt should start
// from a persistent byte-pointer local for member+0x38 and try matching
// retail's asymmetric x-vs-y/z store instruction selection lever by lever
// (docs/shape_levers.md's SIB/copy family) rather than reworking the whole
// body again from scratch.

typedef float Real;
typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_bfmeHead[0x38];
	Coord3D m_bfmePosition;					///< retail this+0x38 (address-derived)
	char m_bfmeMid[0x74 - 0x38 - 0xc];
	void *m_bfmeId;								///< retail this+0x74
};

// the index map BfmeConv776/HordeContainMemberNameMatches pins at 0x0001F91F
class BfmeSubDSU
{
public:
	void **bfmeTwoDSU(void **what);
};

// matches HordeContainMemberNameMatches.cpp's BfmeHordeRosterEntry-adjacent
// BfmeHordeSlot exactly (16 bytes); only used here for its begin/end extent
struct BfmeHordeSlot
{
	char m_bfmeBody[0x10];
};

struct Rva00242A30FormationSlot
{
	char m_pad00[4];
	Coord3D m_position;					///< offset 0x4
	Bool m_busy;							///< offset 0x10
	char m_pad11[0x1c - 0x11];
};

class Rva00242A30Owner;
extern void j_00019736();

class Rva00242A30Owner
{
public:
	void rva00242A30GetFormationPosition(
		Coord3D *outPosition, Object *member, Real *outThird);

private:
	typedef void (Rva00242A30Owner::*Rva00242A30HelperFn)(Real *out);
	void rva00242A30CallHelper(Real *out)
	{
		union
		{
			void (*freeFn)();
			Rva00242A30HelperFn memberFn;
		} fn;
		fn.freeFn = ::j_00019736;
		(this->*fn.memberFn)(out);
	}

	char m_bfmeHead[0x120];
	BfmeSubDSU m_bfmeIndices;					///< retail this+0x120
	char m_bfmeGap[0x12c - 0x124];
	BfmeHordeSlot *m_bfmeSlotsBegin;			///< retail this+0x12c
	BfmeHordeSlot *m_bfmeSlotsEnd;				///< retail this+0x130
	char m_bfmeGap2[0x1d8 - 0x134];
	Rva00242A30FormationSlot *m_formationSlots;	///< retail this+0x1d8
	char m_bfmeGap3[0x1fc - 0x1dc];
	Bool m_readyFlag;							///< retail this+0x1fc
};

void Rva00242A30Owner::rva00242A30GetFormationPosition(
	Coord3D *outPosition, Object *member, Real *outThird)
{
	Coord3D *pos = &member->m_bfmePosition;
	void *key = member->m_bfmeId;
	int index = (int)(long)*m_bfmeIndices.bfmeTwoDSU(&key);

	unsigned int fallbackXBits = *(unsigned int *)&pos->x;
	unsigned int fallbackYBits = *(unsigned int *)&pos->y;
	unsigned int fallbackZBits = *(unsigned int *)&pos->z;

	if (index < 0)
	{
		outPosition->x = *(Real *)&fallbackXBits;
		*(unsigned int *)&outPosition->y = fallbackYBits;
		*(unsigned int *)&outPosition->z = fallbackZBits;
		return;
	}

	UnsignedInt count = (UnsignedInt)(m_bfmeSlotsEnd - m_bfmeSlotsBegin);
	if ((UnsignedInt)index > count)
	{
		outPosition->x = *(Real *)&fallbackXBits;
		*(unsigned int *)&outPosition->y = fallbackYBits;
		*(unsigned int *)&outPosition->z = fallbackZBits;
		return;
	}

	if (m_readyFlag)
	{
		Rva00242A30FormationSlot *slot = &m_formationSlots[index];
		if (!slot->m_busy)
		{
			outPosition->x = slot->m_position.x;
			outPosition->y = slot->m_position.y;
			outPosition->z = slot->m_position.z;
			return;
		}
	}

	Real callResult;
	rva00242A30CallHelper(&callResult);
	Real xNew = callResult + pos->x;
	*outThird = *(Real *)&fallbackZBits;
	Real yNew = *(Real *)&fallbackZBits + pos->y;
	Real zPass = pos->z;
	outPosition->x = xNew;
	outPosition->y = yNew;
	outPosition->z = zPass;
}
