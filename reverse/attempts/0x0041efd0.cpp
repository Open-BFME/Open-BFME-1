// ?Rva0041EFD0@BfmeOwnerRC@@QAEDPAX0@Z
// partial score=0.9 date=2026-09-11
//
// Owner tag BfmeOwnerRC already established by its landed callees' pins
// (bfmeGetARC/bfmeGetBRC/bfmeSendRC @BfmeOwnerRC, bfmeResolveRC@BfmeInnerRC);
// the method itself and the intermediate BfmeUnitRC/BfmeStateRC/
// BfmeHolderRC/BfmeThingRC field models are not recovered identities.
// t=25min model=Sonnet 5
//
// Identity note: the four REL32 callees (0x000022BB, 0x0004B12D, 0x00040246,
// 0x00036EA3) are themselves gen-thunk jump stubs (5B each), not the real
// callees. Their real targets are already-landed, unrelated methods:
// Overridable::getFinalOverride (0x00087A80, via 0x000022BB),
// BFMERopeDrawableGetPositionShim::get (0x0041D090, via 0x0004B12D),
// Thing::getUnitDirectionVector2D (0x00132140, via 0x00040246), and
// 0x00413A40 (via 0x00036EA3, not yet in the ledger). This is a real lead on
// the owning class (likely Drawable- or Object-adjacent, given the rope/
// direction-vector/override callees and the landed Drawable.cpp neighbour at
// 0x0041F2A0), but recovering it needs a dedicated investigation, not
// something this pass could close; recorded here so the next agent does not
// re-discover it from scratch.
//
// 113/117 bytes. Guard chain, resolve, the two no-arg calls and the
// six-argument forward (including returning the callee's char result
// directly) all match; return-0 is correctly last.
// Residue: retail materialises the null arm of `state` --
//   test ebp,ebp / je L0 / mov eax,[ebp+204h] / jmp L1 / L0: xor eax,eax /
//   L1: test eax,eax / je exit
// -- while MSVC threads the jump (a null unit and a null state reach the
// same exit) and emits a single `test ebp,ebp; je exit`. That is the whole
// 4-byte gap (the "jmp L1"+"xor eax,eax" retail pair we never emit), and it
// also shifts the callee-saved allocation (retail ebx/ebp/edi, ours
// ebp/esi/edi -- cosmetic, not a byte-count contributor; confirmed by
// disassembly, the diff is exactly the 4 missing bytes of the null-arm
// materialization).
//
// Ruled out this pass (both compile byte-identical to the already-banked
// if/else and ternary spellings -- same instruction/relocation shape,
// confirmed via tools/probe.py's experiment-history cache):
//   - Explicit goto-based control flow mirroring retail's basic-block shape
//     literally (`if (unit==0) goto null_state; state=...; goto have_state;
//     null_state: state=0; have_state: if (state) ...`): MSVC 7.1 still
//     proves the two paths converge and re-threads the jump identically.
//   - `BfmeStateRC * volatile state`: forces a real spill/reload (134 bytes,
//     worse) but still does not reproduce retail's specific fld/materialize
//     shape; volatile changes memory traffic, not the branch topology.
// Prior pass (model=opus-5) had already ruled out plain if/else and the
// ternary form. Between the two passes, if/else, ternary and goto all
// produce the identical threaded shape: this is jump-threading the MSVC 7.1
// optimizer performs at the IR level, before any of these C++ spellings
// could differ from one another. Next agent: this is very likely a genuine
// optimizer wall, not a source-shape defect; if attempting again, the only
// unexplored lever is forcing register pressure or an intervening opaque
// call between the unit-null test and the state-null test so the compiler
// cannot prove the two conditions collapse to one, but that risks adding an
// instruction retail does not have.
class BfmeThingRC;

class BfmeInnerRC
{
public:
	BfmeThingRC *bfmeResolveRC(void);
};

class BfmeThingRC
{
public:
	unsigned char m_bfmeHeadRC[4];
	BfmeInnerRC *m_bfmeInnerRC;
	unsigned char m_bfmeGapRC[0x68];
	int m_bfmeKindRC;
};

class BfmeHolderRC
{
public:
	int m_bfmeSpareRC;
	BfmeThingRC *m_bfmeThingRC;
};

class BfmeStateRC
{
public:
	unsigned char m_bfmeHeadRC[0x1cc];
	BfmeHolderRC *m_bfmeHolderRC;
};

class BfmeUnitRC
{
public:
	unsigned char m_bfmeHeadRC[0x204];
	BfmeStateRC *m_bfmeStateRC;
};

class BfmeOwnerRC
{
public:
	char Rva0041EFD0(void *first, void *second);

	void *bfmeGetARC(void);
	void *bfmeGetBRC(void);
	char bfmeSendRC(BfmeUnitRC *unit, BfmeHolderRC *holder, void *a, void *b, void *first, void *second);

	unsigned char m_bfmeHeadRC[0xfc];
	BfmeUnitRC *m_bfmeUnitRC;
};

char BfmeOwnerRC::Rva0041EFD0(void *first, void *second)
{
	BfmeUnitRC *unit = m_bfmeUnitRC;
	BfmeStateRC *state = unit ? unit->m_bfmeStateRC : 0;

	if (state)
	{
		BfmeHolderRC *holder = state->m_bfmeHolderRC;

		if (holder)
		{
			BfmeThingRC *thing = holder->m_bfmeThingRC;

			if (thing && thing->m_bfmeInnerRC)
				thing = thing->m_bfmeInnerRC->bfmeResolveRC();

			if (thing->m_bfmeKindRC == 1)
			{
				void *a = bfmeGetARC();
				void *b = bfmeGetBRC();

				return bfmeSendRC(unit, holder, a, b, first, second);
			}
		}
	}

	return 0;
}
