class BfmeOwnerEBC
{
public:
	void bfmeCallEBC();
};

struct BfmeThingEBC
{
	void bfmeGoEBC(void *unused);
	unsigned char m_bfmeHead[0x21];
	char m_bfmeFlag;
};

void BfmeThingEBC::bfmeGoEBC(void *unused)
{
	((BfmeOwnerEBC *)((char *)this - 0x1c))->bfmeCallEBC();
	m_bfmeFlag = 1;
}

class BfmeSubEBD
{
public:
	void bfmeCallEBD();
};

struct BfmeThingEBD
{
	void bfmeGoEBD();
	unsigned char m_bfmeHead[0x18];
	BfmeSubEBD m_bfmeSub;
	unsigned char m_bfmePad[0x4f];
	char m_bfmeFlag;
};

void BfmeThingEBD::bfmeGoEBD()
{
	m_bfmeSub.bfmeCallEBD();
	m_bfmeFlag = 0;
}

class BfmeGlobEBE
{
public:
	void *bfmeLookEBE(void *p);
};

extern BfmeGlobEBE *g_bfmeObjEBE;

struct BfmeThingEBE
{
	void *bfmeGoEBEa();
	void *bfmeGoEBEb();
	unsigned char m_bfmeHead[0x20];
	void *m_bfmeP;
};

void *BfmeThingEBE::bfmeGoEBEa()
{
	void *p = m_bfmeP;
	if (p)
		return g_bfmeObjEBE->bfmeLookEBE(p);
	return 0;
}

void *BfmeThingEBE::bfmeGoEBEb()
{
	void *p = m_bfmeP;
	if (p)
		return g_bfmeObjEBE->bfmeLookEBE(p);
	return 0;
}

void bfmeTwoEBF();

struct BfmeThingEBF
{
	void bfmeGoEBF();
	void bfmeOneEBF();
	unsigned char m_bfmeHead[0x74];
	char m_bfmeFlag;
};

void BfmeThingEBF::bfmeGoEBF()
{
	bfmeOneEBF();
	bfmeTwoEBF();
	m_bfmeFlag = 0;
}

void bfmeTwoEBG();

struct BfmeThingEBG
{
	BfmeThingEBG *bfmeGoEBG();
	void bfmeOneEBG();
};

BfmeThingEBG *BfmeThingEBG::bfmeGoEBG()
{
	bfmeOneEBG();
	bfmeTwoEBG();
	return this;
}

struct BfmeHeldEBH
{
	unsigned char m_bfmeHead[0x28];
	float m_bfmeX;
};

struct BfmeThingEBH
{
	void bfmeGoEBH();
	float bfmeCalcEBH(float v);
	unsigned char m_bfmeHead[4];
	BfmeHeldEBH *m_bfmeP;
	float m_bfmeF;
};

void BfmeThingEBH::bfmeGoEBH()
{
	m_bfmeF = bfmeCalcEBH(m_bfmeP->m_bfmeX);
}
