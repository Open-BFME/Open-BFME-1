// ?bfmeInitTWB@BfmeThingTWB@@QAEPAV1@XZ
// partial score=0.92 date=2026-09-13
// Open-BFME5: BfmeThingTWB's constructor, retail 0x007F6D60. Pairs with the
// matched destructor bfmeDelTWB (BfmeConv1325.cpp, same g_bfmeVftATWB vtable
// at +0), which proves the class. Installs its own vtable, zeroes the fields
// bfmeDelTWB also re-zeroes, resets the +0x1c byte buffer (jabba's
// Rva00800290Buffer, Y2FeslBufferAndChain.cpp) via its Gen_00800280 ctor
// helper, and builds two SnapshotDupReplica-shaped records at +0x2c and
// +0x3c through the matched dup_7e86b0 base constructor.

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

class BfmeThingTWB
{
public:
	BfmeThingTWB *bfmeInitTWB();
};

BfmeThingTWB *BfmeThingTWB::bfmeInitTWB()
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

	return this;
}
