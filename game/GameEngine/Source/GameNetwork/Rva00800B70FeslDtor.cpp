// cl: /GX-
// Scalar-deleting sibling of matched 0x00800A00 (BfmeB1045::bfmeGo1045B): same
// twin-vptr restore, zero +8/+C/+10, eight reverse 0x24-stride bfmeDone1045
// calls from +0x204, then sized delete 0x1F8 when flags&1. Retail body is 90B
// (ghidra/gen_asm size 84 truncates the epilogue).

// retail 0x0112C308: the Rva00800920Owner primary vftable this body stores at
// +0x00, spelled exactly as its defining object spells it.
extern "C" void *__identifier("??_7Rva00800920Owner@@6BRva00800920Primary@@@")[];
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

// retail 0x007F0170: the sized release this body calls when flags&1, defined
// as the class operator delete ??3Gen007F0170@@SAXPAX@Z in
// game/GameEngine/Source/Common/S3AllocatorOperatorNewDelete.cpp. Retail's
// body reads one argument and returns, but the call sites push the size and
// clean 8 bytes, so the call goes through that definition with a
// two-argument pointer type -- the same shape
// game/GameEngine/Source/GameNetwork/Y4FeslSubTest.cpp already carries.
class Gen007F0170
{
public:
	static void operator delete(void *block);
};

typedef void (__cdecl *Gen007F0170SizedFree)(void *block, unsigned int size);

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

	m_bfmeVfptr = __identifier("??_7Rva00800920Owner@@6BRva00800920Primary@@@");
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
		((Gen007F0170SizedFree)&Gen007F0170::operator delete)( this, 0x1F8 );

	return this;
}
