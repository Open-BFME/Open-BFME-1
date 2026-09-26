// Six __thiscall constructors that open with the vftable-plus-zeroed-dword
// head and then copy whole aggregates in behind it.
//
// Read VptrZeroPrefixCtors.cpp's header for the head itself; these are the
// same constructor with sub-objects instead of scalars.  The copies are the
// shape FunctorBindWrapperCtors.cpp landed at sixteen bytes -- an inlined
// __thiscall copy constructor whose `this` is materialised with
// `lea ecx,[eax+<offset>]` and whose dwords then move in declaration order --
// scaled to twenty-four bytes, and, in the two-argument shapes, done twice:
//
//     ...copy N bytes to +0x08... / mov edx,[esp+0xC] / ...copy N bytes to
//     +0x08+N... / pop esi / ret 8
//
// The second argument is read at [esp+0xC] rather than [esp+8] because `push
// esi` has already moved the stack; in the caller's frame the two arguments are
// adjacent dwords, so both are references and neither aggregate is passed by
// value.  The destination offsets confirm the layout: the second sub-object
// begins exactly where the first ends (+0x14 after twelve bytes at +0x08,
// +0x20 after twenty-four), so the head's two dwords and the aggregates account
// for the whole object with no padding.
//
// The aggregates are modelled as plain dword blocks because that is all the
// bytes show -- the copy is memberwise and untyped, and nothing here reveals
// what the dwords mean.  Each body is named for its own address; no class name
// has been recovered.

struct VptrZeroBlock12
{
	unsigned int m_dword_00;
	unsigned int m_dword_04;
	unsigned int m_dword_08;
};

struct VptrZeroBlock24
{
	unsigned int m_dword_00;
	unsigned int m_dword_04;
	unsigned int m_dword_08;
	unsigned int m_dword_0C;
	unsigned int m_dword_10;
	unsigned int m_dword_14;
};

class VptrZeroBlockHead
{
public:
	VptrZeroBlockHead() : m_unmodelled_04( 0 ) {}

	virtual void vptrZeroBlockAnchor();

	unsigned int m_unmodelled_04;
};

// twenty-four bytes to +0x08, ret 4
#define BFME_VPTR_ZERO_BLOCK24_CTOR( NAME )                                   \
	class NAME : public VptrZeroBlockHead                                     \
	{                                                                         \
	public:                                                                   \
		NAME( const VptrZeroBlock24 &block );                                 \
                                                                              \
		VptrZeroBlock24 m_block;                                              \
	};                                                                        \
	NAME::NAME( const VptrZeroBlock24 &block ) : m_block( block ) {}

// twelve bytes to +0x08 and twelve more to +0x14, ret 8
#define BFME_VPTR_ZERO_BLOCK12_PAIR_CTOR( NAME )                              \
	class NAME : public VptrZeroBlockHead                                     \
	{                                                                         \
	public:                                                                   \
		NAME( const VptrZeroBlock12 &first, const VptrZeroBlock12 &second );  \
                                                                              \
		VptrZeroBlock12 m_first;                                              \
		VptrZeroBlock12 m_second;                                             \
	};                                                                        \
	NAME::NAME( const VptrZeroBlock12 &first, const VptrZeroBlock12 &second )  \
		: m_first( first ), m_second( second ) {}

// twenty-four bytes to +0x08 and twenty-four more to +0x20, ret 8
#define BFME_VPTR_ZERO_BLOCK24_PAIR_CTOR( NAME )                              \
	class NAME : public VptrZeroBlockHead                                     \
	{                                                                         \
	public:                                                                   \
		NAME( const VptrZeroBlock24 &first, const VptrZeroBlock24 &second );  \
                                                                              \
		VptrZeroBlock24 m_first;                                              \
		VptrZeroBlock24 m_second;                                             \
	};                                                                        \
	NAME::NAME( const VptrZeroBlock24 &first, const VptrZeroBlock24 &second )  \
		: m_first( first ), m_second( second ) {}

BFME_VPTR_ZERO_BLOCK24_CTOR( Rva00251980VptrZeroBlockObject )
BFME_VPTR_ZERO_BLOCK24_CTOR( Rva00410750VptrZeroBlockObject )

BFME_VPTR_ZERO_BLOCK12_PAIR_CTOR( Rva00149EA0VptrZeroBlockObject )
BFME_VPTR_ZERO_BLOCK12_PAIR_CTOR( Rva001FC280VptrZeroBlockObject )

BFME_VPTR_ZERO_BLOCK24_PAIR_CTOR( Rva000C3DD0VptrZeroBlockObject )
BFME_VPTR_ZERO_BLOCK24_PAIR_CTOR( Rva00160BE0VptrZeroBlockObject )

