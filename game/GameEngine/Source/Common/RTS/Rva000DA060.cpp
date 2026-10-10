// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include "ascii_string.h"
#include "xfer.h"

namespace rts { template<class T> struct hash { unsigned int operator()(T value) const; }; }
typedef _STL::hash_map<AsciiString,float,rts::hash<AsciiString> > Rva000DA060Rooms;
typedef Rva000DA060Rooms::value_type Rva000DA060Pair;
typedef _STL::hashtable<Rva000DA060Pair,AsciiString,rts::hash<AsciiString>,
    _STL::_Select1st<Rva000DA060Pair>,_STL::equal_to<AsciiString>,
    _STL::allocator<Rva000DA060Pair> > Rva000DA060Table;
extern void j_00036f0c();
extern void j_0000b271();

class Rva000DA060Calls
{
public:
    // ?begin@Rva000DA060Calls@@QAE?AU?$_Ht_iterator@U?$pair@$$CBVAsciiString@@M@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@M@_STL@@@2@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@M@_STL@@@2@U?$equal_to@VAsciiString@@@2@V?$allocator@U?$pair@$$CBVAsciiString@@M@_STL@@@2@@_STL@@XZ absent-from-retail
    __forceinline Rva000DA060Rooms::iterator begin()
    {
        typedef void (Rva000DA060Table::*Method)(Rva000DA060Rooms::iterator *);
        union { void (__cdecl *address)(); Method method; } call;
        call.address = &j_00036f0c;
        Rva000DA060Rooms::iterator result;
        (reinterpret_cast<Rva000DA060Table *>(this)->*call.method)(&result);
        return result;
    }

    // ??ARva000DA060Calls@@QAEAAMABVAsciiString@@@Z absent-from-retail
    __forceinline float &operator[](const AsciiString &key)
    {
        typedef float &(Rva000DA060Rooms::*Method)(const AsciiString &);
        union { void (__cdecl *address)(); Method method; } call;
        call.address = &j_0000b271;
        return (reinterpret_cast<Rva000DA060Rooms *>(this)->*call.method)(key);
    }
};

// ?rva000da060@@YGXPAVXfer@@PAV?$hash_map@VAsciiString@@MU?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@M@_STL@@@5@@_STL@@@Z
void __stdcall rva000da060(Xfer *owner, Rva000DA060Rooms *rooms)
{
    if (owner->IsStoring())
    {
        unsigned int count = rooms->size();
        *owner == count;
        Rva000DA060Rooms::iterator it;
        it = reinterpret_cast<Rva000DA060Calls *>(rooms)->begin();
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
            (*reinterpret_cast<Rva000DA060Calls *>(rooms))[key] = value;
        }
    }
}
