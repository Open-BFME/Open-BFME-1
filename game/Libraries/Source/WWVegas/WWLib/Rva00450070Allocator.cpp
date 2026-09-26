// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail uses the STLport allocator split for a four-byte element here.

#include <vector>

struct Rva00450070Elem
{
	char m_body[4];
	Rva00450070Elem();
	Rva00450070Elem(const Rva00450070Elem &);
	~Rva00450070Elem();
	Rva00450070Elem &operator=(const Rva00450070Elem &);
};

template class _STL::vector<Rva00450070Elem>;
