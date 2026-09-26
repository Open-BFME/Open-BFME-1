// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// STLport vector<T>::operator= for the 180-byte element family reached by
// Rva00366060::operator=.  The enclosing assignment pins the ILT and proves
// that its 12-byte member is this vector; only the element payload is unknown.

#include <vector>

struct Rva00365070Element
{
	char m_body[0xB4];
	Rva00365070Element();
	Rva00365070Element(const Rva00365070Element &other);
	~Rva00365070Element();
	Rva00365070Element &operator=(const Rva00365070Element &other);
};

template class _STL::vector<Rva00365070Element>;
