// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: vector<AsciiString>::_M_insert_overflow, retail 0x00757C70. The
// name was parked on the 5-byte thunk at 0x000112C0.
//
// STLport's own body out of the real header. AsciiString needs only its size
// and the two members the body reaches -- a copy constructor for the element
// moves and releaseBuffer for the tail -- both of which stay calls.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// Only what these bodies reach.
#include "string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}
	~AsciiString() { m_data.releaseBuffer(); }

	StringBase<char> m_data;
};

void BfmeAsciiStringVectorAnchor(_STL::vector<AsciiString> &v, const AsciiString &value)
{
	v.insert(v.begin(), value);
}
