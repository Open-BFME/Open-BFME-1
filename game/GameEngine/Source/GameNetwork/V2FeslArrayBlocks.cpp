// cl: /GX-
// EA FESL client SDK ("jabba") -- allocator-backed element blocks.
//
// Same translation-unit cluster as V2FeslTxnRequests.cpp; see that file's head
// comment for how the span was identified.
// `/GX-` is required because retail calls both nontrivial member constructors
// without installing a constructor-unwind frame.
//
// WHAT THE BYTES SHOW.  Every row here reaches its storage through the same
// __cdecl getter at RVA 0x007EFFC0 that game/GameEngine/Source/Common/
// S3PolymorphicArrayClear.cpp already names Gen007EFFC0, and drives the object
// it returns through its vtable.  Two slots are used:
//     [vptr+0x08]  entered __thiscall with (size, 0) and its eax kept as a
//                  pointer -- an ALLOCATE
//     [vptr+0x0C]  entered __thiscall with (block, flag) and no result used -- a
//                  RELEASE, which is the slot S3PolymorphicArrayClear.cpp
//                  already spells as `release`
// This file therefore refines that file's placeholder `v2` into an allocating
// slot; it does not contradict it, and it does not land over it.  The class
// name GenAlloc is kept so the existing Gen007EFFC0 pin resolves; the slots are
// virtual calls and need no symbol at all.
//
// The BLOCK objects are all two fields, a pointer at +0 and a count at +4.  The
// evidence for each element STRIDE is an immediate with no relocation: an
// `imul ecx,ecx,0x1C`, a `shl ecx,6`, a `lea ecx,[edi*8]`.  Where a stride-8
// block frees its elements it calls RVA 0x00800290 once per element with the
// element address in ecx and nothing pushed -- a destructor, which is what the
// tree already pins that address as.
//
// Where an allocate is followed by a per-element `if (p) ctor(p)` the null test
// is MSVC's placement-new codegen, so those loops are spelled as placement new.
//
// WHAT THE BYTES CANNOT DECIDE.  Nothing names the block types, the element
// types, or the owners.  Rows 0x007F6CF0 and 0x007F7860 are the same body twice
// under two different call sites; the bytes do not say the two owners are
// related.  All names here are address-derived.

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( unsigned int size, int flags );
	virtual void release( void *block, int flags );
};

extern GenAlloc *Gen007EFFC0();

// The two array objects game/GameEngine/Source/Common/S3PolymorphicArrayClear.cpp
// already claims a `clear` on, redeclared here so their existing symbols resolve.
class Rva007F6BA0
{
public:
	void clear();                                                     // 0x007F6BA0
	void *m_array;
	int m_count;
};

class Rva007F6C60
{
public:
	void clear();                                                     // 0x007F6C60
	void *m_array;
	int m_count;
};

struct Gen_dtor_007f6d20
{
	Gen_dtor_007f6d20();                                              // 0x00800280
	virtual ~Gen_dtor_007f6d20();                                     // 0x00800290
	int m_pad;
};

struct V2ZeroInt
{
	__forceinline V2ZeroInt() : m_value(0) {}
	int m_value;
};

struct Rva00802E70Element
{
	__declspec(noinline) Rva00802E70Element();                        // 0x00802E70
	virtual void slot();
	int m_value04;
	V2ZeroInt m_value08;
	Gen_dtor_007f6d20 m_value0c;
	Gen_dtor_007f6d20 m_value14;
};

struct Rva00802D00Element
{
	__declspec(noinline) Rva00802D00Element();                        // 0x00802D00
	virtual void slot();
	int m_value04;
	V2ZeroInt m_value08;
	Gen_dtor_007f6d20 m_value0c;
	Gen_dtor_007f6d20 m_value14;
	int m_value1c;
	int m_value20;
	int m_value24;
	int m_value28;
	int m_value2c;
	int m_value30;
	int m_value34;
	int m_value38;
	int m_value3c;
};

inline void *operator new( unsigned int, void *where ) { return where; }

