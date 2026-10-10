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
	if (m_data)
	{
		if (m_data->capacity > newLen)
		{
			if (m_data->ref_count == 1)
			{
				if (src1)
				{
					memcpy(m_data->data, src1, src1Len * sizeof(T));
					m_data->length = src1Len;
				}
				if (src2)
				{
					memcpy(m_data->data + m_data->length, src2, src2Len * sizeof(T));
					m_data->length += src2Len;
				}
				m_data->data[m_data->length] = 0;
				return;
			}
		}
		else if (src2)
		{
			unsigned grown = m_data->capacity + m_data->capacity / 2;
			if ((int)grown - 1 > newLen)
				newLen = (int)grown - 1;
		}
	}

	int bytes = sizeof(int) + 2 * sizeof(unsigned short) + (newLen + 1) * sizeof(T);
	if (bytes > 0x7fff)
		throw 1;
	bytes = (bytes + 3) / 4 * 4;

	Header *newData = (Header *)malloc(bytes);
	newData->ref_count = 1;
	newData->capacity = (unsigned short)((bytes - 8) / sizeof(T));
	if (m_data && keepData)
	{
		memcpy(newData->data, m_data->data, m_data->length * sizeof(T));
		newData->length = m_data->length;
	}
	else
	{
		newData->length = 0;
	}
	if (src1)
	{
		memcpy(newData->data, src1, src1Len * sizeof(T));
		newData->length = src1Len;
	}
	if (src2)
	{
		memcpy(newData->data + newData->length, src2, src2Len * sizeof(T));
		newData->length += src2Len;
	}
	newData->data[newData->length] = 0;

	releaseBuffer();
	m_data = newData;
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
