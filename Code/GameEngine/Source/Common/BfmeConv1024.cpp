// Open-BFME5 conversions.

class BfmeV1024;

class BfmeM1024
{
public:
	BfmeV1024 *bfmeFind1024(int h);
};

extern BfmeM1024 *g_bfmeM1024;

class BfmeSlots1024
{
public:
	BfmeV1024 **bfmeSlot1024(int k);
};

class BfmeA1024
{
public:
	void bfmeGo1024A(int k, int h);

	char m_bfmePad[0x6c];
	BfmeSlots1024 m_bfmeMap;
};

void BfmeA1024::bfmeGo1024A(int k, int h)
{
	BfmeV1024 *v = g_bfmeM1024->bfmeFind1024(h);

	if (v != 0)
		*m_bfmeMap.bfmeSlot1024(k) = v;
}

class BfmeN1024
{
public:
	void bfmeDrop1024(int id);
};

extern BfmeN1024 *g_bfmeN1024;

class BfmeList1024
{
public:
	void bfmeClear1024(void);

	void *m_bfmeHead;
	char m_bfmePad[8];
};

class BfmeB1024
{
public:
	void bfmeGo1024B(void);

	char m_bfmePad[0x14];
	BfmeList1024 m_bfmeList;
	int m_bfmeId;
};

void BfmeB1024::bfmeGo1024B(void)
{
	if (m_bfmeList.m_bfmeHead != 0) {
		g_bfmeN1024->bfmeDrop1024(m_bfmeId);
		m_bfmeList.bfmeClear1024();
		m_bfmeId = 0;
	}
}

class BfmeG1024
{
public:
	virtual void bfmeVG01024();
	virtual void bfmeVG11024();
	virtual void bfmeVG21024();
	virtual void bfmeVG31024();
	virtual void bfmeVG41024();
	virtual void bfmeVG51024();
	virtual void bfmeVG61024();
	virtual void bfmeVG71024();
	virtual void bfmeVG81024();
	virtual void bfmeVG91024();
	virtual void bfmeVG101024();
	virtual void bfmeVG111024();
	virtual void bfmeVG121024();
	virtual void bfmeVG131024();
	virtual void bfmeVG141024();
	virtual void bfmeVG151024();
	virtual void bfmeVG161024();
	virtual void bfmeVG171024();
	virtual void bfmeVG181024();
	virtual void bfmeKill1024(int v);
};

extern BfmeG1024 *g_bfmeG1024;

class BfmeH1024
{
public:
	void bfmeAdd1024(int a, int b);

	char m_bfmePad[8];
	int m_bfmeVal;
};

class BfmeC1024
{
public:
	void bfmeGo1024C(void);

	char m_bfmePad[0xc];
	int m_bfmeH;
};

void BfmeC1024::bfmeGo1024C(void)
{
	if (g_bfmeG1024 != 0) {
		g_bfmeG1024->bfmeKill1024(m_bfmeH);
		m_bfmeH = 1;
	}

	((BfmeH1024 *)((char *)this - 0x20))->bfmeAdd1024(
		((BfmeH1024 *)((char *)this - 0x20))->m_bfmeVal, 0x3fffffff);
}

class BfmeTab1024
{
public:
	int bfmeFind1024(int k);
	void bfmeAdd1024(int k, int v);
};

struct BfmeMap1024
{
	char m_bfmePad[8];
	BfmeTab1024 m_bfmeTab;
};

extern BfmeMap1024 *g_bfmeMap1024;

class BfmeD1024
{
public:
	char bfmeGo1024D(int unused, int k, int v);

	char m_bfmePad[8];
	BfmeTab1024 m_bfmeOwn;
};

char BfmeD1024::bfmeGo1024D(int unused, int k, int v)
{
	if (g_bfmeMap1024->m_bfmeTab.bfmeFind1024(k) == 0)
		m_bfmeOwn.bfmeAdd1024(k, v);

	return 1;
}

class BfmeE1024;

class BfmeP1024
{
public:
	void bfmeReg1024(BfmeE1024 *p);
};

extern BfmeP1024 *g_bfmeP1024;

class BfmeE1024
{
public:
	void bfmeGo1024E(void);

	char m_bfmePad[4];
	int m_bfmeFlags;
};

void BfmeE1024::bfmeGo1024E(void)
{
	if ((m_bfmeFlags & 0xff0000) == 0x70000)
		return;

	if (g_bfmeP1024 == 0)
		return;

	g_bfmeP1024->bfmeReg1024(this);
}

struct BfmeRec1024
{
	char m_bfmePad[0x344];
	char m_bfmeFlags;
};

class BfmeStore1024
{
public:
	BfmeRec1024 *bfmeFind1024S(int id);
};

extern BfmeStore1024 *g_bfmeStore1024;

class BfmeF1024
{
public:
	char bfmeGo1024F(void);

	char m_bfmePad[0x20];
	int m_bfmeId;
};

char BfmeF1024::bfmeGo1024F(void)
{
	int id = m_bfmeId;

	if (id == 0)
		return 0;

	BfmeRec1024 *r = g_bfmeStore1024->bfmeFind1024S(id);

	if (r == 0)
		return 1;

	char f = r->m_bfmeFlags;

	f &= 1;
	return f;
}
