// ?Rva0042F0D0@@YG_NVAsciiString@@@Z
// Authentic one-pointer StringInline ABI audit; target's word length field is retained by the proven retail layout.
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Ireference/shims/stringinline
#include "StringInline.h"

struct Rva0042F0D0Buffer
{
    int m_refCount;
    short m_length;
};

// address-derived name (real owner/name unproven)
bool __stdcall Rva0042F0D0(AsciiString value)
{
    const Rva0042F0D0Buffer *buffer = *(const Rva0042F0D0Buffer **)&value;

    if (!buffer)
        goto zero;
    if (!buffer->m_length)
        goto zero;
    goto one;
zero:
    return false;
one:
    return true;
}
