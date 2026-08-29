// Open-BFME5 conversions.

class BfmeX1076;

class BfmeR1076
{
public:
	void bfmeRun1076(BfmeX1076 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1076 *g_bfmeR1076;
extern char g_bfmeFmt1076[];

class BfmeQ1076
{
public:
	int bfmeGo1076A(int a, char b, char c);
	void bfmeF1076(void);
	void bfmeG1076(int a);
	char m_bfmePad[0x250];
	BfmeX1076 *m_bfme250;
	char m_bfmePad1[4];
	int m_bfme258;
	int m_bfme25c;
};

int BfmeQ1076::bfmeGo1076A(int a, char b, char c)
{
	if (a != 0x15 || b != 1 || !(c & 1))
		return 0;
	if (m_bfme25c == 0 && m_bfme258 != 2)
		g_bfmeR1076->bfmeRun1076(m_bfme250, g_bfmeFmt1076, 0, 0, 0, 0, 0, 0);
	else if (m_bfme25c != 0 && m_bfme258 == 0)
		bfmeF1076();
	else if (m_bfme25c == 0 && m_bfme258 == 2)
		bfmeG1076(0);
	return 1;
}
