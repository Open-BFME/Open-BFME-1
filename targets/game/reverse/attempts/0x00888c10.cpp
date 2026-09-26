// ?set@?$StringBase@D@@QAEXABV1@HH@Z
// partial score=0.4965 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <stddef.h>
#include "string_base.h"
extern const char g_bfmeEmptyAscii[];

template <>
void StringBase<char>::set(const StringBase<char> &src, int start, int len)
{
    int end = start + len;
    if (end >= 0)
    {
        int srcLen = src.m_data ? src.m_data->length : 0;
        if (start < srcLen)
        {
            if (start < 0)
            {
                len = end;
                start = 0;
            }
            if (start + len >= (src.m_data ? src.m_data->length : 0))
                len = (src.m_data ? src.m_data->length : 0) - start;
            const char *data = src.m_data ? &src.m_data->data[0] : g_bfmeEmptyAscii;
            data += start;
            if (m_data && data == &m_data->data[0])
                return;
            if (len)
            {
                ensureUniqueBufferOfSize(len, false, data, len, 0, 0);
                return;
            }
        }
    }
    releaseBuffer();
}
