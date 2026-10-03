// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail's tail call at 0x000A1D60 leaves the incoming `what` argument at
// [esp+4] and returns the callee's eax, so the thunk it jumps to is entered
// with the caller's own argument already in place and pops it itself.

// The only definition of RVA 0x000294E7 is the 5-byte ILT thunk
// ?j_000294e7@@YAXXZ (game/gen_small/thunks_019.cpp), a plain void(void)
// __cdecl symbol, so its name cannot spell the callee-cleanup, one-stack-argument
// tail call this body makes.  Calling it through a callee-cleanup alias of that
// thunk keeps the relocation on ?j_000294e7@@YAXXZ - the only spelling that both
// resolves to 0x000294E7 for the byte comparison and links - while declaring
// the entry ABI retail's own bytes prove.
extern void j_000294e7();
typedef void *(__stdcall *Rva000A1D60Thunk)(void *what);

class BfmeThingDSA
{
public:
	void *bfmeGoDSA(void *what);
	char m_bfmeHead[0x40];
	char m_bfmeFlag;
};

void *BfmeThingDSA::bfmeGoDSA(void *what)
{
	if (m_bfmeFlag)
		return 0;
	return ((Rva000A1D60Thunk)&j_000294e7)(what);
}