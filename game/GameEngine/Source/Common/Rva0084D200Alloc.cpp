// cl: /O2 /MD
//
// Opaque 12-byte zeroed allocator at 0x0084D200 (29 B). The body pushes
// 0xC, calls malloc through IAT slot 0x0135944C, drops the argument, and
// on null returns null; otherwise it zeroes three dwords and returns the
// pointer. The `memset(p, 0, 0xC)` spelling is EXACT via probe.py: the
// three plain stores hoist `xor ecx,ecx` above `add esp,4` and use
// `cmp/je`, missing by 15 bytes, while memset reproduces retail's
// `add-esp/test/jne-1` order, the bare `ret` null arm, and the
// `xor-ecx/mov-edx-eax` triple-store tail.
//
// IDENTITY IS NOT RECOVERED: no caller, string or vtable names the holder,
// so the record and function names are derived from the address.

#include <string.h>

extern "C" __declspec(dllimport) void *__cdecl malloc(unsigned int);

struct Rva0084D200Rec
{
    int m_a;
    int m_b;
    int m_c;
};

// ?dup_0084d200@@YAPAURva0084D200Rec@@XZ
Rva0084D200Rec *__cdecl dup_0084d200(void)
{
    Rva0084D200Rec *p = (Rva0084D200Rec *)malloc(0xC);
    if (p == 0)
        return 0;
    memset(p, 0, 0xC);
    return p;
}
