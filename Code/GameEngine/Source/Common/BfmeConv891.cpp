struct BfmeGlobFBA
{
	unsigned char m_bfmeHead[0x3c];
	unsigned int m_bfmeMax;
};

extern BfmeGlobFBA *g_bfmeObjFBA;

struct BfmeThingFBA
{
	float bfmeGoFBA(void *a);
	void bfmeUpdFBA(void *a);
	unsigned char m_bfmeHead[0x358];
	float m_bfmeF;
	unsigned int m_bfmeN;
};

float BfmeThingFBA::bfmeGoFBA(void *a)
{
	if (m_bfmeN < g_bfmeObjFBA->m_bfmeMax)
		bfmeUpdFBA(a);
	return m_bfmeF;
}

class BfmeGlobFBB
{
public:
	char bfmeCallFBB(void *x, void *a, void *y);
};

extern BfmeGlobFBB *g_bfmeObjFBB;

struct BfmeThingFBB
{
	bool bfmeGoFBB(void *a);
	unsigned char m_bfmeHead[8];
	void *m_bfme8;
	char m_bfmeC;
	unsigned char m_bfmePad[3];
	void *m_bfme10;
};

bool BfmeThingFBB::bfmeGoFBB(void *a)
{
	return g_bfmeObjFBB->bfmeCallFBB(m_bfme8, a, m_bfme10) == m_bfmeC;
}

class BfmeObjFBC
{
public:
	char bfmeCallFBC(void *x, void *a, int z, void *y);
};

struct BfmeThingFBC
{
	bool bfmeGoFBC(void *a);
	unsigned char m_bfmeHead[8];
	void *m_bfme8;
	BfmeObjFBC *m_bfmeObj;
	char m_bfme10;
	unsigned char m_bfmePad[3];
	void *m_bfme14;
};

bool BfmeThingFBC::bfmeGoFBC(void *a)
{
	return m_bfmeObj->bfmeCallFBC(m_bfme8, a, 0, m_bfme14) == m_bfme10;
}

struct BfmeObjFBD
{
	bool bfmeAskFBD();
};

class BfmeGlobFBD
{
public:
	BfmeObjFBD *bfmeFindFBD(void *p);
};

extern BfmeGlobFBD *g_bfmeObjFBD;

struct BfmeThingFBD
{
	bool bfmeGoFBD();
	unsigned char m_bfmeHead[8];
	void *m_bfmeP;
};

bool BfmeThingFBD::bfmeGoFBD()
{
	BfmeObjFBD *o = g_bfmeObjFBD->bfmeFindFBD(m_bfmeP);
	if (o && o->bfmeAskFBD())
		return true;
	return false;
}

struct BfmeItemFBG
{
	void bfmeRunFBG(int f);
};

struct BfmeThingFBG
{
	void bfmeGoFBG();
	unsigned char m_bfmeHead[8];
	BfmeItemFBG *m_bfmeArr[4];
};

void BfmeThingFBG::bfmeGoFBG()
{
	for (int i = 0; i < 4; ++i)
	{
		BfmeItemFBG *p = m_bfmeArr[i];
		if (p)
			p->bfmeRunFBG(0);
	}
}
