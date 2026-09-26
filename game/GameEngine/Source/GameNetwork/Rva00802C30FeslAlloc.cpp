// cl: /GX-
// Allocate counted 0x80-stride array: clear@Rva00802A10, Gen007EFFC0 acquire,
// placement-new element ctor at 0x00801FB0.

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( unsigned int size, int flags );
	virtual void release( void *block, int flags );
};

extern GenAlloc *Gen007EFFC0();

class Rva00801FB0Elem
{
public:
	Rva00801FB0Elem();
};

inline void *operator new( unsigned int, void *where ) { return where; }

class Rva00802A10
{
public:
	void clear();
	void allocate( int count );

	Rva00801FB0Elem *m_array;
	int m_count;
};

void Rva00802A10::allocate( int count )
{
	clear();
	m_array = (Rva00801FB0Elem *)Gen007EFFC0()->allocate( count * 0x80, 0 );
	for( int i = 0; i < count; ++i )
		new ( (char *)m_array + i * 0x80 ) Rva00801FB0Elem;
	m_count = count;
}
