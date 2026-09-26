// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <utility>

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString();
};

typedef std::pair<const UnicodeString, UnicodeString> UnicodeStringPair;

// The wide-key tree's _Construct at 0x0068F900 calls this copy constructor.
// Both constructors copy wide members at +0/+4; their unwind maps destroy
// the first member through UnicodeString's 0x0005EEA0 destructor.
template UnicodeStringPair::pair(const UnicodeString &, const UnicodeString &);
template UnicodeStringPair::pair(const UnicodeStringPair &);
