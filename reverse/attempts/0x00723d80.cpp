// ?d_00723d80@@YAXXZ
// partial score=0.35 date=2026-09-02
// PARTIAL / UNVERIFIED -- does not compile-match yet. Banked for the next agent.
// ghidra: FUN_00b23d80 retail @ 0x00723D80 size 160
// Sibling of BfmeA1137Cache/BfmeA1137Cache2 (see attempt_723b60.cpp,
// attempt_723c50.cpp). Zeroes this->m_bfme4c and this->m_bfme98, copies a
// field from a SECOND global pointer at RVA 0x0012F0FE0 (->[+0xc]) into
// this->m_bfme94, then branches on a byte at [globalUnknown1137 + 0x3a]:
//   - false path: copies this->m_bfme58/m_bfme5c into this->m_bfme38/m_10,
//     clears this->m_bfme3d, returns.
//   - true path: re-derives the global-or-this pointer again (same
//     "global->[+4] non-null -> lock thunk" guard as the rest of the
//     family) and copies its [+0x30] into this->m_bfme38, then a THIRD
//     independent lookup of the same guard copies [+0x34] into
//     this->m_bfme10.
//
// Blocker: same 0x0012F15F8 (and now also 0x0012F0FE0) global identity gap;
// this is otherwise the most tractable of the four once that identity
// lands, since it has no x87/float content at all.

extern "C" void *g_bfmeGlobalUnknown1137; // RVA 0x0012F15F8, identity TBD
extern "C" void *g_bfmeGlobalUnknown1137B; // RVA 0x0012F0FE0, identity TBD
void __fastcall bfmeWalkLock1137(void *p); // RVA 0x000022BB thunk -> 0x00087A80

class BfmeA1137Reset
{
public:
	void bfmeResetOrCopy();
	int m_bfme10;
	char m_bfmePad[0x24];
	int m_bfme38;
	char m_bfmePad2[4];
	int m_bfme3a_holder; // byte at +0x3a lives inside this padding
	char m_bfme3d;
	char m_bfmePad3[0xe];
	int m_bfme4c;
	char m_bfmePad4[8];
	int m_bfme58;
	int m_bfme5c;
	char m_bfmePad5[0x38];
	int m_bfme94;
	int m_bfme98;
};

static inline void *bfmeLockedGlobal1137()
{
	void *g = g_bfmeGlobalUnknown1137;
	if (g)
	{
		void *inner = *(void **)((char *)g + 4);
		if (inner)
			bfmeWalkLock1137(inner);
	}
	return g;
}

void BfmeA1137Reset::bfmeResetOrCopy()
{
	m_bfme4c = 0;
	m_bfme98 = 0;
	m_bfme94 = *(int *)((char *)g_bfmeGlobalUnknown1137B + 0xc);

	void *g = bfmeLockedGlobal1137();
	char flag = g ? *((char *)g + 0x3a) : 0;
	if (!flag)
	{
		m_bfme3d = 0;
		m_bfme38 = m_bfme58;
		m_bfme10 = m_bfme5c;
		return;
	}

	void *g2 = bfmeLockedGlobal1137();
	m_bfme38 = *(int *)((char *)g2 + 0x30);

	void *g3 = bfmeLockedGlobal1137();
	m_bfme10 = *(int *)((char *)g3 + 0x34);
}
