// ?rva006A5950Case2@Gen_006A6AF0@@QAEXPAURva006B9320Request@@@Z
// partial score=0.59 date=2026-09-22
// Open-BFME: Gen_006A6AF0 method, retail 0x006A5950, 128 bytes.
//
// Identity: this is case 2 of the process006B9320 dispatcher
// (Rva006B9320RequestDispatch.cpp) -- its case-2 thunk j_00012c4c targets
// FUN_00aa5950 in Ghidra's naming, i.e. retail RVA 0x006A5950. Reading
// request->m_field->m_field28/m_field64 and comparing against
// this->m_bfmeMap[field28] at this+0xAC4 matches Gen_006A6AF0's ALREADY
// LANDED layout (Rva006A6AF0Grid.cpp): m_bfmePad[0x9D4] + m_bfmeCells[6] *
// sizeof(BfmeCellAF0=0x28) = 0x9D4+0xF0 = 0xAC4, and the equal-branch calls
// the pinned thiscall bfmePrep(int,int) (QAEXHH@Z) with `this` unchanged,
// exactly matching Gen_006A6AF0::bfmePrep's own signature. This reproduces
// half of Gen_006A6AF0::bfmeGo's condition ("if (m_bfmeMap[a] == b)
// bfmePrep(a, c);") but returns immediately afterward instead of falling
// into bfmeFill(), and its false-branch is unrelated to bfmeFill: it
// re-derives the SAME m_bfmeCells[b + 2*a] slot via a decomposed multiply
// (index*5 then an eax*8 SIB scale, since sizeof(BfmeCellAF0)=0x28=5*8) and
// treats that BfmeCellAF0 as an embedded STL deque object (matches the
// already-landed Open269E810DequeFull / Rva006A04E0AudioDeque pop_back_aux
// pin at 0x0069E810, called here through thiscall with ecx == the cell):
// m_bfmeFirst/m_bfmeMiddle are the deque's `start` iterator (0x10 B),
// m_bfmeLast is `finish.cur`, and the first word of m_bfmeTail is
// `finish.first` -- an empty check (finish.cur == start.cur), then a
// block-boundary check (finish.cur == finish.first) that falls into
// _M_pop_back_aux, else decrements finish.cur by one slot (4 B), reads the
// popped element, calls an unresolved global function pointer at 0x1358E54
// on element+4, and on a non-positive result and non-null element makes a
// vtable-slot-0 virtual call on it with argument 1 (a Release()-shaped
// call). Field/offset reading is exact from the disassembly; the exact C++
// surface of the deque manipulation is best-effort and not yet proven.
//
// probe.py: 52 of 128 non-relocation bytes differ (ours compiles to 125
// bytes; score 0.59). The bfmeMap check/call (+0x00..+0x2b) is byte-exact
// up to its relocation. The remainder trades off two mutually exclusive
// forms: sharing ONE `char *cell` pointer across the finish.cur/start.cur
// checks reproduces retail's single combined `lea ecx,[ecx+eax*8+0x9d4]`
// at +0x3b but reads the two fields in the wrong order (retail reads
// finish.cur at +0x9e4 BEFORE deriving the cell base; the shared-pointer
// form reads cell+0 first instead); reading the two fields as two
// independent `m_bfmeCells[idx].field` expressions gets the read order
// (and the +0x9e4 offset) right but then the compiler no longer folds the
// later cell-pointer materialization into one lea, splitting it into
// `lea eax,[ecx+eax*8]` + `lea ecx,[eax+0x9d4]` (127 B, 57 diffs -- worse
// on this metric even though the first field read matches). Neither
// spelling reproduces both retail habits at once in one session; the
// banked form keeps the higher-scoring single-lea version. Not yet tried:
// a source shape that forces MSVC to read finish.cur through the full SIB
// expression while still folding the later cell pointer into one lea.

struct Rva006B9320Field
{
	char m_pad00[0x28];
	int m_field28;
	char m_pad2c[0x18];
	unsigned char m_flag44;
	char m_pad45[0x1f];
	int m_field64;
};

struct Rva006B9320Request
{
	int m_action;
	Rva006B9320Field *m_field;
	void *m_payload;
	char m_pad0c[4];
	unsigned char m_flag10;
	unsigned char m_flag11;
};

class Rva006A04E0AudioDeque
{
public:
	void _M_pop_back_aux();
};

class Rva006A5950Releasable
{
public:
	virtual void release(int flag);
};

extern "C" int (__stdcall *g_rva01358E54)(void *);

struct BfmeCellAF0
{
	void *m_bfmeFirst;
	char m_bfmeMiddle[0x0c];
	void *m_bfmeLast;
	void *m_bfmeBound;
	char m_bfmeRest[0x10];
};

class Gen_006A6AF0
{
public:
	void bfmePrep(int a, int c);
	void rva006A5950Case2(Rva006B9320Request *request);

private:
	char m_bfmePad[0x9D4];
	BfmeCellAF0 m_bfmeCells[6];
	int m_bfmeMap[1];
};

// ?rva006A5950Case2@Gen_006A6AF0@@QAEXPAURva006B9320Request@@@Z
void Gen_006A6AF0::rva006A5950Case2(Rva006B9320Request *request)
{
	Rva006B9320Field *field = request->m_field;
	int a = field->m_field28;
	int b = field->m_field64;

	if (m_bfmeMap[a] == b)
	{
		bfmePrep(a, !request->m_flag10);
		return;
	}

	char *cell = (char *)this + 0x9D4 + (b + a * 2) * 5 * 8;
	void *cur = *(void **)(cell + 0x10);
	if (cur == *(void **)cell)
		return;

	if (cur == *(void **)(cell + 0x14))
	{
		((Rva006A04E0AudioDeque *)cell)->_M_pop_back_aux();
		return;
	}

	void *newCur = (char *)cur - 4;
	*(void **)(cell + 0x10) = newCur;
	void *item = *(void **)newCur;
	if (item == 0)
		return;

	int result = g_rva01358E54((char *)item + 4);
	if (result > 0)
		return;
	if (item == 0)
		return;

	((Rva006A5950Releasable *)item)->release(1);
}
