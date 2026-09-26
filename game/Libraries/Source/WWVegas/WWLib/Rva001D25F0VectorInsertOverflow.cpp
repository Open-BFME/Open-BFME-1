// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// STLport vector<T>::_M_insert_overflow for the 92-byte element family whose
// exact push_back body is at 0x001D28F0.  The element payload is not recovered;
// its width and nontrivial copy operation are fixed by the retail body.

#include <vector>

struct Rva001D28F0Element
{
	char m_body[92];
	Rva001D28F0Element();
	Rva001D28F0Element(const Rva001D28F0Element &other);
	Rva001D28F0Element &operator=(const Rva001D28F0Element &other);
};

template class _STL::vector<Rva001D28F0Element>;
