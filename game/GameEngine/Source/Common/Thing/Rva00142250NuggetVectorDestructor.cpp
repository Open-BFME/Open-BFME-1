// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The carved body at retail RVA 0x00142250 destroys a 20-byte vector element.
// Each element owns two four-byte strings and releases them in reverse order.

#include <vector>
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct Rva00142250Nugget
{
	AsciiString first;
	AsciiString second;
	unsigned char m_padding[12];

	~Rva00142250Nugget()
	{
	}
};

template class _STL::vector<Rva00142250Nugget>;
