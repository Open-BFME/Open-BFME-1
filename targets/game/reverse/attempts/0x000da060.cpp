// ?d_000da060@@YAXXZ
// partial score=1.0 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include "ascii_string.h"
#include "xfer.h"

namespace rts { template<class T> struct hash { unsigned int operator()(T value) const; }; }
typedef _STL::hash_map<AsciiString,float,rts::hash<AsciiString> > Rva000DA060Rooms;
template<> float &Rva000DA060Rooms::operator[](const AsciiString &);
typedef Rva000DA060Rooms::value_type Rva000DA060Pair;
typedef _STL::hashtable<Rva000DA060Pair,AsciiString,rts::hash<AsciiString>,
    _STL::_Select1st<Rva000DA060Pair>,_STL::equal_to<AsciiString>,
    _STL::allocator<Rva000DA060Pair> > Rva000DA060Table;
template<> Rva000DA060Table::iterator Rva000DA060Table::begin();

void __stdcall rva000da060(Xfer *owner, Rva000DA060Rooms *rooms)
{
    if (owner->IsStoring())
    {
        unsigned int count = rooms->size();
        *owner == count;
        Rva000DA060Rooms::iterator it;
        it = rooms->begin();
        for (; it != rooms->end(); ++it)
        {
            AsciiString key = it->first;
            float value = it->second;
            *owner == key;
            *owner == value;
        }
    }
    else
    {
        unsigned int count = 0;
        *owner == count;
        AsciiString key;
        for (unsigned int i = 0; i < count; ++i)
        {
            float value;
            *owner == key;
            *owner == value;
            (*rooms)[key] = value;
        }
    }
}