// -------------------------------------------------- plain release-and-clear
class Rva007F6CF0Block
{
public:
	void clear();
	void *m_data;
	int m_count;
};

void Rva007F6CF0Block::clear()
{
	if( m_data )
	{
		Gen007EFFC0()->release( m_data, 0 );
		m_data = 0;
	}
	m_count = 0;
}

class Rva007F7860Block
{
public:
	void clear();
	void allocate( int count );
	void *m_data;
	int m_count;
};

void Rva007F7860Block::clear()
{
	if( m_data )
	{
		Gen007EFFC0()->release( m_data, 0 );
		m_data = 0;
	}
	m_count = 0;
}

void Rva007F7860Block::allocate( int count )
{
	clear();
	m_data = Gen007EFFC0()->allocate( count * 8, 0 );
	m_count = count;
}

// ------------------------------------- stride-8 block that destroys elements
class Rva007F78E0Block
{
public:
	void clear();
	void allocate( int count );
	Gen_dtor_007f6d20 *m_data;
	int m_count;
};

void Rva007F78E0Block::clear()
{
	if( m_data )
	{
		for( int i = 0; i < m_count; ++i )
			m_data[ i ].Gen_dtor_007f6d20::~Gen_dtor_007f6d20();
		Gen007EFFC0()->release( m_data, 0 );
		m_data = 0;
	}
	m_count = 0;
}

void Rva007F78E0Block::allocate( int count )
{
	clear();
	m_data = (Gen_dtor_007f6d20 *)Gen007EFFC0()->allocate( count * 8, 0 );
	for( int i = 0; i < count; ++i )
		new ( &m_data[ i ] ) Gen_dtor_007f6d20;
	m_count = count;
}

// -------------------------------------- allocate-and-construct over the two
//                                        already-named polymorphic arrays
class Rva007F77B0Block : public Rva007F6BA0
{
public:
	void allocate( int count );
};

void Rva007F77B0Block::allocate( int count )
{
	clear();
	m_array = Gen007EFFC0()->allocate( count * 0x1C, 0 );
	for( int i = 0; i < count; ++i )
		new ( (char *)m_array + i * 0x1C ) Rva00802E70Element;
	m_count = count;
}

class Rva007F7810Block : public Rva007F6C60
{
public:
	void allocate( int count );
};

void Rva007F7810Block::allocate( int count )
{
	clear();
	m_array = Gen007EFFC0()->allocate( count * 0x40, 0 );
	for( int i = 0; i < count; ++i )
		new ( (char *)m_array + i * 0x40 ) Rva00802D00Element;
	m_count = count;
}

// ------------------------------------------- owners that reset a whole array
class Rva007F70D0Owner
{
public:
	void reset();
	char m_head[ 0x38 ];
	Rva007F6BA0 m_array;
	int m_a;
	int m_b;
};

void Rva007F70D0Owner::reset()
{
	m_array.clear();
	m_a = 0;
	m_b = 0;
}

class Rva007F7140Owner
{
public:
	void reset();
	char m_head[ 0x48 ];
	Rva007F6C60 m_array;
	int m_a;
	int m_b;
};

void Rva007F7140Owner::reset()
{
	m_array.clear();
	m_a = 0;
	m_b = 0;
}

// --------------------------------------------------- three-field free-and-zero
class Rva007F9610Holder
{
public:
	void release();
	int m_a;
	int m_b;
	void *m_block;
};

void Rva007F9610Holder::release()
{
	Gen007EFFC0()->release( m_block, 1 );
	m_b = 0;
	m_a = 0;
	m_block = 0;
}

Rva00802E70Element::Rva00802E70Element()
{
	m_value04 = 0;
}

Rva00802D00Element::Rva00802D00Element()
{
	m_value1c = 0;
	m_value20 = 0;
	m_value04 = 0;
	m_value24 = 0;
	m_value2c = 0;
	m_value30 = 0;
	m_value34 = 0;
	m_value38 = 0;
	m_value3c = 0;
}
