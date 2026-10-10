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

// ILT 0x1811A reaches the existing 60-byte construction body at 0x1C3E00.
// It constructs the two snapshot subobjects, rather than calling an opaque
// element copy constructor whose symbol has no retail binding.
struct BfmeThingCNI;
void __cdecl bfmeCopyCNI(BfmeThingCNI *, BfmeThingCNI *);

namespace _STL
{
template <>
__forceinline void _Construct(Rva001D28F0Element *destination,
    const Rva001D28F0Element &value)
{
    bfmeCopyCNI(reinterpret_cast<BfmeThingCNI *>(destination),
        reinterpret_cast<BfmeThingCNI *>(const_cast<Rva001D28F0Element *>(&value)));
}
}

template void _STL::vector<Rva001D28F0Element>::_M_insert_overflow(
    Rva001D28F0Element *, const Rva001D28F0Element &,
    const _STL::__false_type &, unsigned int, bool);
