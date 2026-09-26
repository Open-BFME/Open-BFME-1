// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// STLport vector<pair<AsciiString, unsigned int> > copy at retail 0x0076B080.

#define _STLP_NO_EXCEPTIONS 1
#include <new>
#include <vector>
#include "ascii_string.h"

typedef _STL::pair<AsciiString, unsigned int> Rva0076B080Element;

template class _STL::vector<Rva0076B080Element,
	_STL::allocator<Rva0076B080Element> >;
