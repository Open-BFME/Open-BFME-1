extern "C" unsigned char bfmeVftEOA[];

struct BfmeThingEOA
{
	BfmeThingEOA *bfmeCtorEOA(char flag);
	void bfmeBaseEOA();
	void *volatile m_bfmeVft;
	unsigned char m_bfmeHead[0x3c];
	char volatile m_bfmeFlag;
	unsigned char m_bfmePad[3];
	int volatile m_bfmeK;
};

BfmeThingEOA *BfmeThingEOA::bfmeCtorEOA(char flag)
{
	bfmeBaseEOA();
	m_bfmeFlag = flag;
	m_bfmeVft = bfmeVftEOA;
	m_bfmeK = 0;
	return this;
}

float __cdecl bfmeCalcEOC(void *a);

struct BfmeThingEOC
{
	void bfmeGoEOC(void *a);
	void bfmeAfterEOC();
	unsigned char m_bfmeHead[0x1c];
	float m_bfmeF;
};

void BfmeThingEOC::bfmeGoEOC(void *a)
{
	m_bfmeF = bfmeCalcEOC(a);
	bfmeAfterEOC();
}

struct BfmeThingEOD
{
	BfmeThingEOD *bfmeGoEOD(void *a, void *b);
	void bfmeCallEOD(void *a);
	unsigned char m_bfmeHead[4];
	void *m_bfmeP;
};

BfmeThingEOD *BfmeThingEOD::bfmeGoEOD(void *a, void *b)
{
	bfmeCallEOD(a);
	m_bfmeP = b;
	return this;
}

extern "C" void bfmeCbEOEa();
extern "C" void bfmeCbEOEb();

struct BfmeThingEOE
{
	BfmeThingEOE *bfmeCtorEOE();
};

void __stdcall bfmeInitEOE(BfmeThingEOE *o, int a, int b, void (*ca)(), void (*cb)());

BfmeThingEOE *BfmeThingEOE::bfmeCtorEOE()
{
	bfmeInitEOE(this, 0x14, 8, bfmeCbEOEa, bfmeCbEOEb);
	return this;
}

struct BfmeQueueEOF
{
	unsigned char m_bfmeHead[4];
	void **m_bfmeEnd;
	unsigned char m_bfmePad[4];
	void **volatile m_bfmeCur;
};

struct BfmeThingEOF
{
	void *bfmeGoEOF();
	BfmeQueueEOF *m_bfmeQ;
};

void *BfmeThingEOF::bfmeGoEOF()
{
	BfmeQueueEOF *q = m_bfmeQ;
	if (q->m_bfmeCur == q->m_bfmeEnd)
		return 0;
	void **cur = q->m_bfmeCur;
	void *v = *cur;
	q->m_bfmeCur = cur + 2;
	return v;
}

struct BfmeNodeEOG
{
	BfmeNodeEOG *bfmeUpdEOG();
	unsigned char m_bfmeHead[4];
	BfmeNodeEOG *m_bfmeQ;
	unsigned char m_bfmePad[0x108];
	float m_bfmeF;
};

struct BfmeThingEOG
{
	float bfmeGoEOG();
	unsigned char m_bfmeHead[4];
	BfmeNodeEOG *m_bfmeP;
	unsigned char m_bfmePad[0x108];
	float m_bfmeF;
};

float BfmeThingEOG::bfmeGoEOG()
{
	BfmeNodeEOG *p = m_bfmeP;
	if (p)
	{
		BfmeNodeEOG *q = p->m_bfmeQ;
		if (q)
			p = q->bfmeUpdEOG();
		return p->m_bfmeF;
	}
	return m_bfmeF;
}
