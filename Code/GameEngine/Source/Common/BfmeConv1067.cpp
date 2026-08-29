// Open-BFME5 conversions.

class BfmeX1067;

class BfmeR1067
{
public:
	void bfmeRun1067(BfmeX1067 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1067 *g_bfmeR1067;
extern BfmeX1067 *g_bfmeX1067;
extern BfmeX1067 *g_bfmeV1067;
extern char g_bfmeFmtD1067[];
extern char g_bfmeFmtA1067[];
extern char g_bfmeFmtB1067[];
extern char g_bfmeLit1067[];
extern char g_bfmeLitA1067[];
extern char g_bfmeLitB1067[];

__declspec(dllimport) int __cdecl bfmeFmt1067(char *b, unsigned int n, char *f, int a);
BfmeX1067 *__cdecl bfmeMk1067(BfmeX1067 *a, BfmeX1067 *b);

struct BfmeN1067
{
	char *m_bfme00;
};

void bfmeGo1067A(int a, BfmeN1067 *n)
{
	char buf[0x10];
	char *q;
	char *s;

	bfmeFmt1067(buf, 0x10, g_bfmeFmtD1067, a);
	q = n->m_bfme00;
	s = q ? q + 8 : g_bfmeLit1067;
	g_bfmeR1067->bfmeRun1067(g_bfmeX1067, g_bfmeFmtA1067, 2, buf, s, 0, 0, 0);
}

void bfmeGo1067B(int a, char b)
{
	char buf[0x10];
	char *s;

	bfmeFmt1067(buf, 0x10, g_bfmeFmtD1067, a);
	s = b ? g_bfmeLitA1067 : g_bfmeLitB1067;
	g_bfmeR1067->bfmeRun1067(bfmeMk1067(g_bfmeV1067, g_bfmeV1067), g_bfmeFmtB1067, 2, buf, s, 0, 0, 0);
}
