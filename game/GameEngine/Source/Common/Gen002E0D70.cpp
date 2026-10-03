// cl: /DNDEBUG /MD /O2 /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

struct Gen002E0D70Rec
{
	int a;
	AsciiString name;
	char flag;
};

// RVA 0x0000C437 is retail's five-byte ILT thunk into the 0x002E0BC0 body;
// `?j_0000c437@@YAXXZ` (game/gen_small/thunks_005.cpp) is the only definition
// of that address in the ledger, and the declared-only gen002E0BC0 name has no
// definition anywhere. Naming the thunk and calling it through the body's own
// cdecl signature keeps the reference resolvable at link time and reproduces
// retail's call rel32.
extern void j_0000c437();

typedef void ( *Gen002E0BC0Fn )( void *a, Gen002E0D70Rec *p, Gen002E0D70Rec *q, Gen002E0D70Rec rec, void *c, int zero );

void gen002E0D70(void *a, Gen002E0D70Rec *last, int, void *c)
{
	void *arg4 = c;
	Gen002E0D70Rec *p = last;
	reinterpret_cast<Gen002E0BC0Fn>( j_0000c437 )( a, p - 1, p - 1, p[-1], arg4, 0 );
}
