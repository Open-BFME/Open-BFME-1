// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00062EA0 destroys four-byte elements through AsciiString's
// destructor (ILT 0x0000D828 -> 0x0005EE90), which releases char StringBase data.
// The original folded STL entry spelling is unresolved; this descriptive name
// preserves the proven cdecl range ABI without the former Unicode identities.

#include "ascii_string.h"

void destroyAsciiStringRange(AsciiString *first, AsciiString *last)
{
    for (; first != last; ++first)
        first->~AsciiString();
}
