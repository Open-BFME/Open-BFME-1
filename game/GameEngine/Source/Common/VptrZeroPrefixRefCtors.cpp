// Three __thiscall constructors that open with the vftable-plus-zeroed-dword
// head and then take a reference on each pointer they copy in.
//
// Read VptrZeroPrefixCtors.cpp's header for the head.  Per pointer, retail is
//
//     mov ecx,[<src>] / test ecx,ecx / mov [eax+<off>],ecx / jz +3 /
//     inc dword ptr [ecx+4]
//
// -- the pointer is stored unconditionally and the increment is skipped when it
// is null, which is a copied smart pointer, not an ownership transfer.  The
// counter is a dword at +0x04 of the POINTEE and is raised with `inc`, so it is
// a plain non-atomic reference count; there is no interlocked form and no
// release of a previous value, both of which a constructor would not need.
//
// The two-pointer body reads its source at +0x00 and +0x04 from one dword
// argument and fills +0x08 and +0x0C; the one-pointer body reads +0x00 and
// fills +0x08.  Both dereference the argument rather than storing it, so the
// argument is a reference to the pair (or the single pointer) and not the
// pointer itself -- the same reading that separates the 27-byte and 25-byte
// wrapper constructors in FunctorBindSlotWrapperCtors.cpp and
// FunctorBindValueWrapperCtors.cpp.
//
// The pointee is modelled with one unmodelled dword ahead of the counter
// because +0x04 is where the increment lands and nothing here shows what +0x00
// holds.  Each body is named for its own address; no class name has been
// recovered.

struct VptrZeroRefCounted
{
	void         *m_unmodelled_00;
	unsigned int  m_refCount;
};

struct VptrZeroRefOne
{
	VptrZeroRefCounted *m_first;
};

struct VptrZeroRefPair
{
	VptrZeroRefCounted *m_first;
	VptrZeroRefCounted *m_second;
};

class VptrZeroRefHead
{
public:
	VptrZeroRefHead() : m_unmodelled_04( 0 ) {}

	virtual void vptrZeroRefAnchor();

	unsigned int m_unmodelled_04;
};

#define BFME_VPTR_ZERO_REF_ONE_CTOR( NAME )                                   \
	class NAME : public VptrZeroRefHead                                       \
	{                                                                         \
	public:                                                                   \
		NAME( const VptrZeroRefOne &source );                                 \
                                                                              \
		VptrZeroRefCounted *m_first;                                          \
	};                                                                        \
	NAME::NAME( const VptrZeroRefOne &source )                                \
	{                                                                         \
		m_first = source.m_first;                                             \
		if ( m_first != 0 )                                                   \
			m_first->m_refCount++;                                            \
	}

#define BFME_VPTR_ZERO_REF_PAIR_CTOR( NAME )                                  \
	class NAME : public VptrZeroRefHead                                       \
	{                                                                         \
	public:                                                                   \
		NAME( const VptrZeroRefPair &source );                                \
                                                                              \
		VptrZeroRefCounted *m_first;                                          \
		VptrZeroRefCounted *m_second;                                         \
	};                                                                        \
	NAME::NAME( const VptrZeroRefPair &source )                               \
	{                                                                         \
		m_first = source.m_first;                                             \
		if ( m_first != 0 )                                                   \
			m_first->m_refCount++;                                            \
		m_second = source.m_second;                                           \
		if ( m_second != 0 )                                                  \
			m_second->m_refCount++;                                           \
	}

BFME_VPTR_ZERO_REF_PAIR_CTOR( Rva004C5EA0VptrZeroRefObject )
BFME_VPTR_ZERO_REF_PAIR_CTOR( Rva004C5FB0VptrZeroRefObject )

BFME_VPTR_ZERO_REF_ONE_CTOR( Rva004C5F60VptrZeroRefObject )

struct Rva004C5CE0RefCounted
{
	virtual void release( int deletingFlag );

	int m_refCount;
};

class Rva004C5CE0Reference
{
public:
	Rva004C5CE0Reference( Rva004C5CE0RefCounted *value ) : m_value( value ) {}
	Rva004C5CE0Reference( const Rva004C5CE0Reference &other );
	~Rva004C5CE0Reference();

	Rva004C5CE0RefCounted *m_value;
};

Rva004C5CE0Reference::Rva004C5CE0Reference( const Rva004C5CE0Reference &other ) :
	m_value( other.m_value )
{
	if ( m_value != 0 )
		m_value->m_refCount++;
}

Rva004C5CE0Reference::~Rva004C5CE0Reference()
{
	if ( m_value != 0 && --m_value->m_refCount <= 0 )
		m_value->release( 1 );
}

class Rva004C5CE0ReferenceHolder
{
public:
	Rva004C5CE0ReferenceHolder( Rva004C5CE0Reference value );

	Rva004C5CE0Reference m_value;
};

Rva004C5CE0ReferenceHolder::Rva004C5CE0ReferenceHolder( Rva004C5CE0Reference value ) :
	m_value( value )
{
}
