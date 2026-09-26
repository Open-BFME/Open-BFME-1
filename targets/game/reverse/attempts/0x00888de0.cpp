// ??0?$StringBase@G@@AAE@PBG@Z
// partial score=0.8659 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <stddef.h>
#define _DLL
#include <string.h>
#include "string_base.h"

template <>
StringBase<wchar_t>::StringBase(const wchar_t *str)
{
    m_data = 0;
    if (str) {
        int len = (int)wcslen(str);
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
