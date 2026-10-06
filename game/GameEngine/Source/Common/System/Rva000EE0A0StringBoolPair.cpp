// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Five opaque retail twins (?dup_000ee0a0, ?dup_000ee5a0, ?dup_000eefa0,
// ?dup_0033a5f0, ?dup_0033a870) of a pair<const key, bool> whose key copies
// through the narrow StringBase<char> body 0x00887B60: the two-argument
// constructor, the copy constructor and _Construct. Their rows used to sit on
// the pristine Zero Hour LanguageFilter.cpp, whose strong filterLine is not
// retail's (LanguageFilter_filterLine.cpp owns 0x0044DB90). Two addresses per
// shape means at least two distinct instantiations, and neither key type is
// proven, so the key keeps an address-derived name over the real AsciiString.

#include <utility>
#include <memory>

#include "ascii_string.h"

class Rva000EE0A0Key : public AsciiString
{
public:
    Rva000EE0A0Key(const Rva000EE0A0Key &src) : AsciiString(src) {}
};

typedef std::pair<const Rva000EE0A0Key, bool> Rva000EE0A0Pair;

template _STL::pair<const Rva000EE0A0Key, bool>::pair(const Rva000EE0A0Key &, const bool &);
template _STL::pair<const Rva000EE0A0Key, bool>::pair(const Rva000EE0A0Pair &);
template void _STL::_Construct(Rva000EE0A0Pair *, const Rva000EE0A0Pair &);
