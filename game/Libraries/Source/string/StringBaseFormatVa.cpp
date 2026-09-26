// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <stddef.h>
#define _DLL
#include <stdio.h>
#include "string_base.h"

template <>
void StringBase<char>::format_va(const char *fmt, char *args)
{
    char buffer[8192];
    int len = _vsnprintf(buffer, 8192, fmt, args);
    if (m_data && buffer == &m_data->data[0])
        return;
    if (len)
        ensureUniqueBufferOfSize(len, false, buffer, len, 0, 0);
    else
        releaseBuffer();
}
