// ?bfmeEachRS@@YAXPAXPAUBfmeElemQR@@00@Z (identity unknown)
// partial score=0.85 date=2026-09-06
// 67/70 bytes; everything through the copy-constructor call is byte-exact.
// Sibling of 0x004742C0 (landed as BfmeConv1727.cpp) -- same 16-byte element
// with a trailing handle whose copy ctor is the string_base alias, pinned
// DIRECTLY at 0x00887B60 (the ??0GameSpyGroupRoom pin points at a thunk).
// Three residues:
//   +0x0f  retail `add esi,-0x10`, MSVC `sub esi,0x10` (tried --p, p = p - 1,
//          p += -1, &p[-1]; all give sub);
//   +0x25  marker at [esp+0x2c] vs [esp+0x24] -- retail's slot sits 8 bytes
//          higher, i.e. above the two dwords pushed at +0x0c/+0x0e, so retail
//          treats those as frame slots and MSVC as outgoing arguments;
//   +0x35  retail re-reads the constant from [esp+0x20] and pushes eax where
//          MSVC folds it to `push 0`. The value at that address IS the zero
//          pushed at +0x0c, so the first and last arguments name one object.
// Tried for the last two: a plain int local, a volatile int local (83 bytes,
// whole frame changes), and an 8-byte by-value pair struct built in the
// argument area (68 bytes, MSVC zeroes through ecx). Nothing reproduces a
// memory re-read of a slot MSVC has proved constant.
class BfmeRoomQR
{
public:
	BfmeRoomQR(const BfmeRoomQR &other);	// pin ??0BfmeRoomQR@@QAE@ABV0@@Z,0x00887B60
	~BfmeRoomQR() throw() {}

	int m_bfmeHandleQR;
};

struct BfmeElemQR
{
	int m_bfmeAQR;
	int m_bfmeBQR;
	int m_bfmeCQR;
	BfmeRoomQR m_bfmeRoomQR;
};

void __cdecl bfmeDoRS(int zero, BfmeElemQR *slot, BfmeElemQR *same, BfmeElemQR value,
	void *extra, int flag);	// pin at the thunk 0x0000561E

void __cdecl bfmeEachRS(void *first, BfmeElemQR *last, void *third, void *extra)
{
	int zero = 0;

	last = last - 1;
	bfmeDoRS(zero, last, last, *last, extra, zero);
}
