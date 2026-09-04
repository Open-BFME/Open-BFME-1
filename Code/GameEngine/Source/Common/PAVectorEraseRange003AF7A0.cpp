// cl: -GX-
// stlport
//
// Open-BFME5: STLport vector::erase(first,last) at retail 0x003AF7A0 (77B).
// Same shape as PAVectorEraseRange.cpp (0x00147180): virtual element dtor
// called as scalar-deleting with 0, then add esi, element-size. Stride here
// is 8. Not ICF with the 0x5C-element PA twin (different imm in the loop).

#include <vector>

struct Elem003AF7A0
{
	virtual ~Elem003AF7A0();

	char m_body[ 8 - 4 ];

	Elem003AF7A0();
	Elem003AF7A0( const Elem003AF7A0 & );
	Elem003AF7A0 &operator=( const Elem003AF7A0 & );
};

template class _STL::vector<Elem003AF7A0>;
