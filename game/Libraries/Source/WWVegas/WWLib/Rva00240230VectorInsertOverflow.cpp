// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// STLport vector<T>::_M_insert_overflow for the 28-byte element family whose
// exact push_back body is at 0x00244A80.  The element payload is not recovered;
// its width and nontrivial copy operations are fixed by the retail body.

#include <vector>

struct Rva00244A80Element
{
	char m_body[28];
	Rva00244A80Element();
	Rva00244A80Element(const Rva00244A80Element &other);
	Rva00244A80Element &operator=(const Rva00244A80Element &other);
};

template class _STL::vector<Rva00244A80Element>;
