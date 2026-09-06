// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x000B0DF0 (206 B).  Own vtable 0x010818CC
// installed at entry (real virtual dtor); base BfmeBaseASCa vtable
// 0x010817AC ("_bfmeVftASCa") restored automatically at the tail through an
// inline-empty base destructor.  Body: guarded notification through
// TheAudioClientUpdate (ClientSubsystem vtable slot 0x11C, already pinned
// under this exact global name/type) passing `this`, then a BigBlockReleases-
// style manual vector clear (elemsize 8, start/cap read at +0x8C/+0x94, the
// middle finish pointer at +0x90 unread, threshold 128 = STLport
// _MAX_BYTES).  Reverse member unwind: three opaque 0x10-byte members
// (already-pinned dtor thunk 0x00018E5D) at +0x60/+0x50/+0x40, two
// BFMERetailAsciiString members at +0xC/+0x8.

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

struct Rva000B0DF0Elem8
{
	char m_bytes[ 8 ];
};

class ClientSubsystem
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void unused62();
	virtual void unused63();
	virtual void unused64();
	virtual void unused65();
	virtual void unused66();
	virtual void unused67();
	virtual void unused68();
	virtual void unused69();
	virtual void unused70();
	virtual void notify( void *p );
};

extern ClientSubsystem *TheAudioClientUpdate;

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

class Gen00018E5DMember
{
public:
	~Gen00018E5DMember();

private:
	char m_body[ 0x10 ];
};

class BfmeBaseASCa
{
public:
	virtual ~BfmeBaseASCa() { }
};

struct Rva000B0DF0VectorHolder
{
	~Rva000B0DF0VectorHolder()
	{
		if ( m_start )
		{
			_STL::__node_alloc< true, 0 >::deallocate(
				m_start,
				( m_cap - m_start ) * sizeof( Rva000B0DF0Elem8 ) );
		}
	}

	Rva000B0DF0Elem8 *m_start;
	Rva000B0DF0Elem8 *m_finish;
	Rva000B0DF0Elem8 *m_cap;
};

class Rva000B0DF0 : public BfmeBaseASCa
{
public:
	virtual ~Rva000B0DF0();

private:
	unsigned char m_unreconstructed04[ 8 - 4 ];
	BFMERetailAsciiString m_str08;
	BFMERetailAsciiString m_str0C;
	unsigned char m_unreconstructed10[ 0x40 - 0x10 ];
	Gen00018E5DMember m_member40;
	Gen00018E5DMember m_member50;
	Gen00018E5DMember m_member60;
	unsigned char m_unreconstructed70[ 0x8C - 0x70 ];
	Rva000B0DF0VectorHolder m_vector8C;
};

// ??1Rva000B0DF0@@UAE@XZ
Rva000B0DF0::~Rva000B0DF0()
{
	if ( TheAudioClientUpdate )
	{
		TheAudioClientUpdate->notify( this );
	}
}
