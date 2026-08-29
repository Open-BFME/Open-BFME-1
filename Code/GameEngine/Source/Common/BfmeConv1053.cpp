// Open-BFME5 conversions.

extern "C" void *bfmeVft1053A[];
void *bfmeAlloc1053(int n);

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
	m_bfmeBuf = bfmeAlloc1053(0x1000);

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
