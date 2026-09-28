// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x006A7B60 (418 bytes): STLport hashtable::resize for
// hash_map<AsciiString, UnicodeString, rts::hash, rts::equal_to>.  The value
// type was earlier modelled as GameSpyGroupRoom (the copy ctor at 0x00887B60
// is only the AsciiString key copy rts::hash takes by value).  The table's
// node constructor copies pair<const AsciiString, UnicodeString> through the
// out-of-line pair copy at 0x0069EF10 (StringBase<char> then StringBase<G>),
// and its caller 0x006AF840 inserts exactly that pair into the
// MilesAudioManager subtitle map at +0x96C (resize then
// insert_unique_noresize at 0x006AB4A0).

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *first, const void *second, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
    AsciiString(const AsciiString &other) : m_data(other.m_data) {}

    const char *str() const
    {
        return m_data.m_data ? &m_data.m_data->data[0] : "";
    }

    int compare(const AsciiString &other) const
    {
        const int length = other.m_data.m_data ? other.m_data.m_data->length : 0;
        const char *data = other.m_data.m_data ? &other.m_data.m_data->data[0] : "";
        const int myLength = m_data.m_data ? m_data.m_data->length : 0;
        const char *myData = m_data.m_data ? &m_data.m_data->data[0] : "";
        const int result = memcmp(myData, data, myLength < length ? myLength : length);
        if (result != 0)
            return result;
        return myLength - length;
    }

    StringBase<char> m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
    return left.compare(right) == 0;
}

namespace rts
{
template <class T>
struct hash
{
    unsigned int operator()(T value) const;
};

template <>
struct hash<AsciiString>
{
    unsigned int operator()(AsciiString value) const
    {
        return static_cast<unsigned int>(_STL::__stl_hash_string(value.str()));
    }
};
}

#include "unicode_string.h"

namespace rts
{
template <class T> struct equal_to;
template <> struct equal_to<AsciiString>
{
    bool operator()(const AsciiString &left, const AsciiString &right) const
    {
        return left == right;
    }
};
}

typedef _STL::pair<const AsciiString, UnicodeString> AsciiUnicodePair;

typedef _STL::hashtable<AsciiUnicodePair, AsciiString, rts::hash<AsciiString>,
    _STL::_Select1st<AsciiUnicodePair>, rts::equal_to<AsciiString>,
    _STL::allocator<AsciiUnicodePair> > Rva006A7B60Table;

template void Rva006A7B60Table::resize(unsigned int);
