// cl: -GX- /MD
// stlport

#include <algorithm>

// Retail 0x00260850 (97 bytes, reached only through ILT 0x0002AD74): STLport
// _STL::__median over a plain function-pointer comparator that takes both
// elements by reference -- each call pushes the element addresses themselves
// and returns one of the three addresses.  Nothing calls the ILT, so the
// element type is not recovered and is named for the address.

struct Rva00260850Elem
{
	int m_value;
};

typedef bool (__cdecl *Rva00260850Less)(const Rva00260850Elem &, const Rva00260850Elem &);

template const Rva00260850Elem &_STL::__median<Rva00260850Elem, Rva00260850Less>(
	const Rva00260850Elem &, const Rva00260850Elem &, const Rva00260850Elem &, Rva00260850Less);
