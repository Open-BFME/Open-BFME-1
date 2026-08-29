// Open-BFME5 conversions.

extern "C" void *bfmeVft1029A[];

class BfmeA1029
{
public:
	BfmeA1029 *bfmeGo1029A(int a);
	void bfmeBase1029(int n, int m);

	void *m_bfmeVfptr;
	char m_bfmePad[0x1c];
	int m_bfmeVal;
};

BfmeA1029 *BfmeA1029::bfmeGo1029A(int a)
{
	bfmeBase1029(9, 8);
	m_bfmeVal = a;
	m_bfmeVfptr = bfmeVft1029A;
	return this;
}

class BfmeSub1029
{
public:
	void bfmeInit1029(void);
};

class BfmeB1029
{
public:
	BfmeB1029 *bfmeGo1029B(void);

	char m_bfmeFlag;
	char m_bfmePad[3];
	BfmeSub1029 m_bfmeSub;
	char m_bfmePad2[0xb];
	int m_bfmeX;
	int m_bfmeY;
};

BfmeB1029 *BfmeB1029::bfmeGo1029B(void)
{
	m_bfmeFlag = 0;
	m_bfmeSub.bfmeInit1029();
	m_bfmeX = 0;
	m_bfmeY = 0;
	return this;
}

extern char g_bfmeFmt1029[];
int bfmeCount1029(int a, int b, char *f, int n);

class BfmeC1029
{
public:
	int bfmeGo1029C(void);

	char m_bfmePad[0x14];
	int m_bfmeB;
	int m_bfmeA;
};

int BfmeC1029::bfmeGo1029C(void)
{
	return bfmeCount1029(0, m_bfmeA, g_bfmeFmt1029, 0x54) + m_bfmeB + 1;
}

void bfmeNote1029(int i, char v);

class BfmeD1029
{
public:
	void bfmeGo1029D(int i, char v);

	char m_bfmePad[0x18];
	char m_bfmeBuf[1];
};

void BfmeD1029::bfmeGo1029D(int i, char v)
{
	bfmeNote1029(i, v);
	m_bfmeBuf[i] = v;
}

void bfmeCopy1029(char *d, int n, char *s);

class BfmeE1029
{
public:
	void bfmeGo1029E(char *s, int n);

	char m_bfmePad[8];
	char m_bfmeBuf[0x1c];
	int m_bfmeN;
};

void BfmeE1029::bfmeGo1029E(char *s, int n)
{
	bfmeCopy1029(m_bfmeBuf, 0x1c, s);
	m_bfmeN = n;
}
