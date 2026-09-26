// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport vector<8-byte POD>::~vector at 0x009CBBA0 (45 B; a gap
// claimed by its shape): the base releases the buffer -- blocks over 0x80
// bytes through operator delete the rest through the static node allocator.
// The element is an address-derived shell; STLport exceptions off.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva009CBBA0Elem
{
	int m_0;
	int m_1;
};

template class _STL::vector<Rva009CBBA0Elem>;
