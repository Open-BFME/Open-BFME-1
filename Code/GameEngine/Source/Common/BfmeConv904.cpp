// Open-BFME5 conversions.

struct BfmeSlotMA
{
	int m_bfmeVal;
	char m_bfmePad[0x14];
};

class BfmeThingMA
{
public:
	char bfmeGoMA(int i);
	char m_bfmePad[0x2bc];
	int m_bfmeCur;
	BfmeSlotMA m_bfmeArr[17];
};

char BfmeThingMA::bfmeGoMA(int i)
{
	if (i >= 0 && i < 0x11)
		return (char)(m_bfmeArr[i].m_bfmeVal != m_bfmeCur);
	return 0;
}

class BfmeGlobMB
{
public:
	void bfmeDoMB(int f, void *p);
};

extern BfmeGlobMB *g_bfmeGlobMB;

struct BfmeSlotMB
{
	void *m_bfmeP;
	char m_bfmePad[0x14];
};

struct BfmeTabMB
{
	char m_bfmePad[0x1c];
	BfmeSlotMB m_bfmeArr[1];
};

class BfmeThingMB
{
public:
	void bfmeGoMB(void *a);
	char m_bfmePad[8];
	BfmeTabMB *m_bfmeTab;
	int m_bfmeIdx;
};

void BfmeThingMB::bfmeGoMB(void *a)
{
	void *p = m_bfmeTab->m_bfmeArr[m_bfmeIdx].m_bfmeP;
	if (p)
		g_bfmeGlobMB->bfmeDoMB(0, p);
}

class BfmeGlobMC
{
public:
	virtual void bfmeSlotMC00();
	virtual void bfmeSlotMC01();
	virtual void bfmeSlotMC02();
	virtual void bfmeSlotMC03();
	virtual void bfmeSlotMC04();
	virtual void bfmeSlotMC05();
	virtual void bfmeSlotMC06();
	virtual void bfmeSlotMC07();
	virtual void bfmeSlotMC08();
	virtual void bfmeSlotMC09();
	virtual void bfmeSlotMC10();
	virtual void bfmeSlotMC11();
	virtual void bfmeSlotMC12();
	virtual void bfmeSlotMC13();
	virtual void bfmeSlotMC14();
	virtual void bfmeSlotMC15();
	virtual void bfmeSlotMC16();
	virtual void bfmeSlotMC17();
	virtual void bfmeSlotMC18();
	virtual void bfmeSlotMC19();
	virtual void bfmeSlotMC20();
	virtual void bfmeSlotMC21();
	virtual void bfmeSlotMC22();
	virtual void bfmeSlotMC23();
	virtual void bfmeSlotMC24();
	virtual void bfmeSlotMC25();
	virtual void bfmeSlotMC26();
	virtual void bfmeSlotMC27();
	virtual void bfmeSlotMC28();
	virtual void bfmeSlotMC29();
	virtual void bfmeSlotMC30();
	virtual void bfmeSlotMC31();
	virtual void bfmeSlotMC32();
	virtual void bfmeSlotMC33();
	virtual void bfmeSlotMC34();
	virtual void bfmeSlotMC35();
	virtual void bfmeSlotMC36();
	virtual void bfmeSlotMC37();
	virtual void bfmeSlotMC38();
	virtual void bfmeSlotMC39();
	virtual void bfmeSlotMC40();
	virtual void bfmeSlotMC41();
	virtual void bfmeSlotMC42();
	virtual void bfmeSlotMC43();
	virtual bool bfmeCheckMC(void *a);
};

extern BfmeGlobMC *g_bfmeGlobMC;

class BfmeThingMC
{
public:
	int bfmeGoMC();
	char m_bfmePad[0x64];
	void *m_bfmeArg;
};

int BfmeThingMC::bfmeGoMC()
{
	if (g_bfmeGlobMC) {
		if (g_bfmeGlobMC->bfmeCheckMC(m_bfmeArg))
			return 1;
	}
	return 0;
}

class BfmeObjMD
{
public:
	void bfmeOneMD(int v);
	void bfmeTwoMD();
};

extern char g_bfmeFlagMD;
extern int g_bfmeValMD;
extern BfmeObjMD *g_bfmeObjMD;

void bfmeGoMD(void)
{
	if (g_bfmeFlagMD) {
		g_bfmeObjMD->bfmeOneMD(g_bfmeValMD);
		g_bfmeObjMD->bfmeTwoMD();
	}
}

class BfmeThingME
{
public:
	void bfmeGoME(int a);
	int bfmeTestME();
	void bfmeActME();
	char m_bfmePad[0x258];
	int m_bfmeState;
};

void BfmeThingME::bfmeGoME(int a)
{
	if (bfmeTestME() == 0) {
		bfmeActME();
		return;
	}
	m_bfmeState = 0xb;
}

class BfmeSubMF
{
public:
	void bfmeTailMF(int f);
};

class BfmeThingMF
{
public:
	void bfmeGoMF(int f);
	char m_bfmePad[0x310];
	BfmeSubMF *m_bfmeSub;
	char m_bfmePad2[4];
	int m_bfmeA;
	int m_bfmeB;
};

void BfmeThingMF::bfmeGoMF(int f)
{
	m_bfmeA = 0;
	m_bfmeB = -1;
	if (m_bfmeSub)
		m_bfmeSub->bfmeTailMF(1);
}

class BfmeObjMG
{
public:
	void bfmeDoMG();
};

extern int g_bfmeAMG;
extern int g_bfmeBMG;
extern int g_bfmeFlagMG;
extern BfmeObjMG *g_bfmeObjMG;

void __stdcall bfmeGoMG(int a)
{
	g_bfmeAMG = -1;
	g_bfmeBMG = -1;
	if (g_bfmeFlagMG)
		g_bfmeObjMG->bfmeDoMG();
}
