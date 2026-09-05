// cl: -GX-
// stlport
//
// Open-BFME5: STLport vector::erase(first,last) at retail 0x000FAF90 (76B).
// Same shape as PAVectorEraseRange003AF7A0.cpp (0x003AF7A0): shift-down
// helper call, then walk the freed tail calling the element destructor
// directly (not through a vtable) and advancing by the element stride.
// Stride here is 0x60, and the destructor is non-virtual -- the pin
// ??1BfmeVecElem_000FAFF0@@QAE@XZ (0x0002C3BD, "QAE" = public non-virtual)
// used by the sibling vector-destroy at 0x000FAFF0
// (Bfme5VectorDestroysWide.cpp) confirms the shape. Address-derived element
// name kept local to this TU to avoid a cross-TU duplicate definition.

#include <vector>

struct BfmeVecElem_000FAFF0
{
	char m_body[ 0x60 ];

	~BfmeVecElem_000FAFF0();
	BfmeVecElem_000FAFF0();
	BfmeVecElem_000FAFF0( const BfmeVecElem_000FAFF0 & );
	BfmeVecElem_000FAFF0 &operator=( const BfmeVecElem_000FAFF0 & );
};

template class _STL::vector<BfmeVecElem_000FAFF0>;
