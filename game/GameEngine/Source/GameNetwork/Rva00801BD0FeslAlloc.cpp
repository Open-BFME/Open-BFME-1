// cl: /GX-
// Allocate counted 0x38-stride array: clear, bfmeGo929C acquire, placement-new
// Rva00802680Owner per slot. Sibling of clear@Rva00801600 at 0x00801600.

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( int size, int flags );
	virtual void release( void *block, int flags );
};

extern void *bfmeGo929C();

class Rva00802680Owner
{
public:
	Rva00802680Owner();
};

inline void *operator new( unsigned int, void *where ) { return where; }

class Rva00801600
{
public:
	void clear();
	void allocate( int count );

	Rva00802680Owner *m_array;
	int m_count;
};

void Rva00801600::allocate( int count )
{
	clear();
	m_array = (Rva00802680Owner *)((GenAlloc *)bfmeGo929C())->allocate( count * 0x38, 0 );
	for( int i = 0; i < count; ++i )
		new ( (char *)m_array + i * 0x38 ) Rva00802680Owner;
	m_count = count;
}
