// cl: /EHsc

extern void ( __cdecl *g_Va01337830 )( void *storage, unsigned int size );
extern void __cdecl Rva00897330NotifyFree( void *storage );

class Rva00892ED0Base
{
public:
	virtual ~Rva00892ED0Base() {}

	static void operator delete( void *storage, unsigned int size )
	{
		Rva00897330NotifyFree( storage );
		g_Va01337830( (char *)storage - 8, size + 8 );
	}
};

struct Rva00892ED0ReferenceCount
{
	unsigned short m_count;
};

extern void ( __cdecl **Rva00892ED0ReleaseTable )( void * );

class Rva00892ED0Reference
{
public:
	~Rva00892ED0Reference()
	{
		Rva00892ED0ReferenceCount *reference = m_reference;
		--reference->m_count;
		if( reference->m_count == 0 )
			Rva00892ED0ReleaseTable[ 1 ]( reference );
	}

	Rva00892ED0ReferenceCount *m_reference;
};

class BfmeObj4310
{
public:
	void bfmeCleanup( int mode );
};

class BfmeNodeEA;
extern void __cdecl bfmeUnlink( BfmeNodeEA *node );

class Rva00892ED0HeaderedDeleting : public Rva00892ED0Base
{
public:
	virtual ~Rva00892ED0HeaderedDeleting();

	unsigned int m_flags;
	void *m_slot;
	Rva00892ED0Reference m_reference;
	char m_gap10[ 0x48 - 0x10 ];
	void *m_block;
	char m_gap4c[ 0x60 - 0x4c ];
	unsigned int m_state;
};

Rva00892ED0HeaderedDeleting::~Rva00892ED0HeaderedDeleting()
{
	void *block = m_block;

	if( block != 0 )
	{
		g_Va01337830( block, 0x30 );
		m_block = 0;
	}

	((BfmeObj4310 *)this)->bfmeCleanup( 0 );

	if( (m_state & 0xc0000) != 0x40000 )
		bfmeUnlink( (BfmeNodeEA *)this );
}
