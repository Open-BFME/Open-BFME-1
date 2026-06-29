#include "string_base.h"

#include <string.h>

template <typename T>
StringBase<T>::StringBase()
{
    m_data = 0;
}

template <typename T>
void StringBase<T>::debugIgnoreLeaks()
{
}

template <typename T>
bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

template <typename T>
bool StringBase<T>::isNotEmpty() const
{
    return !isEmpty();
}

template <typename T>
int StringBase<T>::getLength() const
{
    return m_data ? m_data->length : 0;
}

template <typename T>
const T *StringBase<T>::str() const
{
    return m_data ? &m_data->data[0] : (const T *)"";
}

template <typename T>
T *StringBase<T>::peek() const
{
    return &m_data->data[0];
}

template <typename T>
T StringBase<T>::getCharAt(int index) const
{
    return m_data ? m_data->data[index] : 0;
}

template <typename T>
void StringBase<T>::validate() const
{
}

template class StringBase<char>;
template class StringBase<wchar_t>;
