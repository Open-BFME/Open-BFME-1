// Open-BFME5 conversions.

class BfmeE1037;

class BfmeD1037
{
public:
	BfmeD1037 *bfmeInit1037(BfmeE1037 *o);
};

void *bfmeAlloc1037(int n);

class BfmeE1037
{
public:
	BfmeD1037 *bfmeGo1037E(void);
};

BfmeD1037 *BfmeE1037::bfmeGo1037E(void)
{
	BfmeD1037 *p = (BfmeD1037 *)bfmeAlloc1037(0x90);

	if (p != 0)
		return p->bfmeInit1037(this);

	return 0;
}

class BfmeG1037
{
public:
	void bfmeDo1037(int b, int c);
};

BfmeG1037 * __stdcall bfmeFind1037F(int a);

void __stdcall bfmeGo1037F(int a, int b, int c)
{
	BfmeG1037 *g = bfmeFind1037F(a);

	if (g != 0)
		g->bfmeDo1037(b, c);
}

class BfmeLog1037
{
public:
	virtual void bfmeV01037();
	virtual void bfmeSay1037(char *m);
};

__declspec(dllimport) int __stdcall bfmeWait1037(void *h, int t);
BfmeLog1037 *bfmeGetLog1037(void);
extern char g_bfmeMsg1037[];

class BfmeH1037
{
public:
	void bfmeGo1037H(void);

	char m_bfmePad[4];
	void *m_bfmeHandle;
};

void BfmeH1037::bfmeGo1037H(void)
{
	if (bfmeWait1037(m_bfmeHandle, -1) != 0)
		bfmeGetLog1037()->bfmeSay1037(g_bfmeMsg1037);
}

class BfmeI1037
{
public:
	void bfmeGo1037I(char f);
	void bfmeTailA1037(int n);
	void bfmeTailB1037(int n);

	char m_bfmePad[0x98];
	int m_bfmeFlags;
};

void BfmeI1037::bfmeGo1037I(char f)
{
	m_bfmeFlags |= 2;

	if (f != 0)
		bfmeTailA1037(1);
	else
		bfmeTailB1037(1);
}
