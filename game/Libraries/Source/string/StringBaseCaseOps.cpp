// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// StringBase<T> case and trim operations. Retail inlines the templated
// ensureUniqueBufferOfSize into each of them, so they live apart from
// StringBase.cpp, whose out-of-line instantiations of that helper would
// force a call instead.
#include "../WWVegas/WWLib/string_base.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
            int grown = m_data->capacity + (m_data->capacity >> 1) - 1;
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

template <>
void StringBase<char>::removeLastChar()
{
    if (m_data) {
        ensureUniqueBufferOfSize(m_data->length, true, 0, 0, 0, 0);
        int len = m_data->length - 1;
        if (len > 0) {
            m_data->data[len] = 0;
            m_data->length = len;
        } else releaseBuffer();
    }
}


template <>
void StringBase<char>::toLower()
{
    if (m_data) {
        ensureUniqueBufferOfSize(m_data->length, true, 0, 0, 0, 0);
        char *p = m_data->data;
        char *end = p + m_data->length;
        while (p != end) {
            *p = (char)tolower(*p);
            ++p;
        }
    }
}

template <>
void StringBase<char>::toUpper()
{
    if (m_data) {
        ensureUniqueBufferOfSize(m_data->length, true, 0, 0, 0, 0);
        char *p = m_data->data;
        char *end = p + m_data->length;
        while (p != end) {
            *p = (char)toupper(*p);
            ++p;
        }
    }
}

template <>
void StringBase<wchar_t>::removeLastChar()
{
    if (m_data) {
        ensureUniqueBufferOfSize(m_data->length, true, 0, 0, 0, 0);
        int len = m_data->length - 1;
        if (len > 0) {
            m_data->data[len] = 0;
            m_data->length = len;
        } else releaseBuffer();
    }
}

template <>
void StringBase<wchar_t>::toLower()
{
    if (m_data) {
        ensureUniqueBufferOfSize(m_data->length, true, 0, 0, 0, 0);
        wchar_t *p = m_data->data;
        wchar_t *end = p + m_data->length;
        while (p != end) {
            wchar_t c = *p;
            *p = (wchar_t)towlower(c);
            ++p;
        }
    }
}

template <>
void StringBase<wchar_t>::toUpper()
{
    if (m_data) {
        ensureUniqueBufferOfSize(m_data->length, true, 0, 0, 0, 0);
        wchar_t *p = m_data->data;
        wchar_t *end = p + m_data->length;
        while (p != end) {
            wchar_t c = *p;
            *p = (wchar_t)towupper(c);
            ++p;
        }
    }
}
