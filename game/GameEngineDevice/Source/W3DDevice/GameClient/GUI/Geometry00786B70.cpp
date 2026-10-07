// cl: /DNDEBUG /MD /O2 /Ob2
// 0x00786B70: 40 executable bytes; RET at +0x27, then INT3 at +0x28.
// The matched Rva00788A30GeometryParser.cpp caller allocates 0x28 bytes and
// calls this constructor through ILT 0x000347A2 with ECX and no stack arguments.
// Geometry00786B70 is that caller's address-qualified owner, not an EA name.
// Retail installs table 0x01126AE4, also used by the matched 0x007875E0 dtor,
// and clears the three vector words at +4 and six trailing words at +0x10.
// This TU uses an offset-only view of those words; their semantics are unknown.

#include <string.h>

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// The table at 0x01126AE4 is the vftable recorded as ??_7Gen_007875E0@@6B@
// (emitted by Bfme5SelfRangeDtors.cpp); spelled by __identifier.
extern "C" int __identifier("??_7Gen_007875E0@@6B@")[];

class Geometry00786B70
{
public:
    Geometry00786B70() throw();
    void *m_at00;
    unsigned int m_at04;
    unsigned int m_at08;
    unsigned int m_at0c;
    unsigned int m_block[6]; // +0x10; retain the banked attempt's neutral name.
};

Geometry00786B70::Geometry00786B70() throw()
{
    m_at00 = __identifier("??_7Gen_007875E0@@6B@");
    // Keep the table store ahead of the zeroing, as in the retail constructor.
    // The intrinsic constrains compiler ordering without emitting instructions.
    _ReadWriteBarrier();
    m_at04 = 0;
    m_at08 = 0;
    m_at0c = 0;
    memset(m_block, 0, sizeof(m_block));
}
