// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// The symbol pin and the SubsystemLegend copy callers identify this as the
// STLport vector<AsciiString> copy constructor at retail 0x000D2E70.
#define _STLP_NO_EXCEPTIONS 1
#include <new>
#include "ascii_string.h"
#include <vector>

template class _STL::vector<AsciiString,
	_STL::allocator<AsciiString> >;
