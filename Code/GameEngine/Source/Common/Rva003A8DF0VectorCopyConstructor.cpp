// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME7: STLport vector<16-byte record>::vector(const vector &), retail
// 0x003A8DF0, 70 bytes -- the copy constructor shape of
// GeometryInfoCopyConstructor.cpp's vector<GeometryRecord> once
// _STLP_NO_EXCEPTIONS removes the try/catch around the element copy.  The
// element is only known to be sixteen trivially copyable bytes.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva003A8DF0Record
{
	int m_a;
	int m_b;
	int m_c;
	int m_d;
};

template _STL::vector<Rva003A8DF0Record, _STL::allocator<Rva003A8DF0Record> >::vector(
	const _STL::vector<Rva003A8DF0Record, _STL::allocator<Rva003A8DF0Record> > &);
