// cl: /GX-
// Scalar-deleting sibling of matched 0x00800A00 (BfmeB1045::bfmeGo1045B): same
// twin-vptr restore, zero +8/+C/+10, eight reverse 0x24-stride bfmeDone1045
// calls from +0x204, then sized delete 0x1F8 when flags&1. Retail body is 90B
// (ghidra/gen_asm size 84 truncates the epilogue).

extern "C" void *bfmeVft1045A[];
extern "C" void *bfmeVft1045B[];

class BfmeSub1045
{
public:
	void bfmeDone1045(void);
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
	m_bfmeVfptr2 = bfmeVft1045B;
	m_bfme08 = z;
	m_bfme0c = z;
	m_bfme10 = z;

	BfmeSub1045 *p = &m_bfmeArr[8];
	int n = 8;

	do {
		p--;
		p->bfmeDone1045();
	} while( --n != 0 );

	if( flags & 1 )
		bfmeDeleteVMP( this, 0x1F8 );

	return this;
}
