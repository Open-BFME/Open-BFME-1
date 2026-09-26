// Open-BFME5 conversions.

class BfmeX1078;

class BfmeR1078
{
public:
	void bfmeRun1078(BfmeX1078 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern BfmeR1078 *g_bfmeR1078;
extern char g_bfmeFmt1078[];

class BfmeSubA1078
{
public:
	virtual void bfmeSlot1078_0(void);
	virtual void bfmeSlot1078_1(void);
	virtual void bfmeSlot1078_2(void);
	virtual void bfmeSlot1078_3(void);
};

class BfmeSubB1078
{
public:
	void bfmeReset1078(int a);
	char m_bfmePad[12];
};

struct BfmeG1078
{
	char m_bfmePad[0x5c];
	int m_bfme5c;
	int m_bfme60;
	int m_bfme64;
};

extern BfmeG1078 *g_bfmeG1078;

class BfmeQ1078
{
public:
	void bfmeGo1078A(void);
	void bfmeInit1078(void);
	char m_bfmePad[0x250];
	BfmeX1078 *m_bfme250;
	char m_bfmePad1[0x13c];
	BfmeSubA1078 m_bfmeSubA;
	char m_bfmePad2[0x14];
	int m_bfme3a8;
	int m_bfme3ac;
	int m_bfme3b0;
	int m_bfme3b4;
	int m_bfme3b8;
	int m_bfme3bc;
	BfmeSubB1078 m_bfmeSubB;
	int m_bfme3cc;
	char m_bfmePad3[3];
	char m_bfme3d3;
	int m_bfme3d4;
	char m_bfme3d8;
};

void BfmeQ1078::bfmeGo1078A(void)
{
	bfmeInit1078();
	m_bfmeSubA.bfmeSlot1078_3();
	m_bfme3d8 = 1;
	m_bfme3d3 = 0;
	m_bfme3ac = 0;
	m_bfme3b0 = 0;
	m_bfme3b4 = 0;
	m_bfme3b8 = 0;
	m_bfme3bc = 0;
	m_bfmeSubB.bfmeReset1078(0);
	m_bfme3cc = 0;
	m_bfme3a8 = 0;
	if (!(m_bfme3d4 & 2)) {
		g_bfmeR1078->bfmeRun1078(m_bfme250, g_bfmeFmt1078, 0, 0, 0, 0, 0, 0);
		m_bfme3d4 |= 2;
	}
	if (g_bfmeG1078) {
		g_bfmeG1078->m_bfme64 = 0;
		g_bfmeG1078->m_bfme5c = 0;
		g_bfmeG1078->m_bfme60 = 0;
	}
}
