// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00181DF0: virtual destructor of the owner that lazily holds the
// 0x1C inner at +0x54.  Guarded delete of that pointer, then the inlined
// destructor of a 12-byte-element vector at +0x44, then the base destructor.

void __cdecl bfmeFreeScalar( void *block );
void __cdecl bfmeDeallocate( void *block, unsigned int bytes );

inline void bfmeRelease( void *block, unsigned int bytes )
{
	if ( bytes > 0x80 )
		bfmeFreeScalar( block );
	else
		bfmeDeallocate( block, bytes );
}

struct Rva00181DF0Elem
{
	int m_0;
	int m_1;
	int m_2;
};

class Rva00181DF0Vec
{
public:
	~Rva00181DF0Vec()
	{
		Rva00181DF0Elem *start = m_start;

		if ( start )
			bfmeRelease( start, sizeof( Rva00181DF0Elem ) * ( m_end - start ) );
	}

	Rva00181DF0Elem *m_start;
	Rva00181DF0Elem *m_finish;
	Rva00181DF0Elem *m_end;
};

struct Rva00181DF0Owned
{
	virtual ~Rva00181DF0Owned();
};

struct Rva00031D5ETailBase
{
	virtual ~Rva00031D5ETailBase();
};

class Rva00181DF0Owner : public Rva00031D5ETailBase
{
public:
	virtual ~Rva00181DF0Owner();

private:
	char m_pad[ 0x40 ];
	Rva00181DF0Vec m_vec;
	char m_gap[ 4 ];
	Rva00181DF0Owned *m_inner;
};

Rva00181DF0Owner::~Rva00181DF0Owner()
{
	if ( m_inner != 0 )
	{
		delete m_inner;
		m_inner = 0;
	}
}
