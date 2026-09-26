// Open-BFME5 conversions.

class BfmeSubA1034
{
public:
	void bfmeAdd1034(int b);
};

struct BfmeX1034
{
	char m_bfmePad[4];
	BfmeSubA1034 m_bfmeSub;
};

BfmeX1034 * __stdcall bfmeFind1034(int a, int n);

void __stdcall bfmeGo1034A(int a, int b)
{
	BfmeX1034 *x = bfmeFind1034(a, 0);

	if (x != 0)
		x->m_bfmeSub.bfmeAdd1034(b);
}

class BfmeZ1034
{
public:
	void bfmeSet1034(char on);
};

struct BfmeW1034
{
	char m_bfmePad[0x204];
	BfmeZ1034 *m_bfmeZ;
};

struct BfmeV1034
{
	char m_bfmePad[0x70];
	char m_bfmeFlag;
};

class BfmeC1034
{
public:
	void bfmeGo1034C(void);
};

void BfmeC1034::bfmeGo1034C(void)
{
	BfmeZ1034 *z = (*(BfmeW1034 **)((char *)this - 8))->m_bfmeZ;

	if (z != 0)
		z->bfmeSet1034((char)((*(BfmeV1034 **)((char *)this - 0xc))->m_bfmeFlag == 0));
}

char bfmeTest1034(int a);

class BfmeD1034
{
public:
	void bfmeGo1034D(int a);

	char m_bfmePad[8];
	char m_bfmeFlag;
	char m_bfmePad2[3];
	int m_bfmeVal;
};

void BfmeD1034::bfmeGo1034D(int a)
{
	if (bfmeTest1034(a) != 0) {
		m_bfmeFlag = 1;
		m_bfmeVal = a;
	}
}

struct BfmeRc1034
{
	unsigned short m_bfmeCount;
};

struct BfmeAlloc1034
{
	void *m_bfmePad;
	void (__cdecl *m_bfmeFree)(BfmeRc1034 *r);
};

extern BfmeAlloc1034 *g_bfmeAlloc1034;

class BfmeE1034
{
public:
	void bfmeGo1034E(void);

	BfmeRc1034 *m_bfmeRc;
};

void BfmeE1034::bfmeGo1034E(void)
{
	BfmeRc1034 *r = m_bfmeRc;

	if (--r->m_bfmeCount == 0)
		g_bfmeAlloc1034->m_bfmeFree(r);

	m_bfmeRc = 0;
}

class BfmeN1034
{
public:
	int bfmeVal1034(void);
};

class BfmeTab1034
{
public:
	BfmeN1034 *bfmeFind1034F(int k);
};

class BfmeF1034
{
public:
	int bfmeGo1034F(int k);

	char m_bfmePad[8];
	BfmeTab1034 *m_bfmeTab;
};

int BfmeF1034::bfmeGo1034F(int k)
{
	BfmeN1034 *n = m_bfmeTab->bfmeFind1034F(k);

	if (n != 0)
		return n->bfmeVal1034();

	return -1;
}

class BfmeH1034
{
public:
	void bfmeStep1034(void);
};

class BfmeG1034
{
public:
	void bfmeGo1034G(void);

	char m_bfmePad[0x14];
	BfmeH1034 *m_bfmeArr[0x20];
};

void BfmeG1034::bfmeGo1034G(void)
{
	BfmeH1034 **p = m_bfmeArr;
	int n = 0x20;

	do {
		(*p)->bfmeStep1034();
		p++;
	} while (--n != 0);
}

