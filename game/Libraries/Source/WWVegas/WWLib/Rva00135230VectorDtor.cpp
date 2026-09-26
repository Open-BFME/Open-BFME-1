// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport vector<4-byte POD>::~vector at 0x00135230 (45 B; a gap
// claimed by its shape): the base releases the buffer -- blocks over 0x80
// bytes through operator delete the rest through the static node allocator.
// The element is an address-derived shell; STLport exceptions off.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva00135230Elem
{
	int m_0;
};

template class _STL::vector<Rva00135230Elem>;
