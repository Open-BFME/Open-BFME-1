// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: vector<GenericObjectCreationNugget::AnimSet>::_M_insert_overflow,
// retail 0x00755CA0, 284 bytes (the extent runs to the int3 padding). The name
// was parked on the 5-byte thunk at 0x0000DB2F.
//
// The element is twelve bytes -- the copy loop steps by 0x0C -- and one of them
// is an AsciiString, since each move calls StringBase<char>'s copy constructor.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;

#include "string_base.h"

#include "ascii_string.h"

class GenericObjectCreationNugget
{
public:
	struct AnimSet
	{
		AsciiString m_bfmeName;
		Int m_bfmeFirst;
		Int m_bfmeSecond;
	};
};

void BfmeAnimSetVectorAnchor(_STL::vector<GenericObjectCreationNugget::AnimSet> &v, const GenericObjectCreationNugget::AnimSet &value)
{
	v.insert(v.begin(), value);
}
