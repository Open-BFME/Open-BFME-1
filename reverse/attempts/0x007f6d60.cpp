// ??0Rva007F6D60Child@@QAE@XZ
// partial score=0.93 date=2026-09-18
// Reviewer correction: the named BfmeThingTWB identity was not unique. The
// caller BfmeThingDGDConstructor.cpp constructs four Rva007F6D60Child-sized
// records, and its child destructor witnesses the 0x0112B5C4 vtable and the
// same +0x1c buffer / nested-record prefix. Keep the caller-backed child
// constructor identity; the nested record class names remain unproven.

extern void *g_bfmeVftATWB[];
extern const char g_Rva0107301CEmptyString[];

class Gen_00800280
{
public:
	void *m();
};

class SnapshotDupReplica
{
public:
	SnapshotDupReplica();
};

class Rva00800290Buffer
{
public:
	void append( const char *text );
};

class Rva007F6D60Child
{
public:
	Rva007F6D60Child();
};

Rva007F6D60Child::Rva007F6D60Child()
{
	char *obj1 = (char *)this + 0x1c;

	*(void * volatile *)this = (void *)g_bfmeVftATWB;
	*(volatile int *)( (char *)this + 0x18 ) = 0;
	( (Gen_00800280 *)obj1 )->m();
	*(volatile int *)( (char *)this + 0x24 ) = 0;
	*(volatile int *)( (char *)this + 0x28 ) = 0;

	char *obj2 = (char *)this + 0x2c;
	( (SnapshotDupReplica *)obj2 )->SnapshotDupReplica::SnapshotDupReplica();
	*(void * volatile *)obj2 = (void *)0x011296B0;
	*(volatile int *)( obj2 + 0x08 ) = 0;
	*(volatile int *)( obj2 + 0x0c ) = 0;
	*(volatile int *)( obj2 + 0x04 ) = 0;

	char *obj3 = (char *)this + 0x3c;
	( (SnapshotDupReplica *)obj3 )->SnapshotDupReplica::SnapshotDupReplica();
	*(void * volatile *)obj3 = (void *)0x0112B4B4;
	*(volatile int *)( obj3 + 0x04 ) = 1;
	*(volatile unsigned char *)( obj3 + 0x08 ) = 0;
	*(volatile int *)( obj3 + 0x24 ) = 0;

	( (Rva00800290Buffer *)obj1 )->append( g_Rva0107301CEmptyString );
	*(volatile int *)( (char *)this + 0x08 ) = 0;
	*(volatile int *)( (char *)this + 0x0c ) = 0;
	*(volatile int *)( (char *)this + 0x10 ) = 0;
	*(volatile unsigned char *)( (char *)this + 0x14 ) = 0;
	*(volatile int *)( (char *)this + 0x18 ) = 0;
	*(volatile int *)( (char *)this + 0x24 ) = 0;
	*(volatile int *)( (char *)this + 0x28 ) = 0;
	*(volatile unsigned char *)( (char *)this + 0x6c ) = 0;

}
