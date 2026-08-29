// Open-BFME5 conversions.

class BfmeTab1052
{
public:
	char bfmeHas1052(int a, int v);
};

struct BfmeD1052
{
	char m_bfmePad[0x118];
	BfmeTab1052 m_bfmeTab;
};

class BfmeE1052
{
public:
	int bfmeGet1052(void);
};

class BfmeC1052
{
public:
	char bfmeGo1052C(int a, int b);
};

char BfmeC1052::bfmeGo1052C(int a, int b)
{
	BfmeD1052 *d = *(BfmeD1052 **)((char *)this - 0x1c);
	int v = (*(BfmeE1052 **)((char *)this - 0x18))->bfmeGet1052();

	return (char)(d->m_bfmeTab.bfmeHas1052(a, v) != 0);
}

class BfmeSubF1052
{
public:
	virtual void bfmeVS01052();
	virtual void bfmeVS11052();
	virtual void bfmeVS21052();
	virtual void bfmeTick1052();
	void bfmeStep1052(void);
};

struct BfmeG1052
{
	char m_bfmePad[0x18];
	int m_bfme18;
};

class BfmeF1052
{
public:
	char bfmeGo1052F(BfmeG1052 *p, int v);

	char m_bfmePad[0x16c];
	BfmeSubF1052 m_bfmeSub;
};

char BfmeF1052::bfmeGo1052F(BfmeG1052 *p, int v)
{
	p->m_bfme18 = v;
	m_bfmeSub.bfmeStep1052();
	m_bfmeSub.bfmeTick1052();
	return 1;
}

class BfmeI1052
{
public:
	int bfmeFind1052(char *n, int f);
};

extern char g_bfmeName1052[];

class BfmeH1052
{
public:
	void bfmeGo1052H(BfmeI1052 *p);
	void bfmeDo1052(int a, BfmeI1052 *p, int r);
};

void BfmeH1052::bfmeGo1052H(BfmeI1052 *p)
{
	bfmeDo1052(0, p, p->bfmeFind1052(g_bfmeName1052, 0));
}

class BfmeK1052
{
public:
	virtual void bfmeVK01052();
	virtual void bfmeVK11052();
	virtual void bfmeVK21052();
	virtual void bfmeVK31052();
	virtual void bfmeVK41052();
	virtual void bfmeVK51052();
	virtual void bfmeVK61052();
	virtual void bfmeVK71052();
	virtual void bfmeQuery1052(int a, int *t);
};

extern BfmeK1052 *g_bfmeK1052;

class BfmeJ1052
{
public:
	void bfmeGo1052J(int a);
	void bfmeUse1052(int *t);
};

void BfmeJ1052::bfmeGo1052J(int a)
{
	int t[3];

	g_bfmeK1052->bfmeQuery1052(a, t);
	bfmeUse1052(t);
}

extern "C" void bfmeHook1052(void);

struct BfmeM1052
{
	char m_bfmePad[0xc];
	int m_bfmeVal;
	char m_bfmePad2[4];
	char m_bfmeFlag;
};

class BfmeN1052
{
public:
	void bfmeReg1052(int *p, void (*fn)(void));
};

extern BfmeN1052 *g_bfmeN1052;

class BfmeL1052
{
public:
	void bfmeGo1052L(BfmeM1052 *p);
	void bfmeTail1052(BfmeM1052 *p);

	char m_bfmePad[0x44];
	char m_bfmeFlag;
};

void BfmeL1052::bfmeGo1052L(BfmeM1052 *p)
{
	g_bfmeN1052->bfmeReg1052(&p->m_bfmeVal, bfmeHook1052);
	m_bfmeFlag = p->m_bfmeFlag;
	bfmeTail1052(p);
}
