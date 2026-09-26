// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep
// RVA 0x009A85D0: GlobalAlloc wrapper with flag 0x40.
// The former dump claim crossed two int3 bytes into GlobalFree at 0x009A85E0.
#include "windows.h"

HGLOBAL __cdecl Rva009A85D0GlobalAlloc(SIZE_T bytes)
{
    return ::GlobalAlloc(0x40, bytes);
}
