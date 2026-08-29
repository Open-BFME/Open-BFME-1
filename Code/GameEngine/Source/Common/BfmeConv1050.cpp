// Open-BFME5 conversions.

void bfmeReset1050(int n);

class BfmeA1050
{
public:
	void bfmeGo1050A(void);

	char m_bfmePad[8];
	int m_bfme08;
	char m_bfmePad2[0x55];
	char m_bfmeFlag;
	char m_bfmePad3[0xc6];
	int m_bfme128;
};

void BfmeA1050::bfmeGo1050A(void)
{
	m_bfmeFlag = 0;
	bfmeReset1050(0);
	m_bfme08 = 0;
	m_bfme128 = 0;
}

extern "C" void *bfmeVft1050B[];

class BfmeB1050
{
public:
	BfmeB1050 *bfmeGo1050B(void);
	void bfmeBase1050(void);

	void *m_bfmeVfptr;
	char m_bfmePad[0x54];
	int m_bfme58;
	int m_bfme5c;
	float m_bfme60;
	char m_bfme64;
};

BfmeB1050 *BfmeB1050::bfmeGo1050B(void)
{
	bfmeBase1050();

	int z = 0;

	m_bfme58 = z;
	m_bfme5c = z;
	m_bfme64 = (char)z;
	m_bfme60 = 20.0f;
	m_bfmeVfptr = bfmeVft1050B;
	return this;
}

class BfmeP1050
{
public:
	void bfmeFwd1050(int a, int b, int c, int d, int e);
};

class BfmeC1050
{
public:
	void bfmeGo1050C(int a, int b, int c, int d, int e);

	char m_bfmePad[0xc];
	BfmeP1050 *m_bfmeP;
};

void BfmeC1050::bfmeGo1050C(int a, int b, int c, int d, int e)
{
	m_bfmeP->bfmeFwd1050(a, c, b, d, e);
}

extern "C" void *bfmeVft1050F[];

class BfmeF1050
{
public:
	BfmeF1050 *bfmeGo1050F(int a, int b, int c);
	void bfmeBaseF1050(int a, int b, int c);

	void *m_bfmeVfptr;
};

BfmeF1050 *BfmeF1050::bfmeGo1050F(int a, int b, int c)
{
	bfmeBaseF1050(a, b, c);
	m_bfmeVfptr = bfmeVft1050F;
	return this;
}

