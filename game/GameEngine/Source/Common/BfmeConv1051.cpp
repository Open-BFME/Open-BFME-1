// Open-BFME5 conversions.

class BfmeLog1051
{
public:
	void bfmeLog1051(int a, char *f, int n, char *t, int p, int q, int r, int s);
};

extern BfmeLog1051 *g_bfmeLog1051;
extern char g_bfmeFmt1051[];
extern char g_bfmeArg1051[];

class BfmeA1051
{
public:
	void bfmeGo1051A(void);

	char m_bfmePad[0x250];
	int m_bfmeId;
	char m_bfmePad2[4];
	int m_bfmeState;
};

void BfmeA1051::bfmeGo1051A(void)
{
	m_bfmeState = 4;
	g_bfmeLog1051->bfmeLog1051(m_bfmeId, g_bfmeFmt1051, 1, g_bfmeArg1051, 0, 0, 0, 0);
}

struct BfmeC1051
{
	char m_bfmePad[0xc];
	int m_bfme0c;
	int m_bfme10;
};

struct BfmeS1051
{
	char m_bfmePad[0x3c];
	int m_bfme3c;
};

extern BfmeS1051 *g_bfmeS1051;
extern char g_bfmeFmt1051B[];
int bfmeCount1051(int a, int b, char *f, int n);

class BfmeB1051
{
public:
	void bfmeGo1051B(void);

	char m_bfmePad[4];
	BfmeC1051 *m_bfmeC;
	char m_bfmePad2[0x18];
	int m_bfme20;
	int m_bfme24;
};

void BfmeB1051::bfmeGo1051B(void)
{
	BfmeC1051 *c = m_bfmeC;
	int n = bfmeCount1051(c->m_bfme0c, c->m_bfme10, g_bfmeFmt1051B, 0x6a);
	int base = g_bfmeS1051->m_bfme3c;

	m_bfme24 = base;
	m_bfme20 = base + n;
}

class BfmeSub1051
{
public:
	void bfmeSend1051(int a, int b, int c, int d, int e, int f);
};

class BfmeD1051
{
public:
	void bfmeGo1051D(int a, int b, int c, int d, int e);

	char m_bfmePad[0x60];
	BfmeSub1051 m_bfmeSub;
};

void BfmeD1051::bfmeGo1051D(int a, int b, int c, int d, int e)
{
	m_bfmeSub.bfmeSend1051(a, b, c, d, e, 0);
}

struct BfmeSubN1051
{
	char m_bfmePad[4];
};

struct BfmeN1051
{
	int m_bfmeFirst;
	BfmeSubN1051 m_bfmeSub;
};

void *bfmeAlloc1051(int n);
void bfmeInit1051(BfmeSubN1051 *s, int a);

void * __stdcall bfmeGo1051G(int a)
{
	BfmeN1051 *n = (BfmeN1051 *)bfmeAlloc1051(0x2c);

	n->m_bfmeFirst = 0;
	bfmeInit1051(&n->m_bfmeSub, a);
	return n;
}
