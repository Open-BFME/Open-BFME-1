// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <stddef.h>
#include "string_base.h"

template <>
StringBase<char>::StringBase(const StringBase<char> &src, int start, int len)
{
    m_data = 0;
    set(src, start, len);
}
