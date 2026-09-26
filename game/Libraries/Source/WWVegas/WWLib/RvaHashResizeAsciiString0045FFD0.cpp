// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

class AsciiString
{
public:
    AsciiString(const AsciiString &other) : m_data(other.m_data) {}

    const char *str() const
    {
        return m_data.m_data ? &m_data.m_data->data[0] : "";
    }

    StringBase<char> m_data;
};

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

struct Rva00461360Value
{
public:
    Rva00461360Value(const Rva00461360Value &other);
    ~Rva00461360Value();

    AsciiString m_name;
    UnicodeString m_translatedName;
    int m_groupID;
    int m_numWaiting;
    int m_maxWaiting;
    int m_numGames;
    int m_numPlaying;
};

struct Rva00461360ExtractKey
{
    const AsciiString &operator()(const Rva00461360Value &entry) const
    {
        return entry.m_name;
    }
};

typedef _STL::hashtable<Rva00461360Value, AsciiString, rts::hash<AsciiString>,
    Rva00461360ExtractKey, _STL::equal_to<AsciiString>,
    _STL::allocator<Rva00461360Value> > Rva00461360Table;

template void Rva00461360Table::resize(unsigned int);
