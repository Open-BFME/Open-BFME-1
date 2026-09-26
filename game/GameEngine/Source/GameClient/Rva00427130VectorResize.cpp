// cl: /O2 /DNDEBUG /MD /EHsc
// Address-derived conversion of the one-argument Eva message-vector resize at
// 0x00427130.  The constructor at 0x004271B0 calls this entry on the
// 0x18 default-check-info vector member with 0x11.  Its 28-byte seed is the parsed
// message record: four literal head words followed by the proven 12-byte
// STLport tree header whose 24-byte sentinel allocation is visible here.

typedef unsigned int UnsignedInt;

// Existing STLport allocator body at 0x0082E540.  This is a typed use of the
// resolver's already-owned address, not a new ledger pin or alias.
namespace _STL
{
class __new_alloc
{
public:
	static void *allocate( UnsignedInt bytes );
};
}

// This declaration deliberately keeps the existing retail callee's canonical
// COFF identity.  The target body only relies on the 28-byte ABI; its local
// seed has no caller-side destructor, matching the retail epilogue.
struct BfmeSubERF
{
	void *m_header;
	UnsignedInt m_count;
	UnsignedInt m_unported;

	BfmeSubERF() : m_header( 0 )
	{
		m_header = _STL::__new_alloc::allocate( 0x18 );
		m_count = 0;
		*(unsigned char *)m_header = 0;
		((UnsignedInt *)m_header)[1] = 0;
		((UnsignedInt *)m_header)[2] = (UnsignedInt)m_header;
		((UnsignedInt *)m_header)[3] = (UnsignedInt)m_header;
	}
};

struct BfmeItemERF
{
	UnsignedInt m_head0;
	UnsignedInt m_head1;
	UnsignedInt m_head2;
	UnsignedInt m_head3;
	BfmeSubERF m_bfmeSubERF;

	BfmeItemERF()
		: m_head0( 0x4e20 ), m_head1( 0x5dc ), m_head2( 0 ), m_head3( 5 ),
		  m_bfmeSubERF()
	{
	}
	BfmeItemERF( const BfmeItemERF &that );
	~BfmeItemERF();
};

class BfmeVecERF
{
public:
	void bfmeResizeERF( UnsignedInt count, BfmeItemERF value );
};

class Rva00427130Vector
{
public:
	void resize( UnsignedInt count );
};

void Rva00427130Vector::resize( UnsignedInt count )
{
	((BfmeVecERF *)this)->bfmeResizeERF( count, BfmeItemERF() );
}
