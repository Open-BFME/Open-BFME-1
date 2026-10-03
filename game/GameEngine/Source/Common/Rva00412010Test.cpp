// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00412010Inner
{
	char m_bfmeUnused;
};

// Retail calls the ILT thunk at 0x00019B5F, owned by game/gen_small/thunks_012.cpp
// as ?j_00019b5f@@YAXXZ (its target, 0x005C9980, has no ledger row of its own).
// The call is reached through a member-function pointer so it keeps its
// thiscall shape; ready is never referenced by name.
extern "C" void __cdecl __identifier("?j_00019b5f@@YAXXZ")();
typedef bool (Rva00412010Inner::*RvaReadyInnerThunk)();
union RvaReadyInnerThunkRef
{
	void *m_thunk;
	RvaReadyInnerThunk m_call;
};

class Rva00412010
{
	char m_pad[0xFC];
	Rva00412010Inner *m_inner;

public:
	int test() const;
};

int Rva00412010::test() const
{
	RvaReadyInnerThunkRef ready;
	ready.m_thunk = (void *)&__identifier("?j_00019b5f@@YAXXZ");
	Rva00412010Inner *inner = m_inner;
	if (inner && (inner->*ready.m_call)())
		return 1;
	return 0;
}
