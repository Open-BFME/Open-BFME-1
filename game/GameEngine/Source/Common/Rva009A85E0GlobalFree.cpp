// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep
// RVA 0x009A85E0: GlobalFree wrapper following two int3 bytes.
#include "windows.h"

HGLOBAL __cdecl Rva009A85E0GlobalFree(HGLOBAL handle)
{
    return ::GlobalFree(handle);
}
