// Open-BFME5 conversions.

class BfmeX1072;

class BfmeR1072
{
public:
	void bfmeRun1072(BfmeX1072 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1072 *g_bfmeR1072;
extern char g_bfmeFmtA1072[];
extern char g_bfmeFmtB1072[];
extern char g_bfmeFmtC1072[];
extern char g_bfmeFmtD1072[];
extern char g_bfmeFmtE1072[];
extern char g_bfmeLitA1072[];
extern char g_bfmeLitB1072[];
extern char g_bfmeD1072;

__declspec(dllimport) int __cdecl bfmeSpf1072(char *b, char *f, int a);

class BfmeQ1072
{
public:
	void bfmeGo1072A(int a, int b);
	int bfmeGo1072B(void);
	void bfmeGo1072C(char a);
	char m_bfmePad[0x5c];
	BfmeX1072 *m_bfme5c;
	char m_bfmePad1[0x20];
	int m_bfme80[116];
	BfmeX1072 *m_bfme250;
	char m_bfmePad2[4];
	int m_bfme258;
	char m_bfmePad3[0x178];
	int m_bfme3d4;
};

void BfmeQ1072::bfmeGo1072A(int a, int b)
{
	char buf1[0x40];
	char buf2[0x40];

	bfmeSpf1072(buf1, g_bfmeFmtA1072, m_bfme80[a]);
	bfmeSpf1072(buf2, g_bfmeFmtA1072, b);
	g_bfmeR1072->bfmeRun1072(m_bfme5c, g_bfmeFmtB1072, 2, buf1, buf2, 0, 0, 0);
}

int BfmeQ1072::bfmeGo1072B(void)
{
	if (m_bfme258 == 1) {
		if (g_bfmeD1072) {
			g_bfmeR1072->bfmeRun1072(m_bfme250, g_bfmeFmtC1072, 1, g_bfmeLitA1072, 0, 0, 0, 0);
			m_bfme258 = 3;
		} else {
			g_bfmeR1072->bfmeRun1072(m_bfme250, g_bfmeFmtC1072, 1, g_bfmeLitB1072, 0, 0, 0, 0);
			m_bfme258 = 2;
		}
	}
	return 1;
}

void BfmeQ1072::bfmeGo1072C(char a)
{
	if ((a & 1) && !(m_bfme3d4 & 1)) {
		g_bfmeR1072->bfmeRun1072(m_bfme250, g_bfmeFmtD1072, 0, 0, 0, 0, 0, 0);
		m_bfme3d4 |= 1;
	}
	if ((a & 2) && !(m_bfme3d4 & 2)) {
		g_bfmeR1072->bfmeRun1072(m_bfme250, g_bfmeFmtE1072, 0, 0, 0, 0, 0, 0);
		m_bfme3d4 |= 2;
	}
}
