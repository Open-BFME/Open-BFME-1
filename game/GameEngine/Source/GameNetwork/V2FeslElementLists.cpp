// EA FESL client SDK ("jabba") -- three sibling element-list setters.
//
// Same translation-unit cluster as V2FeslTxnRequests.cpp.
//
// WHAT THE BYTES SHOW.  The three rows at 0x007F8200, 0x007F82A0 and 0x007F8340
// are 148 bytes each and differ in exactly FIFTEEN bytes: two member
// displacements and the position-dependent halves of three relative calls.
// Every call target is identical, including the element method at 0x008002C0.
// The only real axis is the member pair:
//     0x007F8200   0x2A8 / 0x2C0
//     0x007F82A0   0x2B0 / 0x2C8
//     0x007F8340   0x2B8 / 0x2D0
// so the owner carries three of each block, eight bytes apart, and each row
// drives one pair.  That is the whole family.
//
// The FIRST block of each pair is filled by a real CALL to 0x007F7F50, which
// V2FeslArrayBlocks.cpp claims as Rva007F78E0Block::allocate -- so that member
// keeps its out-of-line definition and is only declared here.  The SECOND block
// is filled INLINE with the exact clear-then-allocate sequence that
// V2FeslArrayBlocks.cpp claims out of line at 0x007F7860 / 0x007F7890: same
// null-guarded release, same `[block]=0` inside the guard and `[count]=0`
// outside it, same `count*8` allocate.  One shape appears in retail both as a
// call and inlined, which is what a member defined in the class body does, so it
// is spelled __forceinline here under its own name -- this file does not
// redefine the copy the other file already claims.
//
// The loop bounds-tests the index against the FIRST block's count and yields a
// null element pointer past the end (the `jl` reaches the address computation),
// exactly the accessor V2FeslBrowserRecords.cpp shows on the browser arrays.
//
// WHAT THE BYTES CANNOT DECIDE.  Nothing names the owner, the three block pairs,
// the element method, or what the incoming pointer array holds.  All names are
// address-derived.

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( unsigned int size, int flags );
	virtual void release( void *block, int flags );
};

extern GenAlloc *Gen007EFFC0();

struct Gen_dtor_007f6d20
{
	void attach( void *item );                                        // 0x008002C0
	int m_a;
	int m_b;
};

class Rva007F78E0Block
{
public:
	void allocate( int count );                                       // 0x007F7F50
	Gen_dtor_007f6d20 *m_data;
	int m_count;
};

// Same two-field shape V2FeslArrayBlocks.cpp claims out of line at 0x007F7860
// and 0x007F7890; here it is the inline copy the three rows below fold in.
class Rva007F8200InlineBlock
{
public:
	__forceinline void clear()
	{
		if( m_data )
		{
			Gen007EFFC0()->release( m_data, 0 );
			m_data = 0;
		}
		m_count = 0;
	}

	__forceinline void allocate( int count )
	{
		clear();
		m_data = Gen007EFFC0()->allocate( count * 8, 0 );
		m_count = count;
	}

	void *m_data;
	int m_count;
};

class Rva007F8200Owner
{
public:
	void setList0( void **items, int count );
	void setList1( void **items, int count );
	void setList2( void **items, int count );

	char m_head[ 0x2A8 ];
	Rva007F78E0Block m_elements0;
	Rva007F78E0Block m_elements1;
	Rva007F78E0Block m_elements2;
	Rva007F8200InlineBlock m_items0;
	Rva007F8200InlineBlock m_items1;
	Rva007F8200InlineBlock m_items2;
};

void Rva007F8200Owner::setList0( void **items, int count )
{
	Rva007F78E0Block *elements = &m_elements0;

	elements->allocate( count );
	m_items0.allocate( count );
	for( int i = 0; i < count; ++i )
	{
		Gen_dtor_007f6d20 *element = ( i >= elements->m_count )
			? 0
			: &elements->m_data[ i ];
		element->attach( items[ i ] );
	}
}

void Rva007F8200Owner::setList1( void **items, int count )
{
	Rva007F78E0Block *elements = &m_elements1;

	elements->allocate( count );
	m_items1.allocate( count );
	for( int i = 0; i < count; ++i )
	{
		Gen_dtor_007f6d20 *element = ( i >= elements->m_count )
			? 0
			: &elements->m_data[ i ];
		element->attach( items[ i ] );
	}
}

void Rva007F8200Owner::setList2( void **items, int count )
{
	Rva007F78E0Block *elements = &m_elements2;

	elements->allocate( count );
	m_items2.allocate( count );
	for( int i = 0; i < count; ++i )
	{
		Gen_dtor_007f6d20 *element = ( i >= elements->m_count )
			? 0
			: &elements->m_data[ i ];
		element->attach( items[ i ] );
	}
}

