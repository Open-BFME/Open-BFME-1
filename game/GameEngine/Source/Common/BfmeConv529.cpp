// The forward goes through the five-byte ILT thunk at 0x00024D70, defined as
// ?j_00024d70@@YAXXZ in game/gen_small/thunks_017.cpp.  The thunk declares no
// arguments of its own: it jumps with the thiscall `this` in ECX and the
// caller's arguments already in place, so the call is spelled through a
// thiscall member pointer of the same shape.
extern void j_00024d70();

struct BfmeInnerBUA
{
	unsigned char m_bfmeHead[4];
};

typedef void (BfmeInnerBUA::*bfmeDoBUAThunk)(void *what);

union BfmeDoBUAThunkCast
{
	void (__cdecl *freeFunction)(void *what);
	bfmeDoBUAThunk memberFunction;
};

struct BfmeSubBUA
{
	unsigned char m_bfmeHead[0x20];
	BfmeInnerBUA m_bfmeInner;
};

struct BfmeOwnerBUA
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubBUA *m_bfmeSub;
};

void bfmeGoBUA(BfmeOwnerBUA *owner, void **what)
{
	if (owner != 0 && owner->m_bfmeSub != 0)
	{
		BfmeDoBUAThunkCast cast;
		cast.freeFunction = reinterpret_cast<void (__cdecl *)(void *)>(
			&::j_00024d70);
		(owner->m_bfmeSub->m_bfmeInner.*cast.memberFunction)(*what);
	}
}