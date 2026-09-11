// ?bfmeLookupFJ@BfmeHostFJ@@QAEHH@Z
// partial score=0.94 date=2026-09-11
// Same size as retail (135/135, probe.py "size ours=135 retail=135") and the
// entire loop body, inline strcmp expansion, and epilogue are byte-identical
// from +0x2b through the end (item pointer walked by `add edi,8` each
// iteration matching retail exactly; the match-return path recomputes
// `items[i].m_bfmeValueFJ` from the ORIGINAL base pointer and index, not
// through the incremented walking pointer -- both facts recovered by manual
// disassembly of the full retail body, not just probe.py's evidence window).
// Two source facts fixed this vs the prior 129/135 stash: (1) the loop must
// keep BOTH a walking `item` pointer (its `m_bfmeNameFJ` used for the inline
// strcmp, matching retail's per-iteration `add edi,8`) AND the original
// `items` base+index for the once-only return value -- a plain `items[i]`
// throughout compiles to full scaled-index addressing in the hot loop
// (wrong shape, the prior stash's actual defect); (2) `++i; ++item;` must be
// spelled in THAT order (retail: `inc ebp` before `add edi,8`) or the two
// increments swap.
// Remaining 40/135 diff bytes are confined entirely to the prologue
// (offsets +0x05 to +0x2f, before the loop starts): retail keeps the
// this->table->owner->group chain in eax/ecx/edx alone (no register
// promotion needed) and interleaves `push ebx`/`push ebp`/`push esi` between
// computing `n` and testing it, then `push edi` between the test and the
// `jle`; ours computes the same chain but assigns the table pointer to edi
// (a callee-saved register) and pushes all four callee-saved registers
// together before touching `this`. Ruled out without effect: an explicit
// `BfmeOwnerFJ *owner` local instead of the `s->m_bfmeOwnerFJ->m_bfmeGroupFJ`
// chain (byte-identical output); pointer arithmetic vs `&m_bfmeTableFJ[idx]`
// (not tried further, both already produce the same combined SIB
// addressing retail uses for the owner load). Ruled out as worse: replacing
// the `if (n > 0) { ... }` block with an early `if (n <= 0) return -1;`
// (152 bytes -- the compiler no longer merges the two `return -1` tails,
// confirming the 2026-09-08 lesson that the nested-if/do-while shape is
// required). This is a genuine MSVC 7.1 shrink-wrap/register-promotion
// scheduling difference for the pointer-chase prologue; no source spelling
// tried moves it. t=10min model=Sonnet 5
extern "C" int strcmp(const char *a, const char *b);

#pragma intrinsic(strcmp)

class BfmeItemFJ
{
public:
	const char *m_bfmeNameFJ;
	int m_bfmeValueFJ;
};

class BfmeGroupFJ
{
public:
	unsigned char m_bfmeHeadFJ[0x30];
	int m_bfmeCountFJ;
	BfmeItemFJ *m_bfmeItemsFJ;
};

class BfmeOwnerFJ
{
public:
	unsigned char m_bfmeHeadFJ[0x10];
	BfmeGroupFJ *m_bfmeGroupFJ;
};

class BfmeSlotFJ
{
public:
	void *m_bfmeHeadFJ;
	const char *m_bfmeNameFJ;
	unsigned char m_bfmeGapFJ[4];
	BfmeOwnerFJ *m_bfmeOwnerFJ;
};

class BfmeHostFJ
{
public:
	int bfmeLookupFJ(int idx);

	unsigned char m_bfmeHeadFJ[0x24];
	BfmeSlotFJ *m_bfmeTableFJ;
};

int BfmeHostFJ::bfmeLookupFJ(int idx)
{
	BfmeSlotFJ *s = &m_bfmeTableFJ[idx];
	BfmeGroupFJ *g = s->m_bfmeOwnerFJ->m_bfmeGroupFJ;
	int n = g->m_bfmeCountFJ;

	if (n > 0)
	{
		BfmeItemFJ *items = g->m_bfmeItemsFJ;
		BfmeItemFJ *item = items;
		const char *name = s->m_bfmeNameFJ;
		int i = 0;

		do
		{
			if (strcmp(name, item->m_bfmeNameFJ) == 0)
				return items[i].m_bfmeValueFJ;

			++i;
			++item;
		}
		while (i < n);
	}

	return -1;
}
