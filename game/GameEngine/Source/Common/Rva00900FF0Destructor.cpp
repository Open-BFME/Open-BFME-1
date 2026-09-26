// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the 0x00900FF0 destructor owns five nested vectors and one
// scalar vector. The retail destructor releases its reference before it
// clears the nested vectors, then resets the common base state.

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
	virtual void Delete_This();

	void Release_Ref( void )
	{
		if ( --m_refCount == 0 )
			Delete_This();
	}

	long m_refCount;
};

class Rva00900FF0InnerVector
{
public:
	~Rva00900FF0InnerVector();

	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

class Rva00900FF0VecOfVec
{
public:
	~Rva00900FF0VecOfVec();

	void erase( Rva00900FF0InnerVector *first, Rva00900FF0InnerVector *last );
	void clear( void )
	{
		Rva00900FF0InnerVector *last = m_finish;
		Rva00900FF0InnerVector *first = m_start;
		erase( first, last );
	}

	Rva00900FF0InnerVector *m_start;
	Rva00900FF0InnerVector *m_finish;
	Rva00900FF0InnerVector *m_endOfStorage;
};

struct Rva00900FF0Elem4
{
	char m_bytes[ 4 ];
};

extern void *(__cdecl *bfmeMemCopy)( void *destination, const void *source, unsigned int bytes );

inline Rva00900FF0Elem4 *bfmeCopyRange( Rva00900FF0Elem4 *destination, Rva00900FF0Elem4 *first, Rva00900FF0Elem4 *last )
{
	if ( first == last )
		return destination;

	unsigned int bytes = (char *)last - (char *)first;
	return (Rva00900FF0Elem4 *)((char *)bfmeMemCopy( destination, first, bytes ) + bytes);
}

struct Rva00900FF0VectorHolder
{
	void clear( void )
	{
		m_finish = bfmeCopyRange( m_start, m_finish, m_finish );
	}

	~Rva00900FF0VectorHolder()
	{
		Rva00900FF0Elem4 *start = m_start;
		if ( start )
		{
			unsigned int bytes = (m_endOfStorage - start) * sizeof( Rva00900FF0Elem4 );
			_STL::__node_alloc< true, 0 >::deallocate( start, bytes );
		}
	}

	Rva00900FF0Elem4 *m_start;
	Rva00900FF0Elem4 *m_finish;
	Rva00900FF0Elem4 *m_endOfStorage;
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
	virtual void slot();
	~BfmeThingUB();

	void bfmeResetUB( void );

	unsigned char m_bfmeGap[ 8 ];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap10[ 4 ];
};

class Rva00900FF0 : public BfmeThingUB
{
public:
	virtual ~Rva00900FF0();

private:
	StringClass m_str14;
	StringClass m_str18;
	Rva00900FF0VecOfVec m_vec1C;
	Rva00900FF0VecOfVec m_vec28;
	Rva00900FF0VecOfVec m_vec34;
	Rva00900FF0VecOfVec m_vec40;
	Rva00900FF0VecOfVec m_vec4C;
	Rva00900FF0VectorHolder m_vector58;
	unsigned char m_unreconstructed64[ 0x70 - 0x64 ];
	Counted *m_countedPtr70;
};

Rva00900FF0::~Rva00900FF0()
{
	if ( m_countedPtr70 )
		m_countedPtr70->Release_Ref();

	m_vec1C.clear();
	m_vec28.clear();
	m_vec34.clear();
	m_vec40.clear();
	m_vec4C.clear();
	m_vector58.clear();
}
