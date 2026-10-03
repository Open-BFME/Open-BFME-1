// The INI `ExperienceLevel` block's `ModelConditionState = ` field callback.
// The block is parsed by 0x00382460 and its 22-entry FieldParse table at
// 0x010EAB48 points that key here, at 0x0037D1A0 (docs/ini_schema.md, read out
// of the exe). The body is the null-guarded forward every INIFieldParseProc of
// this shape uses: the instance owns the sub-parser, and a null instance is
// skipped rather than faulted.
//
// The instance layout is not recovered, so the sub-object it forwards to keeps
// its address-family name.

struct BfmeSubBKC
{
	void bfmeDoBKC(void *what, int flag);
	unsigned char m_bfmeHead[4];
};

struct BfmeThingBKC
{
	unsigned char m_bfmeHead[0x50];
	BfmeSubBKC m_bfmeSub;
};

// The forward reaches the ILT thunk at 0x00033433
// (`?j_00033433@@YAXXZ`, game/gen_small/thunks_024.cpp) with the sub-parser
// as this and the instance as the argument, so the callee is named by the
// thunk holding the body at that address.

extern void j_00033433();

void parseExperienceLevelModelConditionState(void *one, BfmeThingBKC *two)
{
	typedef void (BfmeSubBKC::*Call)(void *, int);
	union { void (*raw)(); Call forward; } call;

	if (two != 0)
	{
		call.raw = j_00033433;
		(two->m_bfmeSub.*call.forward)(one, 0);
	}
}
