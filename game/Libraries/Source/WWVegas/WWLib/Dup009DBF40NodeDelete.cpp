// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWDebug

// 20-byte null-guarded pool free at retail 0x009DBF40.
// The scalar operator delete of the pooled MultiListNodeClass that the
// GenericMultiListClass in multilist.cpp allocates: null passes through,
// anything else goes to the matched Free_Object_Memory pool free at
// 0x009DBEB0: retail calls
// ?Free_Object_Memory@?$ObjectPoolClass@VMultiListNodeClass@@$0BAA@@@QAEXPAVMultiListNodeClass@@@Z
// (dis_retail 0x009DBF40) with the MultiListNodeClass pool object at 0x0134ECD4
// as `this`, so pool and member are spelled as the real mempool.h template
// that body was instantiated from, not a TU-local `ObjectPool` view.
// Address-derived opaque name keeps the address token.

#include "mempool.h"

class MultiListNodeClass;

extern ObjectPoolClass<MultiListNodeClass,256> g_pool009DBEB0;

// ?dup_009dbf40@@YAXPAX@Z
void __cdecl dup_009dbf40(void *memory)
{
	if (memory == 0) {
		return;
	}
	g_pool009DBEB0.Free_Object_Memory((MultiListNodeClass *)memory);
}
