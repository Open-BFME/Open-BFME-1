// ?rva006A5870Case4@Gen_006A6AF0@@QAEXPAURva006B9320Request@@@Z
// partial score=0.69 date=2026-09-22
// Open-BFME: Gen_006A6AF0 method, retail 0x006A5870, 170 bytes.
//
// Identity: case 4 of the process006B9320 dispatcher
// (Rva006B9320RequestDispatch.cpp) -- its case-4 thunk j_0000578b targets
// Ghidra's FUN_00aa5870, i.e. retail RVA 0x006A5870. Same family as the
// already-banked case-2 sibling at 0x006A5950 (reverse/attempts/0x006a5950.cpp):
// reads request->m_field->m_field28/m_field64, compares against the already
// landed Gen_006A6AF0::m_bfmeMap[field28] (Rva006A6AF0Grid.cpp), and on a
// match calls the pinned bfmePrep(int,int) with `this` unchanged. Unlike
// case 2, the equal branch does NOT return immediately: it reloads
// request->m_field, calls the landed
// ?getIsLogicalAudio@AudioEventRTS@@QBE_NXZ (AudioEventRTSClassification.cpp,
// pin 0x000046AB) directly on the field pointer with no offset adjustment
// (so this field is itself AudioEventRTS-layout-compatible at offset 0),
// inverts the bool with the classic neg/sbb/inc idiom, and calls a still-dump
// sibling at 0x006A56A0 (j_0003c060) with (field28, field64,
// !isLogicalAudio) -- the same 3-int-argument shape as the dispatcher's
// case5/case7 calls, just with a different third argument source. The
// not-equal branch is IDENTICAL in shape to case 2's: it re-derives
// m_bfmeCells[b + 2*a] and treats it as an embedded STL deque
// (start/finish iterator layout established in the case-2 stash), with the
// same pop_back_aux pin at 0x0069E810, the same unresolved global function
// pointer call through 0x1358E54, and the same conditional virtual
// release(1) call.
//
// probe.py: 53 of 170 non-relocation bytes differ (ours compiles to 164
// bytes; score 0.69). The equal branch (bfmeMap check, bfmePrep call,
// reloaded field, getIsLogicalAudio, inverted-bool call to
// rva006A56A0) is byte-exact through +0x88 -- the neg/sbb/inc inverted-bool
// idiom only appears when the `!expr` is passed inline as the call
// argument; binding it to a named `bool` local first produces a
// xor/test/sete form instead (94 diffs). The not-equal branch reuses case
// 2's shared-`char*` lever (reverse/attempts/0x006a5950.cpp), which scores
// better here too (54 diffs) than reading finish.cur/start.cur as two
// independent `m_bfmeCells[idx].field` expressions (62 diffs) even though
// retail's own instruction order looks like the latter (edx, eax and the
// cell pointer each recomputed via a full `[esi+ecx*8+CONST]` SIB
// address at +0x51/+0x58/+0x61) -- the shared-pointer source only gets
// eax/edx swapped relative to retail's register choice, which a
// `*(void**)cell == cur` operand-order flip narrowed by one byte (54->53).

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

class AudioEventRTS
{
public:
	bool getIsLogicalAudio() const;
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
	void rva006A56A0(int a, int b, int c);
	void rva006A5870Case4(Rva006B9320Request *request);

private:
	char m_bfmePad[0x9D4];
	BfmeCellAF0 m_bfmeCells[6];
	int m_bfmeMap[1];
};

// ?rva006A5870Case4@Gen_006A6AF0@@QAEXPAURva006B9320Request@@@Z
void Gen_006A6AF0::rva006A5870Case4(Rva006B9320Request *request)
{
	Rva006B9320Field *field = request->m_field;
	int b = field->m_field64;
	int a = field->m_field28;

	if (m_bfmeMap[a] == b)
	{
		bfmePrep(a, !request->m_flag10);
		field = request->m_field;
		rva006A56A0(a, b, !((AudioEventRTS *)field)->getIsLogicalAudio());
		return;
	}

	char *cell = (char *)this + 0x9D4 + (b + a * 2) * 5 * 8;
	void *cur = *(void **)(cell + 0x10);
	if (*(void **)cell == cur)
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
