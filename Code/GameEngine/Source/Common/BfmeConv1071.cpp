// Open-BFME5 conversions.

class BfmeX1071;

class BfmeR1071
{
public:
	void bfmeRun1071(BfmeX1071 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
	void bfmeOpen1071(BfmeX1071 *a);
};

extern BfmeR1071 *g_bfmeR1071;
extern BfmeX1071 *g_bfmeX1071;
extern char g_bfmeFmtD1071[];
extern char g_bfmeFmtP1071[];
extern char g_bfmeFmtQ1071[];
extern char g_bfmeFmtR1071[];
extern char g_bfmeF1071;
extern char g_bfmeH1071;

__declspec(dllimport) int __cdecl bfmeSpf1071(char *b, char *f, int a);

void bfmeGo1071A(int a, char b)
{
	char buf[0x10] = "";

	bfmeSpf1071(buf, g_bfmeFmtD1071, a);
	g_bfmeR1071->bfmeRun1071(g_bfmeX1071, b ? g_bfmeFmtP1071 : g_bfmeFmtQ1071, 1, buf, 0, 0, 0, 0);
}

void bfmeGo1071B(char a)
{
	if (a) {
		if (!g_bfmeF1071) {
			g_bfmeH1071 = 1;
			g_bfmeR1071->bfmeOpen1071(g_bfmeX1071);
			g_bfmeF1071 = 1;
			g_bfmeH1071 = 0;
		}
	} else {
		if (!g_bfmeF1071 && !g_bfmeH1071) {
			g_bfmeR1071->bfmeRun1071(g_bfmeX1071, g_bfmeFmtR1071, 0, 0, 0, 0, 0, 0);
			g_bfmeH1071 = 1;
		}
	}
}
