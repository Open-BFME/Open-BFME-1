// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME7: STLport vector<0xB4-byte polymorphic element>::erase(first, last),
// retail 0x00363820, 80 bytes -- a byte twin of INILivingWorldPlayerArmy.cpp's
// vector<LivingWorldArmy>::erase once _STLP_NO_EXCEPTIONS is defined.  The body
// only fixes the element width (the 0xB4 stride of the destroy loop) and that
// its destructor is virtual (slot 0, deleting flag 0), so the element is an
// address-derived tag.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Rva00363820Elem
{
public:
	virtual ~Rva00363820Elem();
private:
	char m_body[ 0xB0 ];
};

template Rva00363820Elem *_STL::vector<Rva00363820Elem, _STL::allocator<Rva00363820Elem> >::erase(
	Rva00363820Elem *, Rva00363820Elem *);
