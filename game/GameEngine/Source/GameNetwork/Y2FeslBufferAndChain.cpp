// EA FESL client SDK ("jabba") -- the two small container types that the
// gamebrowser bodies around them are built out of: a measure-then-allocate
// byte buffer and a singly-linked chain of allocator blocks.
//
// WHERE THE SPAN COMES FROM.  0x008002C0, the buffer's append, reports its
// overflow through the same reporter and the same file string as the rows
// U2FeslGameBrowserAsserts.cpp already landed, and that string is
// "\views\feslbuild_main\jabba\fesl\source\util.cpp" -- so these are jabba's
// utility containers, not game code.
//
// WHAT THE BYTES SHOW.  Every allocation and every release goes through a
// __cdecl getter at 0x007EFFC0 whose result is entered __thiscall with two
// dwords: slot 2 to acquire (size, 0) and slot 3 to release (block, 0).  That
// getter and those two slots are already named by the tree (see
// S3PolymorphicArrayClear.cpp), and the class spelling here matches so the pin
// resolves.
//
// The buffer keeps a pointer at +0 and a running byte count at +4, and it is
// filled in two passes: the addPadded/addString members only ADD to the count,
// and allocate() then asks for exactly that many bytes.  addPadded rounds the
// running count up to a multiple of four before adding (`neg / and 3 / add`),
// which is alignment, not arithmetic.  addString adds strlen+1 -- and adds a
// literal zero on the null path, which is why the null arm still executes an
// `add [this+4], eax`.
//
// The chain keeps a count at +0, a head at +4 and a tail at +8, and each node
// carries its successor at its own +0 with the payload immediately after: both
// append() and first() return the node address PLUS FOUR, and append() asks
// the allocator for size+4.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names either class, either
// member, or the allocator; every name below is derived from an address.  The
// two 42-byte three-field resets at 0x008003C0 and 0x00800630 are byte-equal
// apart from their call displacement, so the bytes cannot say whether they are
// one type seen twice or two types -- they are spelled as two, which is what
// two separate COMDATs in retail assert and nothing more.

#include <string.h>

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *acquire( int size, int flags );
	virtual void release( void *block, int flags );
};

extern GenAlloc *Gen007EFFC0();

// The diagnostic reporter U2FeslGameBrowserAsserts.cpp already names; 0x008002C0
// reports through its FOURTH slot with the same "\views\feslbuild_main\jabba"
// path the rest of this cluster uses, which is what places these containers in
// jabba's util.cpp.
struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expr, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

// ------------------------------------------------------------- byte buffer
class Rva00800290Buffer
{
public:
	void reset();                       // 0x00800290
	void addPadded( int size );         // 0x00800350
	void addString( const char *text );  // 0x00800370
	void allocate();                    // 0x008003A0
	void append( const char *text );    // 0x008002C0

	char *m_ptr;
	int   m_size;
};

void Rva00800290Buffer::reset()
{
	Gen007EFFC0()->release( m_ptr, 0 );
	m_ptr = 0;
	m_size = 0;
}

void Rva00800290Buffer::addPadded( int size )
{
	m_size = m_size + ( -m_size & 3 ) + size;
}

void Rva00800290Buffer::addString( const char *text )
{
	m_size += text == 0 ? 0 : (int)strlen( text ) + 1;
}

void Rva00800290Buffer::allocate()
{
	m_ptr = (char *)Gen007EFFC0()->acquire( m_size, 0 );
}

