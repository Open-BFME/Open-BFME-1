// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "string_base.h"

// The character constructor owns one byte in a unique buffer.
template <>
StringBase<char>::StringBase(char c)
{
    m_data = 0;
    ensureUniqueBufferOfSize(1, false, &c, 1, 0, 0);
}
