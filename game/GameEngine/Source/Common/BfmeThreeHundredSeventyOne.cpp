struct BfmeHeadXA
{
	unsigned char m_bfmePad[4];
	void *m_bfmeOne;
	BfmeHeadXA *m_bfmeTwo;
	BfmeHeadXA *m_bfmeThree;
};

class BfmeListXA
{
public:
	BfmeHeadXA *m_bfmeHead;
	int m_bfmeCount;
};

// The drop goes through the five-byte ILT thunk at 0x0001FF82, defined as
// ?j_0001ff82@@YAXXZ (game/gen_small/thunks_015.cpp); it is spelled through a
// thiscall member pointer of the same shape.
extern void j_0001ff82();

typedef void (BfmeListXA::*bfmeDropXAThunk)(void *what);

union BfmeDropXAThunkCast
{
	void (__cdecl *freeFunction)(void *what);
	bfmeDropXAThunk memberFunction;
};

class BfmeThingXA
{
public:
	void bfmeClearXA();
	unsigned char m_bfmeHead[0x550];
	BfmeListXA m_bfmeList;
};

void BfmeThingXA::bfmeClearXA()
{
	BfmeListXA *list = &m_bfmeList;
	if (list->m_bfmeCount != 0)
	{
		BfmeDropXAThunkCast cast;
		cast.freeFunction = reinterpret_cast<void (__cdecl *)(void *)>(&::j_0001ff82);
		(list->*cast.memberFunction)(list->m_bfmeHead->m_bfmeOne);
		list->m_bfmeHead->m_bfmeTwo = list->m_bfmeHead;
		list->m_bfmeHead->m_bfmeOne = 0;
		list->m_bfmeHead->m_bfmeThree = list->m_bfmeHead;
		list->m_bfmeCount = 0;
	}
}
