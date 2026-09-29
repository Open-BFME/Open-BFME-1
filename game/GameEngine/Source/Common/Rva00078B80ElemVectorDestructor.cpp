// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00078B80, 188 bytes: STLport vector destructor for a 16-byte element.
// The element is one AsciiString at +0 and one vector<AsciiString> at +4. The loop
// calls the vector<AsciiString> destructor at 0x000658A0 through ILT 0x00026AB2
// for the +4 member, then releases the AsciiString buffer at 0x00887940 for the
// +0 member, and the tail frees the buffer with the 0x80 byte node allocator split.
// The old ledger extent of 181 bytes stopped inside the second epilogue, the ret is at +0xBB.
// IDENTITY IS NOT RECOVERED. The element keeps an address-derived name.
#include <vector>
#include "ascii_string.h"

struct Rva00078B80Elem
{
	AsciiString m_name;
	_STL::vector<AsciiString> m_list;
};

typedef char Rva00078B80ElemMustBeSixteenBytes[sizeof(Rva00078B80Elem) == 16 ? 1 : -1];

template _STL::vector<Rva00078B80Elem>::~vector();
