// Open-BFME5 conversions.

class BfmeX1063;

class BfmeR1063
{
public:
	void bfmeRun1063(BfmeX1063 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1063 *g_bfmeR1063;
extern char g_bfmeFmtC1063[];

class BfmeQ1063
{
public:
	void bfmeGo1063Q(void);
	char m_bfmePad[0x250];
	BfmeX1063 *m_bfme250;
	char m_bfmePad2[0x154];
	int m_bfme3a8;
	char m_bfmePad3[0x28];
	int m_bfme3d4;
};

void BfmeQ1063::bfmeGo1063Q(void)
{
	m_bfme3a8 = 1;
	if (!(m_bfme3d4 & 2)) {
		g_bfmeR1063->bfmeRun1063(m_bfme250, g_bfmeFmtC1063, 0, 0, 0, 0, 0, 0);
		m_bfme3d4 |= 2;
	}
}
