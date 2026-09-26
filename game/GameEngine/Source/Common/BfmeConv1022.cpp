// Open-BFME5 conversions.

struct BfmeElem1022
{
	void *m_bfmeP;
	char m_bfmePad[0x14];
};

struct BfmeTab1022
{
	char m_bfmePad[0x1c];
	BfmeElem1022 m_bfmeItems[1];
};

class BfmeE1022
{
public:
	void bfmeDrop1022(int n, void *p);
};

extern BfmeE1022 *g_bfmeE1022;

class BfmeD1022
{
public:
	void bfmeGo1022D(int unused);

	BfmeTab1022 *m_bfmeTab;
	int m_bfmeIdx;
};

void BfmeD1022::bfmeGo1022D(int unused)
{
	void *p = m_bfmeTab->m_bfmeItems[m_bfmeIdx].m_bfmeP;

	if (p != 0)
		g_bfmeE1022->bfmeDrop1022(0, p);
}

class BfmeG1022
{
public:
	virtual void bfmeVG01022();
	virtual void bfmeVG11022();
	virtual void bfmeVG21022();
	virtual void bfmeVG31022();
	virtual void bfmeVG41022();
	virtual void bfmeVG51022();
	virtual void bfmeVG61022();
	virtual void bfmeVG71022();
	virtual void bfmeVG81022();
	virtual void bfmeVG91022();
	virtual void bfmeVG101022();
	virtual void bfmeVG111022();
	virtual void bfmeVG121022();
	virtual void bfmeVG131022();
	virtual void bfmeVG141022();
	virtual void bfmeVG151022();
	virtual void bfmeVG161022();
	virtual void bfmeVG171022();
	virtual void bfmeVG181022();
	virtual void bfmeKill1022(int h);
};

extern BfmeG1022 *g_bfmeG1022;

class BfmeF1022
{
public:
	int bfmeGo1022F(void);

	char m_bfmePad[0x1c];
	int m_bfmeH;
};

int BfmeF1022::bfmeGo1022F(void)
{
	if (g_bfmeG1022 != 0) {
		g_bfmeG1022->bfmeKill1022(m_bfmeH);
		m_bfmeH = 1;
	}

	return 0x3fffffff;
}

class BfmeN1022
{
public:
	virtual void bfmeVN01022();
	virtual void bfmeVN11022();
	virtual void bfmeVN21022();
	virtual void bfmeVN31022();
	virtual void bfmeVN41022();
	virtual void bfmeVN51022();
	virtual void bfmeVN61022();
	virtual void bfmeVN71022();
	virtual void bfmeVN81022();
	virtual void bfmeVN91022();
	virtual void bfmeVN101022();
	virtual void bfmeVN111022();
	virtual void bfmeVN121022();
	virtual void bfmeVN131022();
	virtual void bfmeVN141022();
	virtual void bfmeVN151022();
	virtual void bfmeVN161022();
	virtual void bfmeVN171022();
	virtual void bfmeVN181022();
	virtual void bfmeVN191022();
	virtual void bfmeVN201022();
	virtual void bfmeVN211022();
	virtual void bfmeVN221022();
	virtual void bfmeVN231022();
	virtual void bfmeVN241022();
	virtual void bfmeVN251022();
	virtual void bfmeVN261022();
	virtual void bfmeVN271022();
	virtual void bfmeVN281022();
	virtual void bfmeVN291022();
	virtual void bfmeVN301022();
	virtual void bfmeVN311022();
	virtual void bfmeVN321022();
	virtual void bfmeVN331022();
	virtual void bfmeVN341022();
	virtual void bfmeVN351022();
	virtual void bfmeVN361022();
	virtual void bfmeVN371022();
	virtual void bfmeVN381022();
	virtual void bfmeVN391022();
	virtual void bfmeVN401022();
	virtual void bfmeVN411022();
	virtual void bfmeVN421022();
	virtual void bfmeVN431022();
	virtual void bfmeReg1022(void *p);
	virtual void bfmeVN451022();
	virtual void bfmeVN461022();
	virtual void bfmeVN471022();
	virtual void bfmeVN481022();
	virtual void bfmeVN491022();
	virtual void bfmeVN501022();
	virtual void bfmeVN511022();
	virtual void bfmeVN521022();
	virtual void bfmeQuery1022(int h, int k, int f, int *out);
};

extern BfmeN1022 *g_bfmeN1022;

class BfmeI1022
{
public:
	void bfmeGo1022I(void);

	char m_bfmePad[0x50];
	void *m_bfmeP;
	char m_bfmePad2[0x44];
	char m_bfmeDone;
};

void BfmeI1022::bfmeGo1022I(void)
{
	if (m_bfmeDone == 0) {
		m_bfmeDone = 1;
		g_bfmeN1022->bfmeReg1022(m_bfmeP);
	}
}

class BfmeK1022
{
public:
	virtual void bfmeVK01022();
	virtual void bfmeVK11022();
	virtual void bfmeVK21022();
	virtual void bfmeSend1022(int n);
};

extern BfmeK1022 *g_bfmeK1022;

class BfmeJ1022
{
public:
	void bfmeGo1022J(int unused);

	char m_bfmePad[0x3c];
	int m_bfmeState;
	char m_bfmePad2[0x16];
	char m_bfmeFlag;
};

void BfmeJ1022::bfmeGo1022J(int unused)
{
	m_bfmeState = 2;

	if (m_bfmeFlag != 0) {
		m_bfmeFlag = 0;
		g_bfmeK1022->bfmeSend1022(0);
	}
}

int bfmeGo1022L(int h)
{
	if (h == 0)
		return -1;

	g_bfmeN1022->bfmeQuery1022(h, 0x402b, 0, &h);
	return h;
}
