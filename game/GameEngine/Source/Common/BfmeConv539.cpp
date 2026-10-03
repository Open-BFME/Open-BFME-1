// The kind query goes through the five-byte ILT thunk at 0x0001E33A, defined
// as ?j_0001e33a@@YAXXZ in game/gen_small/thunks_014.cpp (target
// 0x0066F8F0).  The thunk declares no arguments of its own: it jumps with the
// thiscall `this` in ECX, leaving the result in EAX, so the call is spelled
// through a thiscall member pointer of the same shape.
extern void j_0001e33a();

class BfmeSubBVD
{
};

typedef int (BfmeSubBVD::*bfmeKindBVDThunk)(void);

union BfmeKindBVDThunkCast
{
	void (__cdecl *freeFunction)(void);
	bfmeKindBVDThunk memberFunction;
};

struct BfmeMidBVD
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubBVD *m_bfmeSub;
};

struct BfmeOwnerBVD
{
	unsigned char m_bfmeHead[0x10];
	BfmeMidBVD *m_bfmeMid;
};

struct BfmeThingBVD
{
	unsigned char m_bfmeHead[0x1c];
	BfmeOwnerBVD *m_bfmeOwner;
};

bool bfmeGoBVD(BfmeThingBVD *what)
{
	BfmeSubBVD *sub = what->m_bfmeOwner->m_bfmeMid->m_bfmeSub;
	if (!sub)
		return false;

	BfmeKindBVDThunkCast cast;
	cast.freeFunction = reinterpret_cast<void (__cdecl *)(void)>(
		&::j_0001e33a);
	if ((sub->*cast.memberFunction)() == 0x2f)
		return true;
	return false;
}