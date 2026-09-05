// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// STLport vector<T>::operator= for the 220-byte (0xDC) element family.
// Retail 0x003B6A40. Neighbour allocate-and-copy is bfmeMake_003B68A0.
// Element type is the same 220-byte stand-in already used by push_back at
// 0x003AC170 and _M_clear at ILT 0x0000B4F6.

#include <vector>

struct Rva003AC170Element
{
	char m_body[0xD8]; // plus the virtual-table pointer = 0xDC
	Rva003AC170Element();
	Rva003AC170Element(const Rva003AC170Element &other);
	virtual virtual virtual ~Rva003AC170Element();
	Rva003AC170Element &operator=(const Rva003AC170Element &other);
};

template class _STL::vector<Rva003AC170Element>;
