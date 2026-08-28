struct BfmeItemEZA
{
	void bfmeRunEZA();
};

struct BfmeNodeEZA
{
	BfmeNodeEZA *m_bfmeNext;
	unsigned char m_bfmePad[4];
	BfmeItemEZA *m_bfmeItem;
};

struct BfmeThingEZA
{
	void bfmeGoEZA();
	unsigned char m_bfmeHead[0x288];
	BfmeNodeEZA *m_bfmeList;
};

void BfmeThingEZA::bfmeGoEZA()
{
	for (BfmeNodeEZA *n = m_bfmeList->m_bfmeNext; n != m_bfmeList; n = n->m_bfmeNext)
		n->m_bfmeItem->bfmeRunEZA();
}

extern "C" const float bfmeKEZC;

struct BfmeResEZC
{
	unsigned char m_bfmeHead[8];
	float m_bfmeF;
};

class BfmeSubEZC
{
public:
	BfmeResEZC *bfmeFindEZC(void *a);
};

struct BfmeThingEZC
{
	float bfmeGoEZC(void *a);
	unsigned char m_bfmeHead[0x1d8];
	BfmeSubEZC m_bfmeSub;
};

float BfmeThingEZC::bfmeGoEZC(void *a)
{
	BfmeResEZC *r = m_bfmeSub.bfmeFindEZC(a);
	if (r)
		return r->m_bfmeF;
	return bfmeKEZC;
}

struct BfmeSubEZF
{
	unsigned char m_bfmeHead[4];
};

struct BfmeArgEZF
{
	unsigned char m_bfmeHead[0x38];
	BfmeSubEZF m_bfmeSub;
};

class BfmeGlobEZF
{
public:
	void bfmeRunEZF();
};

extern BfmeGlobEZF *g_bfmeObjEZF;
bool __stdcall bfmeAskEZF(int k, BfmeSubEZF *s);

void __stdcall bfmeGoEZF(BfmeArgEZF *a)
{
	if (a && bfmeAskEZF(3, &a->m_bfmeSub))
		g_bfmeObjEZF->bfmeRunEZF();
}

struct BfmeItemEZG
{
	virtual void bfmeDelEZG(int f);
};

struct BfmeThingEZG
{
	void bfmeGoEZG();
	BfmeItemEZG *m_bfmeArr[0x6d];
};

void BfmeThingEZG::bfmeGoEZG()
{
	for (int i = 0; i < 0x6d; ++i)
	{
		BfmeItemEZG *p = m_bfmeArr[i];
		if (p)
		{
			p->bfmeDelEZG(1);
			m_bfmeArr[i] = 0;
		}
	}
}
