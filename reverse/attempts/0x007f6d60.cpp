// ??0Rva007F6D60Child@@QAE@XZ
// partial score=0.99 date=2026-09-21
// Reviewer correction: the named BfmeThingTWB identity was not unique. The
// caller BfmeThingDGDConstructor.cpp constructs four Rva007F6D60Child-sized
// records, and its child destructor witnesses the 0x0112B5C4 vtable and the
// same +0x1c buffer / nested-record prefix. Keep the caller-backed child
// constructor identity; the nested record class names remain unproven.

extern const char g_Rva0107301CEmptyString[];

class Gen_00800280
{
public:
	void *m();
};

class Gen_007E86B0
{
public:
	void m();
};

class SnapshotDupReplica
{
public:
	void init(void)
	{
		((Gen_007E86B0 *)this)->m();
	}

	char m_unmodelled[0x10];
};

class Rva00800290Buffer
{
public:
	void init(void)
	{
		((Gen_00800280 *)this)->m();
	}
	void append( const char *text );

	char m_unmodelled[0x10];
};

class Rva007F6D60Child
{
public:
	Rva007F6D60Child();

	volatile unsigned m_vftable;
	unsigned m_04;
	volatile unsigned m_08;
	char m_pad0C[0x10];
	Rva00800290Buffer m_buffer1C;
	SnapshotDupReplica m_chain2C;
	SnapshotDupReplica m_chain3C;
	char m_pad4C[0x48];
};

Rva007F6D60Child::Rva007F6D60Child()
{
	Rva00800290Buffer *buffer = &m_buffer1C;
	m_vftable = 0x0112B5C4;
	*(volatile int *)( (char *)this + 0x18 ) = 0;
	buffer->init();
	*(volatile int *)( (char *)this + 0x24 ) = 0;
	*(int *)( (char *)this + 0x28 ) = 0;

	{
	m_chain2C.init();
	SnapshotDupReplica *obj2 = &m_chain2C;
	*(void * volatile *)obj2 = (void *)0x011296B0;
	*(volatile int *)( (char *)obj2 + 0x08 ) = 0;
	*(volatile int *)( (char *)obj2 + 0x0c ) = 0;
	*(volatile int *)( (char *)obj2 + 0x04 ) = 0;

	m_chain3C.init();
	SnapshotDupReplica *obj3 = &m_chain3C;
	*(void * volatile *)obj3 = (void *)0x0112B4B4;
	*(volatile int *)( (char *)obj3 + 0x04 ) = 1;
	*(volatile unsigned char *)( (char *)obj3 + 0x08 ) = 0;
	*(volatile int *)( (char *)obj3 + 0x24 ) = 0;

	*(int *)( (char *)this + 0x08 ) = 0;
	*(int *)( (char *)this + 0x0c ) = 0;
	*(int *)( (char *)this + 0x10 ) = 0;
	*(unsigned char *)( (char *)this + 0x14 ) = 0;
	*(int *)( (char *)this + 0x18 ) = 0;
	buffer->append( g_Rva0107301CEmptyString );
	}
	*(int *)( (char *)this + 0x24 ) = 0;
	*(int *)( (char *)this + 0x28 ) = 0;
	*(volatile unsigned char *)( (char *)this + 0x6c ) = 0;

}
