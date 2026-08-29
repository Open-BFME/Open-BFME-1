// Open-BFME5 conversions.

class BfmeA1020
{
public:
	virtual void bfmeVA01020();
	virtual void bfmeVA11020();
	virtual void bfmeVA21020();
	virtual void bfmeVA31020();
	virtual void bfmeVA41020();
	virtual void bfmeVA51020();
	virtual void bfmeVA61020();
	virtual void bfmeVA71020();
	virtual void bfmeVA81020();
	virtual void bfmeVA91020();
	virtual void bfmeVA101020();
	virtual void bfmeVA111020();
	virtual void bfmeVA121020();
	virtual void bfmeVA131020();
	virtual void bfmeVA141020();
	virtual void bfmeVA151020();
	virtual void bfmeVA161020();
	virtual void bfmeVA171020();
	virtual void bfmeVA181020();
	virtual void bfmeVA191020();
	virtual void bfmeVA201020();
	virtual void bfmeVA211020();
	virtual void bfmeVA221020();
	virtual void bfmeVA231020();
	virtual void bfmeVA241020();
	virtual void bfmeVA251020();
	virtual void bfmeVA261020();
	virtual void bfmeVA271020();
	virtual void bfmeVA281020();
	virtual void bfmeVA291020();
	virtual void bfmeVA301020();
	virtual void bfmeVA311020();
	virtual void bfmeVA321020();
	virtual void bfmeVA331020();
	virtual void bfmeVA341020();
	virtual void bfmeVA351020();
	virtual void bfmeVA361020();
	virtual void bfmeVA371020();
	virtual void bfmeVA381020();
	virtual void bfmeVA391020();
	virtual void bfmeVA401020();
	virtual void bfmeVA411020();
	virtual void bfmeVA421020();
	virtual void bfmeVA431020();
	virtual void bfmeVA441020();
	virtual void bfmeVA451020();
	virtual void bfmeVA461020();
	virtual void bfmeVA471020();
	virtual void bfmeVA481020();
	virtual void bfmeVA491020();
	virtual void bfmeVA501020();
	virtual void bfmeVA511020();
	virtual void bfmeVA521020();
	virtual void bfmeVA531020();
	virtual void bfmeVA541020();
	virtual void bfmeVA551020();
	virtual void bfmeVA561020();
	virtual void bfmeVA571020();
	virtual void bfmeVA581020();
	virtual void bfmeClear1020();
};

extern BfmeA1020 *g_bfmeA1020;

class BfmeG1020
{
public:
	void bfmeGo1020G(void);

	char m_bfmePad[8];
	int m_bfmeVal;
};

void BfmeG1020::bfmeGo1020G(void)
{
	g_bfmeA1020->bfmeClear1020();
	m_bfmeVal = 0;
}

class BfmeH1020
{
public:
	void bfmeGo1020H(void);

	char m_bfmePad[8];
	int m_bfmeVal;
	char m_bfmePad2[4];
	char m_bfmeFlag;
};

void BfmeH1020::bfmeGo1020H(void)
{
	g_bfmeA1020->bfmeClear1020();

	int z = 0;

	m_bfmeFlag = (char)z;
	m_bfmeVal = z;
}

class BfmeJ1020
{
public:
	void bfmeSet1020(int a, bool on);
};

extern BfmeJ1020 *g_bfmeJ1020;

int bfmeGo1020I(int a, void *b)
{
	g_bfmeJ1020->bfmeSet1020(a, b != 0);
	return 1;
}

class BfmeLog1020
{
public:
	void bfmeSend1020(int m);
};

extern BfmeLog1020 *g_bfmeLog1020;
extern int g_bfmeMsg1020;
extern char g_bfmeC1020;
extern char g_bfmeD1020;

void bfmeGo1020K(void)
{
	g_bfmeLog1020->bfmeSend1020(g_bfmeMsg1020);
	g_bfmeC1020 = 1;
	g_bfmeD1020 = 0;
}

class BfmeM1020;

class BfmeN1020
{
public:
	virtual void bfmeVN01020();
	virtual void bfmeVN11020();
	virtual void bfmeVN21020();
	virtual void bfmeVN31020();
	virtual void bfmeVN41020();
	virtual void bfmeVN51020();
	virtual void bfmeVN61020();
	virtual void bfmeVN71020();
	virtual void bfmeVN81020();
	virtual void bfmeVN91020();
	virtual void bfmeVN101020();
	virtual void bfmeVN111020();
	virtual void bfmeVN121020();
	virtual void bfmeVN131020();
	virtual void bfmeVN141020();
	virtual void bfmeVN151020();
	virtual void bfmeVN161020();
	virtual void bfmeVN171020();
	virtual void bfmeVN181020();
	virtual void bfmeVN191020();
	virtual void bfmeVN201020();
	virtual void bfmeVN211020();
	virtual void bfmeVN221020();
	virtual void bfmeVN231020();
	virtual void bfmeVN241020();
	virtual void bfmeVN251020();
	virtual void bfmeVN261020();
	virtual void bfmeVN271020();
	virtual void bfmeVN281020();
	virtual void bfmeVN291020();
	virtual void bfmeVN301020();
	virtual void bfmeVN311020();
	virtual void bfmeVN321020();
	virtual void bfmeVN331020();
	virtual void bfmeVN341020();
	virtual void bfmeVN351020();
	virtual void bfmeVN361020();
	virtual void bfmeVN371020();
	virtual void bfmeVN381020();
	virtual void bfmeVN391020();
	virtual void bfmeVN401020();
	virtual void bfmeVN411020();
	virtual void bfmeVN421020();
	virtual void bfmeVN431020();
	virtual void bfmeReg1020(BfmeM1020 *p);
};

extern BfmeN1020 *g_bfmeN1020;

class BfmeM1020
{
public:
	void bfmeGo1020M(int unused);

	char m_bfmePad[0x258];
	int m_bfmeState;
};

void BfmeM1020::bfmeGo1020M(int unused)
{
	g_bfmeN1020->bfmeReg1020(this);
	m_bfmeState = 1;
}
