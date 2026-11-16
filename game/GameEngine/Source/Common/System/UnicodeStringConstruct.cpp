// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// STLport 4.5.3 _Construct at 0x0009EF50 calls the wide StringBase copy at 0x00888400.
// Keeping the UnicodeString forwarder visible preserves that callee instead
// of the unrelated char-copy pin used by the old PeerDefs declaration.
// vector<UnicodeString>::push_back reaches it through ILT 0x00026503 at 0x005330C3.

#include <memory>

class UnicodeString;

#include "string_base.h"

#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->~StringBase(); }


template void _STL::_Construct(UnicodeString *, const UnicodeString &);
