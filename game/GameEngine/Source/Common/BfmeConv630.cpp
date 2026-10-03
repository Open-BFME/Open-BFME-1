typedef bool Bool;

enum KindOfType
{
	KINDOF_INVALID = 0
};

// The kind query this TU calls is Thing::isKindOf(KindOfType) const; the real
// header declares the class, this TU only adds the member it calls.
#define THING_TU_MEMBERS \
	Bool isKindOf(KindOfType t) const;
#include "Thing/thing.h"
#undef THING_TU_MEMBERS

struct BfmeThingCPC
{
	unsigned char m_bfmeHead[0x204];
	void *m_bfmeMid;
};

// Retail's call target is the ILT thunk at 0x00025EF5, owned by
// game/gen_small/thunks_018.cpp as ?j_00025ef5@@YAXXZ.  It is declared here by
// its decorated symbol and called through a __stdcall typedef, the convention
// BfmeConv502.cpp uses, instead of under a TU-local name nothing defines.
extern "C" void __cdecl __identifier("?j_00025ef5@@YAXXZ")();
typedef bool (__stdcall *BfmeAskCPCThunk)(BfmeThingCPC *thing);

bool __stdcall bfmeGoCPC(BfmeThingCPC *thing)
{
	if (((BfmeAskCPCThunk)&__identifier("?j_00025ef5@@YAXXZ"))(thing) &&
		thing->m_bfmeMid != 0 &&
		!((const Thing *)thing)->isKindOf((KindOfType)2))
		return true;
	return false;
}
