// Open-BFME5 conversions.

class BfmeX1073;

class BfmeR1073
{
public:
	void bfmeRun1073(BfmeX1073 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1073 *g_bfmeR1073;
extern BfmeX1073 *g_bfmeX1073;
extern char g_bfmeFmtA1073[];
extern char g_bfmeFmtB1073[];
extern char g_bfmeFmtF1073[];
extern char g_bfmeFmtG1073[];
extern char g_bfmeLit1073[];

class BfmeQ1073
{
public:
	void bfmeGo1073A(char a);
	char m_bfmePad[0x250];
	BfmeX1073 *m_bfme250;
	char m_bfmePad1[0x180];
	int m_bfme3d4;
};

void BfmeQ1073::bfmeGo1073A(char a)
{
	if ((a & 1) && (m_bfme3d4 & 1)) {
		g_bfmeR1073->bfmeRun1073(m_bfme250, g_bfmeFmtA1073, 0, 0, 0, 0, 0, 0);
		m_bfme3d4 &= ~1;
	}
	if ((a & 2) && (m_bfme3d4 & 2)) {
		g_bfmeR1073->bfmeRun1073(m_bfme250, g_bfmeFmtB1073, 0, 0, 0, 0, 0, 0);
		m_bfme3d4 &= ~2;
	}
}

__declspec(dllimport) int __cdecl bfmeFmt1073(char *b, unsigned int n, char *f, double d);

struct BfmeN1073
{
	char *m_bfme00;
};

void bfmeGo1073B(BfmeN1073 *n, float b, float c)
{
	char buf1[0x10];
	char buf2[0x10];
	char *q;
	char *s;

	bfmeFmt1073(buf1, 0x10, g_bfmeFmtF1073, b);
	bfmeFmt1073(buf2, 0x10, g_bfmeFmtF1073, c);
	q = n->m_bfme00;
	s = q ? q + 8 : g_bfmeLit1073;
	g_bfmeR1073->bfmeRun1073(g_bfmeX1073, g_bfmeFmtG1073, 3, s, buf1, buf2, 0, 0);
}
