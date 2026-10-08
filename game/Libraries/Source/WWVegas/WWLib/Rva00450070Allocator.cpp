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

// Only the allocator has a matched row; instantiating vector also emits
// unrelated operations that require the unknown element's special members.
template Rva00450070Elem *_STL::allocator<Rva00450070Elem>::allocate(size_t, const void *);
