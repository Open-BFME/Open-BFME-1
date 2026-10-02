// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x009D79F0 is a 46-byte hash/modulo body, ending at RET 8.
// The former 76-byte dump also covered a separate iterator body at 0x009D7A20.
// No receiver or source-level template identity is established for this copy.
// Keep its owner and partial key view address-derived. The byte loads are signed.

#define _STLP_NO_EXCEPTIONS 1
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <hash_map>
#include <string>

struct Rva009D79F0Key
{
    const signed char *begin;
    const signed char *end;
};
class Rva009D79F0Owner
{
public:
    unsigned int bucket(const Rva009D79F0Key *key, unsigned int count) const;
};
unsigned int Rva009D79F0Owner::bucket(const Rva009D79F0Key *key, unsigned int count) const
{
    unsigned int value = 0;
    unsigned int length = static_cast<unsigned int>(key->end - key->begin);
    unsigned int base = reinterpret_cast<unsigned int>(key->begin);
    for (unsigned int i = 0; i < length; ++i)
        value = value * 5 + *reinterpret_cast<const signed char *>(i + base);
    return value % count;
}

// Retail 0x009D7A20: return the found node together with the table receiver.
// The native _M_find callee at 0x009D7680 proves the key/value contract.
// Keep this separate copy address-derived, as with the 0x009D7840 wrapper.
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > Rva009D7A20String;
typedef _STL::pair<const Rva009D7A20String, int> Rva009D7A20Value;
typedef _STL::hash_map<Rva009D7A20String, int, _STL::hash<Rva009D7A20String>,
    _STL::equal_to<Rva009D7A20String>, _STL::allocator<Rva009D7A20Value> > Rva009D7A20Map;
class Rva009D7A20Owner : public Rva009D7A20Map
{
public:
    Rva009D7A20Map::iterator lookup(const Rva009D7A20String &key);
};
Rva009D7A20Map::iterator Rva009D7A20Owner::lookup(const Rva009D7A20String &key)
{
    return Rva009D7A20Map::find(key);
}
