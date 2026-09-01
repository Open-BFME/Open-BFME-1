// cl: /DNDEBUG /MD /EHs-c-

#include "../../../Libraries/Source/WWVegas/WWLib/refcount.h"

// Two compiler-generated shutdown helpers for ref-counted renderer resources.
//
// Each global owns one reference.  Shutdown releases that reference, invokes
// the object's virtual disposal slot when the count reaches zero, and clears
// the global even when another owner keeps the object alive.

extern RefCountClass *g_rva005F4340Resource;
extern RefCountClass *g_rva005F7FA0Resource;

void releaseRva005F4340Resource(void)
{
	if (g_rva005F4340Resource != 0)
	{
		g_rva005F4340Resource->Release_Ref();
		g_rva005F4340Resource = 0;
	}
}

void releaseRva005F7FA0Resource(void)
{
	if (g_rva005F7FA0Resource != 0)
	{
		g_rva005F7FA0Resource->Release_Ref();
		g_rva005F7FA0Resource = 0;
	}
}
