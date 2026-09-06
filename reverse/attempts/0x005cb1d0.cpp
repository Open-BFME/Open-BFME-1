// ??4U1Assign_005CB1D0@@QAEAAV0@ABV0@@Z
// partial score=0.95 date=2026-09-05
// Attempt at 0x005CB1D0 (60 B), sibling of the U1_CLONE_ASSIGN family in
// Code/GameEngine/Source/Common/U1CloneAssignOperators.cpp.  Byte-identical
// to that family except the parameter's tail-subobject address is computed
// with `lea eax,[ebx+4] / push eax` instead of `add ebx,4 / push ebx`.  This
// TU tries an explicit operator= call spelling (rather than `m_tail =
// rhs.m_tail;`) to see whether that changes which register the allocator
// clobbers for the address computation.

class U1Clonable_B1D0
{
public:
	virtual ~U1Clonable_B1D0();
	virtual U1Clonable_B1D0 *clone();
};

class U1Tail_005CB1D0
{
public:
	U1Tail_005CB1D0 &operator=( const U1Tail_005CB1D0 &rhs );
};

class U1Assign_005CB1D0
{
public:
	U1Assign_005CB1D0 &operator=( const U1Assign_005CB1D0 &rhs );

	U1Clonable_B1D0 *m_held;
	U1Tail_005CB1D0 m_tail;
};

U1Assign_005CB1D0 &U1Assign_005CB1D0::operator=( const U1Assign_005CB1D0 &rhs )
{
	U1Clonable_B1D0 *source = rhs.m_held;
	U1Clonable_B1D0 *copy = source ? source->clone() : 0;
	delete m_held;
	m_held = copy;
	const U1Tail_005CB1D0 *tp = &rhs.m_tail;
	m_tail = *tp;
	return *this;
}
