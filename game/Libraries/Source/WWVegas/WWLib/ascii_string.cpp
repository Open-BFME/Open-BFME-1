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

// str() is inline (string_base.h): the ctor below tests m_data in place and
// falls back to the wide TheNullChr at 0x0107388C, operator+= to the narrow one
// at 0x0107388B.

// 0x00889090: the base StringBase<char> is built first (inline, one zero
// store) and is protected by an EH state while format() runs -- retail's
// unwind funclet at 0x00C56930 destroys it through ??1?$StringBase@D@@AAE@XZ.
AsciiString::AsciiString(const UnicodeString &that)
{
    format(AsciiString("%ls"), that.str());
}

// 0x00889140: the same shape as the converting constructor above, on an
// already-built AsciiString: this->str() first, then the wide argument, into
// the "%s%ls" format string at 0x0113302C. The `this` the body returns is
// never re-zeroed (no `mov [esi],0`), so this is the append overload rather
// than a second converting constructor.
AsciiString &AsciiString::operator+=(const UnicodeString &that)
{
    format(AsciiString("%s%ls"), str(), that.str());
    return *this;
}

