// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector<UnicodeString>::_M_insert_overflow, retail 0x00532A00,
// 268 bytes. The name was parked on the 5-byte thunk at 0x00016A63.
//
// STLport's own body out of the real header. The element is four bytes -- the
// size divides by four and the allocation multiplies by four -- which is
// UnicodeString's single pointer, and its copy constructor and destructor stay
// calls.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString(const UnicodeString &other);
	~UnicodeString();

private:
	void *m_data;
};

void BfmeUnicodeStringVectorAnchor(_STL::vector<UnicodeString> &v, const UnicodeString &value)
{
	v.insert(v.begin(), value);
}
