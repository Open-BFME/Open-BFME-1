// Open-BFME5 conversions.

class BfmeX1064;

class BfmeR1064
{
public:
	void bfmeRun1064(BfmeX1064 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1064 *g_bfmeR1064;
extern char g_bfmeFmtA1064[];
extern char g_bfmeFmtB1064[];
extern char g_bfmeFmtC1064[];

class BfmeQ1064
{
public:
	void bfmeGo1064A(void);
	void bfmeSet1064B(char a);
	char bfmeChk1064(void);
	char m_bfmePad[0x250];
	BfmeX1064 *m_bfme250;
	char m_bfmePad2[0x40];
	char m_bfme294;
	char m_bfme295;
	char m_bfmePad3[0x112];
	int m_bfme3a8;
};

void BfmeQ1064::bfmeGo1064A(void)
{
	if (m_bfme3a8 == 3) {
		if (bfmeChk1064()) {
			g_bfmeR1064->bfmeRun1064(m_bfme250, g_bfmeFmtA1064, 0, 0, 0, 0, 0, 0);
			m_bfme3a8 = 4;
		} else {
			m_bfme3a8 = 1;
		}
	}
}

void BfmeQ1064::bfmeSet1064B(char a)
{
	if (!m_bfme294 && a == m_bfme295)
		return;
	m_bfme295 = a;
	m_bfme294 = 0;
	g_bfmeR1064->bfmeRun1064(m_bfme250, a ? g_bfmeFmtB1064 : g_bfmeFmtC1064, 0, 0, 0, 0, 0, 0);
}

__declspec(dllimport) int __cdecl bfmeFmt1064(char *b, unsigned int n, char *f, int a);

extern BfmeX1064 *g_bfmeV1064;
extern char *g_bfmeTbl1064[];
extern char g_bfmeFmtD1064[];
extern char g_bfmeFmtE1064[];

BfmeX1064 *bfmeMk1064(BfmeX1064 *a, BfmeX1064 *b);

void bfmeGo1064C(int a, int b)
{
	char buf[0x10];
	BfmeX1064 *x;

	bfmeFmt1064(buf, 0x10, g_bfmeFmtD1064, a);
	x = bfmeMk1064(g_bfmeV1064, g_bfmeV1064);
	g_bfmeR1064->bfmeRun1064(x, g_bfmeFmtE1064, 2, buf, g_bfmeTbl1064[b], 0, 0, 0);
}
