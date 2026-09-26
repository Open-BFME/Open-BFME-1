// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport allocator<12-byte element>::allocate at 0x00850D80
// (49 B; a gap in the INI region claimed by its shape): zero elements give a
// null pointer larger blocks than 0x80 bytes go to operator new and the rest
// to the static node allocator.  The element is an address-derived 12-byte
// shell.

#include <memory>

struct Rva00850D80Elem
{
	int m_a, m_b, m_c;
};

template class _STL::allocator<Rva00850D80Elem>;
