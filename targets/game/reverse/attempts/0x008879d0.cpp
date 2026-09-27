// ?ensureUniqueBufferOfSize@?$StringBase@D@@AAEXH_NPBDH1H@Z
// partial score=0.925257731959 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "string_base.h"
#include <stdlib.h>
#include <string.h>

template <typename T>
inline void StringBase<T>::ensureUniqueBufferOfSize(int newLen, bool keepData, const T *src1, int src1Len, const T *src2, int src2Len)
{
    if (m_data) {
        if (m_data->capacity > newLen) {
            if (m_data->ref_count == 1) {
                if (src1) {
                    memcpy(m_data->data, src1, src1Len * sizeof(T));
                    m_data->length = src1Len;
                }
                if (src2) {
                    memcpy(m_data->data + m_data->length, src2, src2Len * sizeof(T));
                    m_data->length += src2Len;
                }
                m_data->data[m_data->length] = 0;
                return;
            }
        } else if (src2) {
            int capacity = m_data->capacity; int grown = capacity + capacity / 2; --grown;
            if (grown > newLen) newLen = grown;
        }
    }
    int bytes = 8 + (newLen + 1) * (int)sizeof(T);
    if (bytes > 32767) throw 1;
    bytes = ((bytes + 3) / 4) * 4;
    Header *data = (Header *)malloc(bytes);
    data->ref_count = 1;
    data->capacity = (bytes - 8) / sizeof(T);
    if (m_data && keepData) {
        memcpy(data->data, m_data->data, m_data->length * sizeof(T));
        data->length = m_data->length;
    } else data->length = 0;
    if (src1) {
        memcpy(data->data, src1, src1Len * sizeof(T));
        data->length = src1Len;
    }
    if (src2) {
        memcpy(data->data + data->length, src2, src2Len * sizeof(T));
        data->length += src2Len;
    }
    data->data[data->length] = 0;
    releaseBuffer();
    m_data = data;
}

template void StringBase<char>::ensureUniqueBufferOfSize(int, bool, const char *, int, const char *, int);
