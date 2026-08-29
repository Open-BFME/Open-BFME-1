// Open-BFME5 conversions.

class BfmeX1069;

class BfmeR1069
{
public:
	void bfmeRun1069(BfmeX1069 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1069 *g_bfmeR1069;
extern char g_bfmeFmt1069[];
extern char g_bfmeLitA1069[];
extern char g_bfmeLitB1069[];

class BfmeH1069
{
public:
	void bfmeSet1069B(char a, char b);
	char m_bfmePad[0x34];
	BfmeH1069 *m_bfme34;
	char m_bfmePad2[0x19d];
	char m_bfme1d5;
	char m_bfmePad3[0x7a];
	BfmeX1069 *m_bfme250;
};

void BfmeH1069::bfmeSet1069B(char a, char b)
{
	if (!b && m_bfme1d5 == a)
		return;
	m_bfme1d5 = a;
	if (a)
		g_bfmeR1069->bfmeRun1069(m_bfme34->m_bfme250, g_bfmeFmt1069, 1, g_bfmeLitA1069, 0, 0, 0, 0);
	else
		g_bfmeR1069->bfmeRun1069(m_bfme34->m_bfme250, g_bfmeFmt1069, 1, g_bfmeLitB1069, 0, 0, 0, 0);
}
