// ??0Rva0015A390Owner@@QAE@XZ
// partial score=0.19 date=2026-09-20
// ?Rva0015A390@Rva0015A390Owner@@QAE@XZ (address-derived; no owner class proven)
// cl: /O2 /Ob0
//
// Retail 0x0015A390 (322 B). Reached via caller 0x0015AB50 (still a dump,
// d_00153d10.asm) which reads TheAI (0x012EF214). Pure leaf constructor: no
// calls, only literal stores. Field +0x4 is twice a count read from
// TheAI->[0x14]->[0xb0]; +0x8..+0x120 is a fixed array of 10 0x1c-byte
// buckets zeroed; +0x120..+0x1b8 is a further zeroed tail region. this-
// relative field +0x0 is the only field named by the brief's evidence
// (+0x14 on a caller of THIS body, per landed-neighbour naming, is not
// modelled here since it belongs to a different function). No source
// declaration, vtable slot, or ZH twin proves the owning class or a
// semantic name, so this keeps the address token per naming policy.

class Rva0015A390Owner
{
public:
	Rva0015A390Owner();

private:
	char m_pad[0x1b9];
};

Rva0015A390Owner::Rva0015A390Owner()
{
	char *p = (char *)this;

	*(int *)p = 0;

	int aiPtr = *(volatile int *)0x012EF214;
	int sub = *(int *)( aiPtr + 0x14 );
	int count = *(int *)( sub + 0xb0 );
	*(int *)( p + 4 ) = count * 2;

	char *bucket = p + 8;
	unsigned int n = 10;
	do
	{
		*(int *)bucket = 0;
		int *inner = (int *)( bucket + 4 );
		inner[0] = 0;
		inner[1] = 0;
		inner[2] = 0;
		inner[3] = 0;
		inner[4] = 0;
		bucket += 0x1c;
		inner[5] = 0;
	} while( --n );

	*(int *)( p + 0x120 ) = 0;
	*(int *)( p + 0x1b4 ) = 0;
	*(unsigned char *)( p + 0x1b8 ) = 0;

	for( int off = 0x124; off <= 0x1ac; off += 4 )
		*(int *)( p + off ) = 0;

	*(int *)( p + 0x1b0 ) = 0;
}
