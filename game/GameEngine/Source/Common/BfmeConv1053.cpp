// Open-BFME5 conversions.

extern "C" void *bfmeVft1053A[];

// 0x008064A0 IS THE RECORD CREATE of the DirtySock record module
// (game/Libraries/Source/DirtySock/Y2Rva00806580Module.cpp), which defines
// it taking no argument; retail's caller at +0x03 pushes 0x1000 and cleans it
// with the `add esp, 4` at +0x21, so the argument is dead weight at the call
// site.  It is declared here with its defining signature and called through a
// one-argument view of its own type, which is what keeps the push and the
// `add esp, 4` in retail's bytes while the call still names the real symbol.
struct Rva00806580Record;
Rva00806580Record *Rva008064A0(void);
typedef Rva00806580Record *( *Rva008064A0WithArg )( int );

class BfmeA1053
{
public:
	BfmeA1053 *bfmeGo1053A(void);

	void *m_bfmeVfptr;
	int m_bfme04;
	void *m_bfmeBuf;
	int m_bfme0c;
	char m_bfme10;
};

BfmeA1053 *BfmeA1053::bfmeGo1053A(void)
{
	m_bfmeVfptr = bfmeVft1053A;
	m_bfmeBuf = ( ( Rva008064A0WithArg )Rva008064A0 )( 0x1000 );

	int z = 0;

	m_bfme04 = z;
	m_bfme0c = z;
	m_bfme10 = (char)z;
	return this;
}

class BfmeE1053;

extern "C" void bfmeHook1053(void);
extern char g_bfmeName1053[];
extern int g_bfmeTab1053;
void bfmeReg1053(int a, int b, char *n, int k, int *t, void (*fn)(void), BfmeE1053 *o, int f);

class BfmeE1053
{
public:
	void bfmeGo1053E(int a, int b);
};

void BfmeE1053::bfmeGo1053E(int a, int b)
{
	bfmeReg1053(a, b, g_bfmeName1053, 8, &g_bfmeTab1053, bfmeHook1053, this, 0);
}
