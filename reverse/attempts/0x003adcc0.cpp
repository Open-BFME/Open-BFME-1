// ?j_00021f26@Glo012F1024Item@@QAEXXZ
// partial score=0.35 date=2026-09-10
// Identity: ILT thunk 0x00021F26 (functions.csv d_00021f26 gen-thunk,
// target=FUN_007adcc0) is called directly by bfmeEnter's tail sequence
// (Glo012F1024Entry_bfmeStep.cpp, matched, 0x003AEE70). Retail body is
// 192B (ghidra boundary 183 was short of the trailing ret).
//
// Shape confirmed: walks the +0x9C BfmeFlag16Vector (16-byte records:
// char head[0xC]; unsigned char flag; char tail[3];). Per record it
// heap-allocates 16 bytes (call ??2@YAPAXI@Z, push 0x10), and IF that
// succeeds constructs the item with three args taken from the record --
// value dword at +4, ADDRESS of the dword at +8, and the flag byte at
// +0xC -- via a callee at retail VA 0x4358FF (RVA 0x000358FF). Whether
// or not the allocation/construction succeeded, the (possibly-null)
// item pointer is always passed to Glo012F1028Type::j_00003f0d (retail
// VA 0x403F0D / RVA 0x00003F0D), called on the global Glo012F1028
// (mov ecx,[0x12F1028]) -- NOT through m_bfmeSub like bfmeNotify.
//
// Both new symbols.csv pins landed clean (pin_consistency --check OK):
//   ??0Glo012F1024FlagCtor16A@@QAE@HPAXE@Z,0x000358FF
//   ?j_00003f0d@Glo012F1028Type@@QAEXPAX@Z,0x00003F0D
//
// THE WALL: retail's SEH prologue is Form B (mov eax,fs:[0] / push -1 /
// push <scopetable> / push eax / mov fs:[0],esp -- see project note
// seh-prologue-has-two-forms). No source shape tried reproduces Form B
// here; MSVC always emits Form A (push -1 first) for this body under
// this TU's /DNDEBUG /MD /EHsc, regardless of whether the constructed
// item is a named local, a bare argument-list temporary, or collapsed
// into the call expression directly (all three tried, byte-identical
// downstream). Making j_00021f26 a REAL Glo012F1024Item member (as
// below) does NOT disturb bfmeEnter's own already-matched 129B compile
// -- confirmed via explain_mismatch after every edit.
//
// SEPARATE from the prologue: even past that, retail keeps 'this' in
// ebx and the byte-offset accumulator in edi; every source shape tried
// here (for-loop, hoisted if+do-while, index-only, explicit byte-offset
// local) gets the SAME two registers but with the roles SWAPPED (this
// in edi, offset in ebx) and a different push grouping around the
// early-exit branch (retail pushes ebx+ebp unconditionally then esi+edi
// only after the size>0 check; ours pushes ebp+esi+edi unconditionally
// then ebx after the check). Best result: 180/192, 142 non-reloc bytes
// differing per tools/probe.py (cascades from the prologue+register
// swap, not a semantic error -- field offsets, callee args and control
// flow all check out against retail's disassembly).
//
// t=90min model=claude-sonnet-5

// cl: /DNDEBUG /MD /EHsc

struct BfmeFlag16
{
	char m_bfmeHead[0x0C];
	unsigned char m_bfmeFlag;
	char m_bfmeTail[0x03];
};

class BfmeFlag16Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeFlag16 *m_bfmeBegin;
	BfmeFlag16 *m_bfmeEnd;
};

class Glo012F1028Type
{
public:
	char m_bfmeHead[0x28];
	void *m_bfmeSub;
	void j_00003f0d(void *item);
};

extern Glo012F1028Type *Glo012F1028;

class Glo012F1024FlagCtor16A
{
public:
	Glo012F1024FlagCtor16A(int value, void *addr, unsigned char flag);
	char m_bfmeBody[0x10];
};

class Glo012F1024Item
{
public:
	void j_00021f26(void);

	char m_bfmePad[0x9C];
	BfmeFlag16Vector m_bfmeFlag16;			// +0x9C
};

void Glo012F1024Item::j_00021f26(void)
{
	unsigned int index = 0;
	if (m_bfmeFlag16.bfmeSize() != 0)
	{
		do
		{
			BfmeFlag16 *elem = m_bfmeFlag16.m_bfmeBegin + index;
			Glo012F1024FlagCtor16A *obj = new Glo012F1024FlagCtor16A(*(int *)((char *)elem + 4), (void *)((char *)elem + 8), elem->m_bfmeFlag);
			void *item = 0;
			if (obj != 0)
				item = obj;
			Glo012F1028->j_00003f0d(item);
			++index;
		} while (index < m_bfmeFlag16.bfmeSize());
	}
}
