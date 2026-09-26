// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x000616D0, 29 bytes. The ILT thunk at 0x0001D2B4
// targets the complete padding-separated body. The old carved start at
// 0x000616E0 was refuted because it is this body's loop back edge.
// Retail reads one cdecl pointer argument, returns zero for null, otherwise
// counts bytes up to the terminator. No class or original name is established.
#include <string.h>
#pragma intrinsic(strlen)

unsigned int rva000616D0StringLength(const char *text)
{
    return text ? strlen(text) : 0;
}
