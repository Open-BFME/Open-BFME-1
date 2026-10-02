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

bool __stdcall bfmeAskCPC(BfmeThingCPC *thing);

bool __stdcall bfmeGoCPC(BfmeThingCPC *thing)
{
	if (bfmeAskCPC(thing) && thing->m_bfmeMid != 0 &&
		!((const Thing *)thing)->isKindOf((KindOfType)2))
		return true;
	return false;
}
