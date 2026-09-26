// cl: /EHs-c-
// EA FESL client SDK ("jabba") -- four destructors from the gamebrowser
// cluster, plus the two compiler-generated scalar-deleting wrappers that two of
// them come with.
//
// WHY THIS FILE CARRIES ITS OWN FLAG.  The base command line spells `-EHsc-`,
// which cl parses as EHs ON: every destructor here then gets an EH frame
// (`push -1 / push <handler> / mov eax,fs:[0]`) that retail's bodies do not
// have.  /EHs-c- turns both halves off and is what the bytes force.
//
// WHAT THE BYTES SHOW.  Each row opens by storing one address over [this] and
// closes by storing a DIFFERENT address over the same slot.  Two vptr writes in
// one body is a derived destructor with its base's destructor inlined: the
// derived vptr is installed on entry, the body runs, and the base destructor
// then reinstalls the base vptr.  So each of these classes has a virtual
// destructor and a base with an EMPTY inline one -- and because the base
// destructor's own body is empty, nothing survives of it but that store.
//
// The member calls between the two stores are NOT destructor calls: they enter
// bodies the ledger already names as `reset` / `clear` (0x00800290, 0x00800630,
// 0x00802A10, 0x007F78E0), so they are ordinary member calls written in the
// destructor body.  Their descending offset order is source order, not
// compiler-generated reverse-declaration destruction.
//
// 0x00802510 and 0x00802D40 are the `??_G` scalar-deleting wrappers MSVC emits
// beside a virtual destructor: same body, then `test byte ptr [esp+8],1` and a
// one-argument global release at 0x00881EB0 that the tree already names
// ??3@YAXPAX@Z.  They are claimed here because writing the destructor is what
// produces them; nothing about them is written by hand.
//
// IDENTITY IS NOT RECOVERED.  Every class and member name is derived from an
// address.  The vtable addresses are DIR32 the patcher fills; they are used
// here only as the evidence for "two classes", not as names.

// The four base classes exist only to produce the SECOND vptr store; their
// destructors are empty and inline, so retail has no separate body for any of
// them and none for the deleting wrappers MSVC emits beside them.  The labels
// below are copied out of this file's own object symbol table, not written by
// hand.
//
// ??1Rva00802EC0Base@@UAE@XZ absent-from-retail
// ??_GRva00802EC0Base@@UAEPAXI@Z absent-from-retail
// ??1Rva00802CA0Base@@UAE@XZ absent-from-retail
// ??_GRva00802CA0Base@@UAEPAXI@Z absent-from-retail
// ??1Rva00802380Base@@UAE@XZ absent-from-retail
// ??_GRva00802380Base@@UAEPAXI@Z absent-from-retail
// ??1Rva00802680Base@@UAE@XZ absent-from-retail
// ??_GRva00802680Base@@UAEPAXI@Z absent-from-retail

// ---------------------------------------------------------------- callees
class Rva00800290Buffer
{
public:
	void reset();                       // 0x00800290

	char *m_ptr;
	int   m_size;
};

class Rva00800630Owner
{
public:
	void clear();                       // 0x00800630

	void *m_block;
	int   m_field4;
	int   m_field8;
};

class Rva00802A10Elem
{
public:
	virtual void step( int flags );
	char m_pad[ 128 - 4 ];
};

class Rva00802A10
{
public:
	void clear();                       // 0x00802A10

	Rva00802A10Elem *m_array;
	int m_count;
};

class Gen_dtor_007f6d20;

class Rva007F78E0Block
{
public:
	void clear();                       // 0x007F78E0

	Gen_dtor_007f6d20 *m_data;
	int m_count;
};

// ------------------------------------------------ 0x00802EC0, two buffers
class Rva00802EC0Base
{
public:
	virtual ~Rva00802EC0Base() {}

	int m_field4;
	int m_field8;
};

class Rva00802EC0Owner : public Rva00802EC0Base
{
public:
	virtual ~Rva00802EC0Owner();

	Rva00800290Buffer m_a;      // +0x0C
	Rva00800290Buffer m_b;      // +0x14
};

Rva00802EC0Owner::~Rva00802EC0Owner()
{
	m_field4 = 0;
	m_b.reset();
	m_a.reset();
}

// ------------------------ 0x00802CA0 + its wrapper 0x00802D40, two buffers
//                          and a counted array
class Rva00802CA0Base
{
public:
	virtual ~Rva00802CA0Base() {}

	int m_field4;
	int m_field8;
};

class Rva00802CA0Owner : public Rva00802CA0Base
{
public:
	virtual ~Rva00802CA0Owner();

	Rva00800290Buffer m_a;          // +0x0C
	Rva00800290Buffer m_b;          // +0x14
	Rva00802A10       m_entries;    // +0x1C
};

Rva00802CA0Owner::~Rva00802CA0Owner()
{
	m_field4 = 0;
	m_entries.clear();
	m_b.reset();
	m_a.reset();
}

// ------------------------ 0x00802380 + its wrapper 0x00802510, one embedded
//                          three-field owner and two trailing dwords
class Rva00802380Base
{
public:
	virtual ~Rva00802380Base() {}

	int m_field4;
	int m_field8;
};

class Rva00802380Owner : public Rva00802380Base
{
public:
	virtual ~Rva00802380Owner();

	char              m_pad00C[ 0x0C ];
	Rva00800630Owner  m_owner;      // +0x18
	int               m_field24;
	int               m_field28;
};

Rva00802380Owner::~Rva00802380Owner()
{
	m_field4 = 0;
	m_field24 = 0;
	m_field28 = 0;
	m_owner.clear();
}

// ------------------------------- 0x00802680, a stride-8 block and two buffers
class Rva00802680Base
{
public:
	virtual ~Rva00802680Base() {}

	int m_field4;
	int m_field8;
	int m_fieldC;
};

class Rva00802680Owner : public Rva00802680Base
{
public:
	virtual ~Rva00802680Owner();

	char              m_pad010[ 0x10 ];
	Rva007F78E0Block  m_block;      // +0x20
	Rva00800290Buffer m_b;          // +0x28
	Rva00800290Buffer m_c;          // +0x30
};

Rva00802680Owner::~Rva00802680Owner()
{
	m_field4 = 0;
	m_fieldC = 0;
	m_field8 = 0;
	m_c.reset();
	m_b.reset();
	m_block.clear();
}
