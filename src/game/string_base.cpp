#include "string_base.h"

#include <string.h>

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
int StringBase<T>::getLength() const
{
    return m_data ? m_data->length : 0;
}

template <typename T>
void StringBase<T>::validate() const
{
}

template class StringBase<char>;
