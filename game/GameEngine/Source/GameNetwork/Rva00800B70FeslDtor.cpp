// cl: /GX-
// Scalar-deleting sibling of matched 0x00800A00 (BfmeB1045::bfmeGo1045B): same
// twin-vptr restore, zero +8/+C/+10, eight reverse 0x24-stride bfmeDone1045
// calls from +0x204, then sized delete 0x1F8 when flags&1. Retail body is 90B
// (ghidra/gen_asm size 84 truncates the epilogue).

extern "C" void *bfmeVft1045A[];
// retail 0x0112C304: the Rva00800920Sec secondary vftable of Rva00800920Owner.
extern "C" void *__identifier("??_7Rva00800920Owner@@6BRva00800920Sec@@@")[];

// 0x007E86C0 is the shared FESL base cleanup (ledger:
// ?m@Gen_007e86c0@@QAEXXZ); it is this body's per-slot teardown step.
class Gen_007e86c0
{
public:
	void m(void);
};

class BfmeSub1045
{
public:
	char m_bfmePad[0x24];
};

void bfmeDeleteVMP( void *block, unsigned size );

class Rva00800B70Owner
{
public:
	void *bfmeGo( unsigned char flags );

	void *m_bfmeVfptr;
	void *m_bfmeVfptr2;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	char m_bfmePad[0xd0];
	BfmeSub1045 m_bfmeArr[8];
};

void *Rva00800B70Owner::bfmeGo( unsigned char flags )
{
	int z = 0;

	m_bfmeVfptr = bfmeVft1045A;
	m_bfmeVfptr2 = __identifier("??_7Rva00800920Owner@@6BRva00800920Sec@@@");
	m_bfme08 = z;
	m_bfme0c = z;
	m_bfme10 = z;

	BfmeSub1045 *p = &m_bfmeArr[8];
	int n = 8;

	do {
		p--;
		((Gen_007e86c0 *)p)->m();
	} while( --n != 0 );

	if( flags & 1 )
		bfmeDeleteVMP( this, 0x1F8 );

	return this;
}
