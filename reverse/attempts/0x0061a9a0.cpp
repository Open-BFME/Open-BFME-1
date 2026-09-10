// ??0Rva0061A5F0@@QAE@ABVAsciiString@@@Z
// partial score=0.97 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x0061A5F0 (312 B) and its paired
// constructor at 0x0061A9A0 (314 B), both on the same non-polymorphic
// 0x98-byte aggregate: thirteen BFMERetailAsciiString members, three
// opaque 0xC-byte vector-like members, and one BigBlockReleases-style
// vector holder (elemsize 8, threshold 128) at +0x40/+0x44/+0x48.

namespace _STL
{

template <bool __threads, int __inst>
class __node_alloc
{
	static void _M_deallocate( void *p, unsigned int n );

public:
	static void deallocate( void *p, unsigned int n )
	{
		if ( n > 128 )
			::operator delete( p );
		else
			_M_deallocate( p, n );
	}
};

}

class AsciiString;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data( 0 ) {}
	BFMERetailAsciiString( const char *text );
	BFMERetailAsciiString( const AsciiString &other );

	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	void releaseBuffer( void );

private:
	char *m_data;
};

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	AttributeModifierAuraUpdateModuleDataMemberB() : m_begin( 0 ), m_end( 0 ), m_capacity( 0 ) {}
	~AttributeModifierAuraUpdateModuleDataMemberB();

	void clear( void )
	{
		erase( m_begin, m_end );
	}

private:
	void *erase( void *first, void *last );

	void *m_begin;
	void *m_end;
	void *m_capacity;
};

struct Rva0061A5F0Elem8
{
	char m_bytes[ 8 ];
};

struct Rva0061A5F0VectorHolder
{
	Rva0061A5F0VectorHolder() : m_start( 0 ), m_finish( 0 ), m_cap( 0 ) {}

	~Rva0061A5F0VectorHolder()
	{
		if ( m_start )
		{
			_STL::__node_alloc< true, 0 >::deallocate(
				m_start,
				( m_cap - m_start ) * sizeof( Rva0061A5F0Elem8 ) );
		}
	}

	Rva0061A5F0Elem8 *m_start;
	Rva0061A5F0Elem8 *m_finish;
	Rva0061A5F0Elem8 *m_cap;
};

class Rva0061A5F0
{
public:
	Rva0061A5F0( const AsciiString &name );
	~Rva0061A5F0();

private:
	BFMERetailAsciiString m_str00;
	BFMERetailAsciiString m_str04;
	BFMERetailAsciiString m_str08;
	BFMERetailAsciiString m_str0C;
	BFMERetailAsciiString m_str10;
	BFMERetailAsciiString m_str14;
	BFMERetailAsciiString m_str18;
	BFMERetailAsciiString m_str1C;
	BFMERetailAsciiString m_str20;
	BFMERetailAsciiString m_str24;
	volatile unsigned int m_unreconstructed28;
	AttributeModifierAuraUpdateModuleDataMemberB m_member2C;
	BFMERetailAsciiString m_str38;
	BFMERetailAsciiString m_str3C;
	Rva0061A5F0VectorHolder m_vector40;
	unsigned char m_flag4C;
	AttributeModifierAuraUpdateModuleDataMemberB m_member50;
	AttributeModifierAuraUpdateModuleDataMemberB m_member5C;
	int m_value68;
	int m_value6C;
	unsigned char m_value70;
	int m_value74;
	int m_value78;
	int m_value7C;
	unsigned char m_value80;
	int m_value84;
	unsigned char m_value88;
	int m_value8C;
	int m_value90;
	BFMERetailAsciiString m_str94;
};

// ??0Rva0061A5F0@@QAE@ABVAsciiString@@@Z
Rva0061A5F0::Rva0061A5F0( const AsciiString &name )
	: m_str00( name ),
	  m_str04(),
	  m_str08( "APT:LivingWorldRegionConqueredNotice" ),
	  m_str0C(),
	  m_str10(),
	  m_str14(),
	  m_str18(),
	  m_str1C(),
	  m_str20(),
	  m_str24(),
	  m_unreconstructed28( 0 ),
	  m_member2C(),
	  m_str38(),
	  m_str3C(),
	  m_vector40(),
	  m_flag4C( 1 ),
	  m_member50(),
	  m_member5C(),
	  m_value68( 0 ),
	  m_value6C( 0 ),
	  m_value70( 0 ),
	  m_value74( 0 ),
	  m_value78( 0 ),
	  m_value7C( 0 ),
	  m_value80( 0 ),
	  m_value84( 0 ),
	  m_value88( 0 ),
	  m_value8C( 0 ),
	  m_value90( 0 ),
	  m_str94()
{
	m_member2C.clear();
	{
		Rva0061A5F0Elem8 *dst = m_vector40.m_start;
		Rva0061A5F0Elem8 *last = m_vector40.m_finish;
		int count = m_vector40.m_finish - last;
		for ( ; count > 0; --count )
		{
			*dst = *last;
			++last;
			++dst;
		}
		m_vector40.m_finish = dst;
	}
	m_member50.clear();
	m_member5C.clear();
}

// ??1Rva0061A5F0@@QAE@XZ
Rva0061A5F0::~Rva0061A5F0()
{
}
