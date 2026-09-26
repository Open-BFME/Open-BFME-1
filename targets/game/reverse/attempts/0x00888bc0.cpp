// ??0?$StringBase@D@@AAE@PBD@Z
// partial score=0.7222 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <stddef.h>
#define _DLL
#include <string.h>
#include "string_base.h"

template <>
StringBase<char>::StringBase(const char *str)
{
    m_data = 0;
    if (str) {
        int len = (int)strlen(str);
        if (m_data && str == &m_data->data[0])
            return;
        if (len)
            ensureUniqueBufferOfSize(len, false, str, len, 0, 0);
        else
            releaseBuffer();
    } else {
        releaseBuffer();
    }
}
