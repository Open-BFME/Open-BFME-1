// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Rva007F6D60Child constructor, retail 0x007F6D60, 130 bytes.
//
// IDENTITY. BfmeThingDGDConstructor.cpp (0x007F7FA0) constructs four of these
// 0x94-byte records at this+0x58, and the destructor at 0x007F6DF0 (slot 0 of
// vtable 0x0112B5C4) tears down the same +0x1c buffer and the +0x2c/+0x3c
// records before restoring the base vtable 0x0112B598, whose own deleting
// destructor at 0x007F6E40 touches nothing but the vptr. Nothing in the image
// names the class, so the name keeps the address.
//
// LAYOUT. +0x1c is the jabba util.cpp buffer (Y2FeslBufferAndChain.cpp): its
// constructor at 0x00800280 zeroes the pointer and the count that reset() at
// 0x00800290 releases. +0x3c is Rva007F4DA0 (Rva007F4DA0Ctor.cpp): the same
// 0x01129358 base constructor at 0x007E86B0, then vtable 0x0112B4B4 with +4 = 1,
// byte +8 = 0 and +0x24 = 0. +0x2c is a 16-byte record on the same base that
// installs vtable 0x011296B0 and clears its three words.
//
// SHAPE. The words at +0x18 and +0x24 are one-word members that zero
// themselves. As plain scalars in the initializer list MSVC hoists each
// following receiver load above the vptr store and above the +0x24 store,
// which retail does not; as members with their own inline constructors the
// schedule is retail's.

extern const char g_Rva0107301CEmptyString[];

class Gen_00800280
{
public:
	void *m();
};

class Rva00800290Buffer
{
public:
	Rva00800290Buffer()
	{
		((Gen_00800280 *)this)->m();
	}
	void append( const char *text );

	char *m_ptr;
	int m_size;
};

class Rva007F6D60ZeroWord
{
public:
	Rva007F6D60ZeroWord() : m_value( 0 ) {}

	unsigned m_value;
};

class SnapshotDupReplica
{
public:
	SnapshotDupReplica();
	virtual void handle();
};

class Rva007F6D60Member2C : public SnapshotDupReplica
{
public:
	Rva007F6D60Member2C()
	{
		m_08 = 0;
		m_0c = 0;
		m_04 = 0;
	}
	virtual void handle();

	int m_04;
	int m_08;
	int m_0c;
};

class Rva007F4DA0 : public SnapshotDupReplica
{
public:
	Rva007F4DA0()
	{
		m_04 = 1;
		m_08 = 0;
		m_24 = 0;
	}
	virtual void handle();

	int m_04;
	char m_08;
	char m_gap[0x1B];
	int m_24;
};

class Rva007F6D60ChildBase
{
public:
	virtual ~Rva007F6D60ChildBase();
};

class Rva007F6D60Child : public Rva007F6D60ChildBase
{
public:
	Rva007F6D60Child();
	virtual ~Rva007F6D60Child();

	unsigned m_04;
	unsigned m_08;
	unsigned m_0c;
	unsigned m_10;
	unsigned char m_14;
	Rva007F6D60ZeroWord m_18;
	Rva00800290Buffer m_buffer1C;
	Rva007F6D60ZeroWord m_24;
	unsigned m_28;
	Rva007F6D60Member2C m_chain2C;
	Rva007F4DA0 m_chain3C;
	unsigned char m_pad64[0x08];
	unsigned char m_6c;
	unsigned char m_pad6D[0x27];
};

Rva007F6D60Child::Rva007F6D60Child()
	: m_28( 0 )
{
	m_08 = 0;
	m_0c = 0;
	m_10 = 0;
	m_14 = 0;
	m_18.m_value = 0;
	m_buffer1C.append( g_Rva0107301CEmptyString );
	m_24.m_value = 0;
	m_28 = 0;
	m_6c = 0;
}
