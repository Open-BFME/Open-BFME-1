// Open-BFME5 conversions.

class BfmeB1025
{
public:
	virtual void bfmeVB01025();
	virtual void bfmeVB11025();
	virtual void bfmeVB21025();
	virtual void bfmeVB31025();
	virtual void bfmeVB41025();
	virtual void bfmeVB51025();
	virtual void bfmeVB61025();
	virtual void bfmeVB71025();
	virtual void bfmeVB81025();
	virtual void bfmeVB91025();
	virtual void bfmeVB101025();
	virtual void bfmeVB111025();
	virtual void bfmeVB121025();
	virtual void bfmeVB131025();
	virtual void bfmeVB141025();
	virtual void bfmeVB151025();
	virtual void bfmeVB161025();
	virtual void bfmeVB171025();
	virtual void bfmeVB181025();
	virtual void bfmeVB191025();
	virtual void bfmeVB201025();
	virtual void bfmeVB211025();
	virtual void bfmeVB221025();
	virtual void bfmeVB231025();
	virtual void bfmeVB241025();
	virtual void bfmeVB251025();
	virtual void bfmeVB261025();
	virtual void bfmeVB271025();
	virtual void bfmeVB281025();
	virtual void bfmeVB291025();
	virtual void bfmeVB301025();
	virtual void bfmeVB311025();
	virtual void bfmeVB321025();
	virtual void bfmeVB331025();
	virtual void bfmeVB341025();
	virtual void bfmeVB351025();
	virtual void bfmeVB361025();
	virtual void bfmeVB371025();
	virtual void bfmeVB381025();
	virtual void bfmeVB391025();
	virtual void bfmeVB401025();
	virtual void bfmeVB411025();
	virtual void bfmeVB421025();
	virtual void bfmeVB431025();
	virtual void bfmeVB441025();
	virtual void bfmeVB451025();
	virtual void bfmeVB461025();
	virtual void bfmeVB471025();
	virtual void bfmeVB481025();
	virtual void bfmeVB491025();
	virtual void bfmeVB501025();
	virtual void bfmeVB511025();
	virtual void bfmeVB521025();
	virtual void bfmeVB531025();
	virtual void bfmeVB541025();
	virtual void bfmeVB551025();
	virtual void bfmeVB561025();
	virtual void bfmeVB571025();
	virtual void bfmeFree1025(int h);
};

extern BfmeB1025 *g_bfmeB1025;

class BfmeA1025
{
public:
	void bfmeGo1025A(void);

	char m_bfmePad[0x54];
	int m_bfmeH;
};

void BfmeA1025::bfmeGo1025A(void)
{
	if (g_bfmeB1025 != 0 && m_bfmeH != 0) {
		g_bfmeB1025->bfmeFree1025(m_bfmeH);
		m_bfmeH = 0;
	}
}

struct BfmeK1025
{
	char m_bfmePad[0x24];
	int m_bfmeKey;
};

class BfmeD1025
{
public:
	unsigned short bfmeLookup1025(int k, int a, int b);
};

extern BfmeD1025 *g_bfmeD1025;

class BfmeC1025
{
public:
	int bfmeGo1025C(void);

	char m_bfmePad[0xc];
	void *m_bfmeA;
	BfmeK1025 *m_bfmeB;
};

int BfmeC1025::bfmeGo1025C(void)
{
	if (m_bfmeA != 0 && m_bfmeB != 0)
		return g_bfmeD1025->bfmeLookup1025(m_bfmeB->m_bfmeKey, 4, 0);

	return 0;
}

class BfmeP1025
{
public:
	char bfmeSay1025(char *t);
};

extern BfmeP1025 *g_bfmeP1025;
extern char g_bfmeLit1025[];

struct BfmeR1025
{
	char *m_bfmeName;
};

char bfmeGo1025F(BfmeR1025 *p)
{
	if (g_bfmeP1025 != 0) {
		char *t;

		if (p->m_bfmeName != 0)
			t = p->m_bfmeName + 8;
		else
			t = g_bfmeLit1025;

		return g_bfmeP1025->bfmeSay1025(t);
	}

	return 0;
}

class BfmeH1025
{
public:
	int bfmeVal1025(void);
};

extern BfmeH1025 *g_bfmeH1025;
extern char g_bfmeFmt1025[];
__declspec(dllimport) void __cdecl bfmePrint1025(int a, char *f, int b);

void __stdcall bfmeGo1025G(int unused, int b, char skip)
{
	if (skip != 0)
		return;

	if (g_bfmeH1025 == 0)
		return;

	bfmePrint1025(b, g_bfmeFmt1025, g_bfmeH1025->bfmeVal1025());
}

class BfmeT1025
{
public:
	char bfmeTest1025(void *h, int a);
};

struct BfmeOwner1025
{
	char m_bfmePad[8];
	BfmeT1025 m_bfmeTab;
};

class BfmeStore1025
{
public:
	void bfmeDo1025(void *h);
};

extern BfmeStore1025 *g_bfmeStore1025;

class BfmeS1025
{
public:
	void bfmeGo1025S(int a);
};

void BfmeS1025::bfmeGo1025S(int a)
{
	void *h = *(void **)((char *)this - 8);
	BfmeOwner1025 *o = *(BfmeOwner1025 **)((char *)this - 0xc);

	if (o->m_bfmeTab.bfmeTest1025(h, a) != 0)
		g_bfmeStore1025->bfmeDo1025(*(void **)((char *)this - 8));
}
