// The forward goes through the five-byte ILT thunk at 0x00002A59, defined as
// ?j_00002a59@@YAXXZ in game/gen_small/thunks_000.cpp (target 0x005D67C0).
// The thunk declares no arguments of its own: it jumps with the thiscall `this`
// in ECX and the caller's arguments already in place, so the call is spelled
// through a thiscall member pointer of the same shape.
extern void j_00002a59();

class BfmeSubBUC
{
};

typedef void (BfmeSubBUC::*bfmeDoBUCThunk)(void *one, void *two, void *three,
	void *four);

union BfmeDoBUCThunkCast
{
	void (__cdecl *freeFunction)(void *one, void *two, void *three, void *four);
	bfmeDoBUCThunk memberFunction;
};

void bfmeGoBUC(BfmeSubBUC *sub, void *one, void *two, void *three, void *four)
{
	if (sub != 0)
	{
		BfmeDoBUCThunkCast cast;
		cast.freeFunction = reinterpret_cast<void (__cdecl *)(void *, void *,
			void *, void *)>(&::j_00002a59);
		(sub->*cast.memberFunction)(one, two, three, four);
	}
}