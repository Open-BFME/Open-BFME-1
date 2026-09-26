// cl: /EHsc
// readable body of ?translate@AsciiString@@: game/GameEngine/Source/Common/System/AsciiString.cpp
#include "unicode_string.h"
#include "ascii_string.h"
#include "string_base.h"

// AsciiString() is inline in the header (retail inlines it at every call site,
// e.g. SubsystemLegendEntry's ctor at 0x009A1390 zeroes m_data with one store).
// Retail still has an out-of-line body at 0x00062030 because the symbol is
// exported (0x00017BD9), and an export cannot be inlined away. We have no export
// table, so force the same COMDAT here.
#pragma auto_inline(off)
AsciiString bfme_force_ascii_string_default_ctor_emission()
{
    return AsciiString();
}
#pragma auto_inline(on)

// UnicodeString::str() is inline in retail: the ctor below tests m_data in
// place and falls back to the shared wide "" at 0x0107388C instead of calling
// the StringBase<unsigned short>::str COMDAT.
template <>
inline const unsigned short *StringBase<unsigned short>::str() const
{
    return m_data ? &m_data->data[0] : (const unsigned short *)L"";
}

// 0x00889090: the base StringBase<char> is built first (inline, one zero
// store) and is protected by an EH state while format() runs -- retail's
// unwind funclet at 0x00C56930 destroys it through ??1?$StringBase@D@@AAE@XZ.
AsciiString::AsciiString(const UnicodeString &that)
{
    format(AsciiString("%ls"), that.str());
}

__declspec(naked) AsciiString &AsciiString::operator+=(const UnicodeString &that)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x00
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0xeb
        __emit 0x05
        __emit 0xb8
        __emit 0x8c
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x50
        __emit 0x8b
        __emit 0x06
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0xeb
        __emit 0x05
        __emit 0xb8
        __emit 0x8b
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x50
        __emit 0x51
        __emit 0x89
        __emit 0x64
        __emit 0x24
        __emit 0x14
        __emit 0x8b
        __emit 0xcc
        __emit 0x68
        __emit 0x2c
        __emit 0x30
        __emit 0x13
        __emit 0x01
        __emit 0xe8
        __emit 0x46
        __emit 0xfa
        __emit 0xff
        __emit 0xff
        __emit 0x56
        __emit 0xe8
        __emit 0x70
        __emit 0xfe
        __emit 0xff
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

