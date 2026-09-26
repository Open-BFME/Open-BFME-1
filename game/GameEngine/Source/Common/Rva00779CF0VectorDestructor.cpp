// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x00779CF0 destroys a 20-byte element whose first member is an
// AsciiString and whose second member is a vector<AsciiString>.  The
// destructor loop calls the nested vector destructor at 0x00026AB2 and then
// releases the first member through the established AsciiString body at
// 0x00887940.

#include <vector>

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct Rva00779CF0Element
{
	AsciiString m_name;
	_STL::vector<AsciiString> m_strings;
	int m_padding;
};

typedef char Rva00779CF0ElementSize[
	(sizeof(Rva00779CF0Element) == 0x14) ? 1 : -1];

template class _STL::vector<Rva00779CF0Element>;
