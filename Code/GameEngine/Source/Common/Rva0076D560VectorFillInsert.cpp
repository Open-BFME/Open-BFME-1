// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME7: STLport vector<12-byte record>::_M_fill_insert, retail
// 0x0076D560, 306 bytes.  A byte twin of the vector<Coord3D> body at
// 0x000B7AF0 (310 bytes) minus the try/catch _STLP_NO_EXCEPTIONS removes:
// this copy came from a TU built with STLport exceptions off.  The element is
// only known to be twelve trivially copyable bytes, so it carries an
// address-derived tag.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva0076D560Record
{
	int m_a;
	int m_b;
	int m_c;
};

template void _STL::vector<Rva0076D560Record, _STL::allocator<Rva0076D560Record> >::_M_fill_insert(
	Rva0076D560Record *, unsigned int, const Rva0076D560Record &);
