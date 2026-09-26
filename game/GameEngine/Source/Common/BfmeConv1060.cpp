// Open-BFME5 conversions.

struct BfmeP1060
{
	char m_bfmePad[0x54];
	volatile int m_bfme54;
};

extern BfmeP1060 *g_bfmeP1060;
extern char g_bfmeLitA1060[];
extern char g_bfmeLitB1060[];
extern char g_bfmeLitC1060[];

class BfmeX1060;
extern BfmeX1060 *g_bfmeX1060;

class BfmeR1060
{
public:
	void bfmeRun1060(BfmeX1060 *a, char *b, int c, char *d, int e, int f, int g, int h);
};

extern BfmeR1060 *g_bfmeR1060;

void bfmeGo1060B(void)
{
	int v = g_bfmeP1060->m_bfme54;
	char *s = --v ? g_bfmeLitA1060 : g_bfmeLitB1060;

	g_bfmeR1060->bfmeRun1060(g_bfmeX1060, g_bfmeLitC1060, 1, s, 0, 0, 0, 0);
}

class BfmeO1060
{
public:
	int bfmeGet1060(int a);
};

class BfmeQ1060
{
public:
	int bfmeConv1060(int a);
};

extern BfmeQ1060 *g_bfmeQ1060;

struct BfmeFn1060
{
	void (__cdecl *m_bfmeFn)(BfmeO1060 *a, int b, int c, int d);
};

class BfmeSub1060
{
public:
	BfmeFn1060 *bfmeFind1060(int *k);
};

class BfmeW1060
{
public:
	char m_bfmePad[8];
	BfmeSub1060 m_bfmeSub;
};

extern BfmeW1060 *g_bfmeW1060;

void bfmeGo1060D(BfmeO1060 *o, int b, int c, int d)
{
	int t = g_bfmeQ1060->bfmeConv1060(o->bfmeGet1060(0));

	g_bfmeW1060->m_bfmeSub.bfmeFind1060(&t)->m_bfmeFn(o, b, c, d);
}
