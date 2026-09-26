// Open-BFME5 conversions.

class BfmeE988;

class BfmeReg988
{
public:
	void bfmeDrop988(BfmeE988 *e);
};

extern BfmeReg988 *g_bfmeReg988;

class BfmeE988
{
public:
	void bfmeGo988A();
	void bfmeGo988B();
	void bfmeSet988(int a, int b);

	char m_bfmePad[8];
	int m_bfmeVal;
	char m_bfmePad2[0x59];
	char m_bfmeOn;
};

void BfmeE988::bfmeGo988A()
{
	if (m_bfmeOn) {
		g_bfmeReg988->bfmeDrop988(this);
		bfmeSet988(m_bfmeVal, 0x3fffffff);
		m_bfmeOn = 0;
	}
}

void BfmeE988::bfmeGo988B()
{
	if (m_bfmeOn) {
		g_bfmeReg988->bfmeDrop988(this);
		bfmeSet988(m_bfmeVal, 0x3fffffff);
		m_bfmeOn = 0;
	}
}

class BfmeUnit988
{
public:
	void bfmeReset988D();

	char m_bfmePad[0x198];
	int m_bfmeA;
	int m_bfmeB;
	char m_bfmePad2[0x188];
	char m_bfmeFlag;
};

struct BfmeHold988
{
	char m_bfmePad[0x204];
	BfmeUnit988 *m_bfmeUnit;
};

struct BfmeOwner988
{
	char m_bfmePad[0x10];
	BfmeHold988 *m_bfmeHold;
};

class BfmeD988
{
public:
	void bfmeGo988D(int a);
	void bfmeBase988D(int a);

	char m_bfmePad[0x1c];
	BfmeOwner988 *m_bfmeOwner;
};

void BfmeD988::bfmeGo988D(int a)
{
	bfmeBase988D(a);

	BfmeUnit988 *u = m_bfmeOwner->m_bfmeHold->m_bfmeUnit;

	if (u) {
		u->bfmeReset988D();
		u->m_bfmeFlag = 0;
		u->m_bfmeA = 0;
		u->m_bfmeB = 0;
	}
}
