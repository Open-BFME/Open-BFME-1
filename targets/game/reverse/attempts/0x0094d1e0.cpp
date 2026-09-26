// ??0Rva0094D1E0Owner@@QAE@HH@Z
// partial score=0.74 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: constructor taking (int capacity, int extra), retail
// 0x0094D1E0, 101 bytes.  Allocates a 36-byte block through the STLport
// node allocator (__node_alloc::_M_allocate thunk, ?allocate@__new_alloc),
// zero-initializes its first two fields and self-links a pointer field at
// +8 to the block's own address (an embedded sentinel), clamps the stored
// capacity to 0x800, and copies the sentinel pointer back out into a member.
// Owning class is unidentified; carries an address-derived tag.

#define _STLP_NO_EXCEPTIONS 1

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate( unsigned int n );
};
}

struct Rva0094D1E0Buffer
{
	unsigned char m_flag;
	int m_count;
	Rva0094D1E0Buffer *m_self;
	Rva0094D1E0Buffer *m_self2;
};

class Rva0094D1E0Owner
{
public:
	Rva0094D1E0Owner( int capacity, int extra );
private:
	int m_capacity;
	int m_extra;
	Rva0094D1E0Buffer *m_buffer;
	int m_zeroC;
	int m_unused10;
	Rva0094D1E0Buffer *m_field14;
	int m_field18;
	unsigned char m_flag1C;
	unsigned char m_flag1D;
};

Rva0094D1E0Owner::Rva0094D1E0Owner( int capacity, int extra ) :
	m_capacity( capacity ),
	m_extra( extra )
{
	m_buffer = 0;
	m_buffer = (Rva0094D1E0Buffer *)_STL::__new_alloc::allocate( sizeof( char[ 0x24 ] ) );
	m_zeroC = 0;
	m_buffer->m_flag = 0;
	m_buffer->m_count = 0;
	m_buffer->m_self = m_buffer;
	m_buffer->m_self2 = m_buffer;
	m_field14 = 0;
	m_field18 = 0;
	m_flag1C = 0;
	m_flag1D = 0;
	if ( m_capacity > 0x800 )
		m_capacity = 0x800;
	m_field14 = m_buffer->m_self;
}
