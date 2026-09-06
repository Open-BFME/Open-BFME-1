// ??1Rva00900FF0@@UAE@XZ
// partial score=0.25 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x00900FF0 (366 B).  Own vtable 0x01139068
// installed at entry.  Body: release a ref-counted object at +0x70
// (Counted/Release_Ref shape, matching AudioEventRTSDtor.cpp's already
// established pattern), erase() five vector<vector<ICoord2D>> members at
// +0x1C/+0x28/+0x34/+0x40/+0x4C (the real matched
// vector<vector<ICoord2D>>::erase(first,last), STLport's generic
// begin()..end() erase idiom), a vector<T> clear+deallocate at +0x58/+0x5C/
// +0x60 (BigBlockReleases-style, elemsize 4), then destroys the five
// vector-of-vector shells through the matched BfmeDtorMemberB pin, two
// StringClass members via the matched Free_String, and finally calls
// bfmeResetUB (BfmeThreeHundredFiftyThree.cpp's already matched manual
// vft-store idiom) explicitly on `this`.  Member types are opaque
// address-derived shells sized from the offsets with out-of-line
// destructors except the named real callees.

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

class Counted
{
public:
	virtual ~Counted();

	void Release_Ref( void )
	{
		if ( --m_refCount == 0 )
			delete this;
	}

	long m_refCount;
};

class CountedPtr
{
public:
	~CountedPtr()
	{
		if ( m_ptr )
			m_ptr->Release_Ref();
	}

private:
	Counted *m_ptr;
};

class Rva00900FF0VecOfVec
{
public:
	~Rva00900FF0VecOfVec();

	void *erase( void *first, void *last );

	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

struct Rva00900FF0Elem4
{
	char m_bytes[ 4 ];
};

struct Rva00900FF0VectorHolder
{
	~Rva00900FF0VectorHolder()
	{
		char *start = m_start;
		unsigned int count = m_endOfStorage - start;

		if ( start )
		{
			_STL::__node_alloc< true, 0 >::deallocate( start, count );
		}
	}

	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

class StringClass
{
public:
	~StringClass()
	{
		Free_String();
	}

	void Free_String( void );

private:
	char *m_buffer;
};

class BfmeThingUB
{
public:
	void bfmeResetUB( void );
};

class Rva00900FF0
{
public:
	virtual ~Rva00900FF0();

private:
	unsigned char m_unreconstructed04[ 0x14 - 4 ];
	StringClass m_str14;
	StringClass m_str18;
	Rva00900FF0VecOfVec m_vec1C;
	Rva00900FF0VecOfVec m_vec28;
	Rva00900FF0VecOfVec m_vec34;
	Rva00900FF0VecOfVec m_vec40;
	Rva00900FF0VecOfVec m_vec4C;
	Rva00900FF0VectorHolder m_vector58;
	unsigned char m_unreconstructed64[ 0x70 - 0x64 ];
	CountedPtr m_countedPtr70;
};

// ??1Rva00900FF0@@UAE@XZ
Rva00900FF0::~Rva00900FF0()
{
	m_vec1C.erase( m_vec1C.m_start, m_vec1C.m_finish );
	m_vec28.erase( m_vec28.m_start, m_vec28.m_finish );
	m_vec34.erase( m_vec34.m_start, m_vec34.m_finish );
	m_vec40.erase( m_vec40.m_start, m_vec40.m_finish );
	m_vec4C.erase( m_vec4C.m_start, m_vec4C.m_finish );

	reinterpret_cast< BfmeThingUB * >( this )->bfmeResetUB();
}
