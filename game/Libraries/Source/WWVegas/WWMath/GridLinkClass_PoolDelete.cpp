// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug

// 20-byte null-guarded pool free at retail 0x008DDEB0.
// The scalar operator delete of the pooled GridLinkClass that gridcull.cpp
// allocates: null passes through, anything else goes to the matched
// Free_Object_Memory pool free at 0x008DDA50: retail calls
// ?Free_Object_Memory@?$ObjectPoolClass@VGridLinkClass@@$0BAA@@@QAEXPAVGridLinkClass@@@Z
// (dis_retail 0x008DDEB0) with the GridLinkClass pool object at 0x0133D1AC as
// `this`, so pool and member are spelled as the real mempool.h template that
// body was instantiated from, not a TU-local `ObjectPool` view.
// Address-derived opaque name keeps the address token.

#include "../WWLib/mempool.h"

class GridLinkClass;

extern ObjectPoolClass<GridLinkClass,256> g_pool008DDA50;

// ?dup_008ddeb0@@YAXPAX@Z
void __cdecl dup_008ddeb0(void *memory)
{
	if (memory == 0) {
		return;
	}
	g_pool008DDA50.Free_Object_Memory((GridLinkClass *)memory);
}