// Grow only when the text does not fit what is already there, then copy it in.
// Both the length and the copy are the /Oi inline forms, not calls.  The
// stringised condition retail reports on a failed allocation is "mBuffer",
// which is the member's REAL name -- the only name in this file that is.
void Rva00800290Buffer::append( const char *text )
{
	unsigned int length = strlen( text );

	if( length >= (unsigned int)m_size )
	{
		m_size = (int)( length + 1 );
		Gen007EFFC0()->release( m_ptr, 0 );
		m_ptr = (char *)Gen007EFFC0()->acquire( m_size, 0 );
	}
	if( m_ptr == 0 )
		Rva007EB810Get()->fail( "mBuffer",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\util.cpp", 149 );
	strcpy( m_ptr, text );
}

// ------------------------------------------------------------- block chain
struct Rva00800550Node
{
	Rva00800550Node *m_next;
};

class Rva00800550Chain
{
public:
	void  clear();              // 0x00800550
	void *append( int size );   // 0x00800590
	void *first();              // 0x008005E0
	void  popFront();           // 0x008005F0

	int              m_count;
	Rva00800550Node *m_head;
	Rva00800550Node *m_tail;
};

void Rva00800550Chain::clear()
{
	Rva00800550Node *node = m_head;

	while( node != 0 )
	{
		Rva00800550Node *next = node->m_next;
		Gen007EFFC0()->release( node, 0 );
		node = next;
	}
	m_count = 0;
	m_head = 0;
	m_tail = 0;
}

void *Rva00800550Chain::append( int size )
{
	Rva00800550Node *node = (Rva00800550Node *)Gen007EFFC0()->acquire( size + 4, 0 );

	node->m_next = 0;
	if( m_tail == 0 )
	{
		m_head = node;
		m_tail = node;
		++m_count;
	}
	else
	{
		m_tail->m_next = node;
		m_tail = node;
		++m_count;
	}
	return node + 1;
}

void *Rva00800550Chain::first()
{
	return m_count != 0 ? m_head + 1 : 0;
}

void Rva00800550Chain::popFront()
{
	if( m_head != 0 )
	{
		Rva00800550Node *next = m_head->m_next;
		Gen007EFFC0()->release( m_head, 0 );
		m_head = next;
		if( next == 0 )
			m_tail = 0;
		--m_count;
	}
}

// ------------------------------------ the two byte-equal three-field resets
class Rva008003C0Owner
{
public:
	void clear();               // 0x008003C0

	void *m_block;
	int   m_field4;
	int   m_field8;
};

void Rva008003C0Owner::clear()
{
	Gen007EFFC0()->release( m_block, 0 );
	m_block = 0;
	m_field4 = 0;
	m_field8 = 0;
}

class Rva00800630Owner
{
public:
	void clear();               // 0x00800630

	void *m_block;
	int   m_field4;
	int   m_field8;
};

void Rva00800630Owner::clear()
{
	Gen007EFFC0()->release( m_block, 0 );
	m_block = 0;
	m_field4 = 0;
	m_field8 = 0;
}

// ------------------------------------------------ 0x008014F0, a lone thunk
// It loads its `this` from [esp+4] rather than using ecx and returns `ret 4`,
// so it is NOT a __thiscall member: it is a one-pointer __stdcall function
// whose whole body is the hpstate setter at 0x008022A0 with a zero.  The
// callee is only DECLARED here -- retail's `call` proves it stayed opaque, and
// defining it in this translation unit would inline it away.
class Rva008022A0Owner
{
public:
	void setHpState( int state );   // 0x008022A0

	int m_field0;
	int m_field4;
	int m_field8;
	int m_hpState;
};

void __stdcall Rva008014F0ResetHpState( Rva008022A0Owner *owner )
{
	owner->setHpState( 0 );
}

// --------------------------------------------- 0x00802DF0, a two-field fill
// Two char arrays 0x80 apart in the source record are appended into two
// buffers; the dword the record starts with lands at +0x08.
struct Rva00802DF0Source
{
	int  m_field0;
	char m_pad004[ 8 ];
	char m_name[ 0x80 ];        // +0x0C
	char m_text[ 1 ];           // +0x8C
};

class Rva00802DF0Owner
{
public:
	void set( Rva00802DF0Source *source, int value );   // 0x00802DF0

	int               m_field0;
	int               m_field4;
	int               m_field8;
	Rva00800290Buffer m_name;   // +0x0C
	Rva00800290Buffer m_text;   // +0x14
};

void Rva00802DF0Owner::set( Rva00802DF0Source *source, int value )
{
	m_field4 = value;
	m_name.append( source->m_name );
	m_text.append( source->m_text );
	m_field8 = source->m_field0;
}
