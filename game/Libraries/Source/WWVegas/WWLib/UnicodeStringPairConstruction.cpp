// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <utility>

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
#include "unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }


typedef std::pair<const UnicodeString, UnicodeString> UnicodeStringPair;

// The wide-key tree's _Construct at 0x0068F900 calls this copy constructor.
// Both constructors copy wide members at +0/+4; their unwind maps destroy
// the first member through UnicodeString's 0x0005EEA0 destructor.
template UnicodeStringPair::pair(const UnicodeString &, const UnicodeString &);
template UnicodeStringPair::pair(const UnicodeStringPair &);
