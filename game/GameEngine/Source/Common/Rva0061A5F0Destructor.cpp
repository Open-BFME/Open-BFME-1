// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x0061A5F0 (312 B), no vtable (non-
// polymorphic member/aggregate).  Reverse member unwind: thirteen
// BFMERetailAsciiString members, three opaque 0xC-byte members (the
// generic AttributeModifierAuraUpdateModuleDataMemberB pin), and one
// BigBlockReleases-style vector holder (elemsize 8, threshold 128) at
// +0x40/+0x44/+0x48.  Member types are opaque address-derived shells sized
// from the offsets with out-of-line destructors; the destructor body is
// empty and the compiler-generated reverse unwind reproduces retail
// exactly.

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

class BFMERetailAsciiString
{
public:
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
	~AttributeModifierAuraUpdateModuleDataMemberB();

private:
	char m_body[ 0xC ];
};

struct Rva0061A5F0Elem8
{
	char m_bytes[ 8 ];
};

struct Rva0061A5F0VectorHolder
{
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
	unsigned char m_unreconstructed28[ 0x2C - 0x28 ];
	AttributeModifierAuraUpdateModuleDataMemberB m_member2C;
	BFMERetailAsciiString m_str38;
	BFMERetailAsciiString m_str3C;
	Rva0061A5F0VectorHolder m_vector40;
	unsigned char m_unreconstructed4C[ 0x50 - 0x4C ];
	AttributeModifierAuraUpdateModuleDataMemberB m_member50;
	AttributeModifierAuraUpdateModuleDataMemberB m_member5C;
	unsigned char m_unreconstructed68[ 0x94 - 0x68 ];
	BFMERetailAsciiString m_str94;
};

// ??1Rva0061A5F0@@QAE@XZ
Rva0061A5F0::~Rva0061A5F0()
{
}
