// Open-BFME5 conversions.

class BfmeUnit1013
{
public:
	void bfmeStop1013(int n);
};

class BfmeA1013
{
public:
	void bfmeGo1013A(int unused);

	char m_bfmePad[0x188];
	int m_bfmeState;
	char m_bfmePad2[0x14];
	BfmeUnit1013 *m_bfmeA;
	BfmeUnit1013 *m_bfmeB;
};

void BfmeA1013::bfmeGo1013A(int unused)
{
	int s = m_bfmeState;

	if (s == 2 || s == 3) {
		m_bfmeA->bfmeStop1013(0);
		m_bfmeB->bfmeStop1013(0);
		m_bfmeState = 4;
	}
}

class BfmeHub1013
{
public:
	virtual void bfmeVH01013();
	virtual void bfmeVH11013();
	virtual void bfmeVH21013();
	virtual void bfmeVH31013();
	virtual void bfmeReset1013();
};

extern BfmeHub1013 *g_bfmeHub1013;

class BfmeB1013
{
public:
	int bfmeGo1013B();
	void bfmeFinish1013();

	char m_bfmePad[0x258];
	int m_bfmeMode;
	char m_bfmePad2[5];
	char m_bfmeFlag;
};

int BfmeB1013::bfmeGo1013B()
{
	if (m_bfmeFlag) {
		m_bfmeFlag = 0;
		bfmeFinish1013();
		return 1;
	}

	if (m_bfmeMode == 1) {
		g_bfmeHub1013->bfmeReset1013();
		m_bfmeMode = 0;
	}

	return 1;
}

class BfmeLog1013
{
public:
	void bfmeLog1013(int a, char *fmt, int n, int p, int q, int r, int s, int t);
};

extern BfmeLog1013 *g_bfmeLog1013;
extern char g_bfmeFmt1013[];

char bfmeAsk1013(void);

class BfmeC1013
{
public:
	void bfmeGo1013C();

	char m_bfmePad[0x250];
	int m_bfmeId;
	char m_bfmePad2[0x154];
	int m_bfmeState;
};

void BfmeC1013::bfmeGo1013C()
{
	if (m_bfmeState != 8)
		return;

	if (bfmeAsk1013()) {
		g_bfmeLog1013->bfmeLog1013(m_bfmeId, g_bfmeFmt1013, 0, 0, 0, 0, 0, 0);
		m_bfmeState = 9;
	} else {
		m_bfmeState = 1;
	}
}
