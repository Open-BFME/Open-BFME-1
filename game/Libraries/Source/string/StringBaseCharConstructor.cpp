// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <stddef.h>
#include "string_base.h"

// The character constructor owns one byte in a unique buffer.
template <>
StringBase<char>::StringBase(char c)
{
    m_data = 0;
    ensureUniqueBufferOfSize(1, false, &c, 1, 0, 0);
}

template <>
StringBase<wchar_t>::StringBase(wchar_t c)
{
    m_data = 0;
    ensureUniqueBufferOfSize(1, false, &c, 1, 0, 0);
}
