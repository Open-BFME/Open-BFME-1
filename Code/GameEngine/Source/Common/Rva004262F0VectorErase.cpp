// cl: -GX-
// stlport
//
// Open-BFME5: STLport vector::erase(first,last) at retail 0x004262F0 (76B).
// Twin of Rva000FAF90VectorErase.cpp / ModuleFactory.cpp's
// vector<FXBoneInfo>::erase: shift-down helper call, then walk the freed
// tail calling the element destructor DIRECTLY (not through a vtable) and
// advancing by the element stride 0x1C. 0x00002BC6 also carries an
// existing "UAE" (virtual) pin under the name Gen_dtor_004255c0 from a
// different caller's speculative guess, but the retail bytes here are a
// single direct CALL with no vtable load/no `push 0` flag -- the same
// shape as the non-virtual 0x0002C3BD sibling at 0x000FAF90, not the
// scalar-deleting shape in PAVectorEraseRange003AF7A0.cpp. Declared
// non-virtual and pinned under a new, more specific name; the existing
// UAE pin for another caller is left untouched.

#include <vector>

struct Rva004262F0Elem
{
	char m_body[ 0x1C ];

	~Rva004262F0Elem();
	Rva004262F0Elem();
	Rva004262F0Elem( const Rva004262F0Elem & );
	Rva004262F0Elem &operator=( const Rva004262F0Elem & );
};

template class _STL::vector<Rva004262F0Elem>;
