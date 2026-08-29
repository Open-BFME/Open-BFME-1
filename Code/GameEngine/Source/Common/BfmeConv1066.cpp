// Open-BFME5 conversions.

class BfmeX1066;

class BfmeR1066
{
public:
	void bfmeRun1066(BfmeX1066 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
	void bfmeStop1066(int a);
};

extern BfmeR1066 *g_bfmeR1066;
extern char g_bfmeFmtA1066[];
extern char g_bfmeFmtB1066[];
extern char g_bfmeLitA1066[];
extern char g_bfmeLitB1066[];

struct BfmeM1066
{
	char m_bfmePad[0xa9f];
	char m_bfmea9f;
};

extern BfmeM1066 *g_bfmeM1066;

class BfmeH1066;

BfmeX1066 *__cdecl bfmeConv1066(BfmeH1066 *h);

class BfmeH1066
{
public:
	void bfmeGo1066A(int a);
	void bfmeGo1066B(int a);
	char m_bfmePad[0x250];
	BfmeX1066 *m_bfme250;
	char m_bfmePad2[4];
	char m_bfme258;
	char m_bfme259;
	char m_bfme25a;
	char m_bfme25b;
};

void BfmeH1066::bfmeGo1066A(int a)
{
	if (m_bfme25a)
		return;
	g_bfmeR1066->bfmeRun1066(bfmeConv1066(this), g_bfmeFmtA1066, 0, 0, 0, 0, 0, 0);
	m_bfme25a = 1;
	if (!m_bfme25b) {
		g_bfmeR1066->bfmeStop1066(0);
		m_bfme25b = 1;
	}
}

void BfmeH1066::bfmeGo1066B(int a)
{
	char *s = g_bfmeM1066->m_bfmea9f ? g_bfmeLitA1066 : g_bfmeLitB1066;

	g_bfmeR1066->bfmeRun1066(m_bfme250, g_bfmeFmtB1066, 1, s, 0, 0, 0, 0);
	m_bfme258 = 1;
	if (m_bfme259) {
		m_bfme25a = 1;
		m_bfme259 = 0;
	}
}
