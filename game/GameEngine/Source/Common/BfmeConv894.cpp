struct BfmeHeldFEA
{
	unsigned char m_bfmeHead[0x370];
	int m_bfmeK;
};

class BfmeGlobFEA
{
public:
	void bfmeCallFEA(void *a, int k);
};

extern BfmeGlobFEA *g_bfmeObjFEA;

struct BfmeThingFEA
{
	void bfmeGoFEA(void *a);
	unsigned char m_bfmeHead[8];
	BfmeHeldFEA *m_bfmeP;
};

void BfmeThingFEA::bfmeGoFEA(void *a)
{
	if (!a)
		return;
	BfmeHeldFEA *h = m_bfmeP;
	if (!h)
		return;
	int k = h->m_bfmeK;
	if (k == -1)
		return;
	g_bfmeObjFEA->bfmeCallFEA(a, k);
}

struct BfmeHeldFEC
{
	unsigned char m_bfmeHead[0x246];
	char m_bfmeB;
};

struct BfmeThingFEC
{
	int bfmeGoFEC();
	unsigned char m_bfmeHeadA[4];
	BfmeHeldFEC *m_bfmeP;
	unsigned char m_bfmeHeadB[0x24];
	int m_bfmeC;
	unsigned char m_bfmeHeadC[0xac];
	char m_bfmeA;
};

int BfmeThingFEC::bfmeGoFEC()
{
	if (!m_bfmeA)
	{
		if (!m_bfmeP->m_bfmeB)
		{
			if (m_bfmeC == 0)
				return 0x3fffffff;
		}
	}
	return 1;
}

class BfmeBaseFED
{
public:
	void bfmeCallFED(void *p, int f);
};

struct BfmeThingFED
{
	void bfmeGoFED(void *a, int b, int c);
	unsigned char m_bfmeHead[0xc];
	int m_bfmeK;
};

void BfmeThingFED::bfmeGoFED(void *a, int b, int c)
{
	if (c > b && c == 3)
	{
		void *p = *(void **)((char *)this - 0x18);
		m_bfmeK = 0x28;
		((BfmeBaseFED *)((char *)this - 0x20))->bfmeCallFED(p, 1);
	}
}

struct BfmeResFEF
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual void bfmeV22();
	virtual void bfmeV23();
	virtual void bfmeVirt24FEF();
};

struct BfmeSubFEF
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual void bfmeV22();
	virtual void bfmeV23();
	virtual void bfmeV24();
	virtual void bfmeV25();
	virtual void bfmeV26();
	virtual void bfmeV27();
	virtual void bfmeV28();
	virtual void bfmeV29();
	virtual void bfmeV30();
	virtual void bfmeV31();
	virtual void bfmeV32();
	virtual void bfmeV33();
	virtual void bfmeV34();
	virtual void bfmeV35();
	virtual void bfmeV36();
	virtual void bfmeV37();
	virtual void bfmeV38();
	virtual void bfmeV39();
	virtual void bfmeV40();
	virtual void bfmeV41();
	virtual void bfmeV42();
	virtual void bfmeV43();
	virtual void bfmeV44();
	virtual void bfmeV45();
	virtual void bfmeV46();
	virtual void bfmeV47();
	virtual void bfmeV48();
	virtual void bfmeV49();
	virtual void bfmeV50();
	virtual void bfmeV51();
	virtual void bfmeV52();
	virtual void bfmeV53();
	virtual void bfmeV54();
	virtual void bfmeV55();
	virtual void bfmeV56();
	virtual void bfmeV57();
	virtual void bfmeV58();
	virtual void bfmeV59();
	virtual void bfmeV60();
	virtual void bfmeV61();
	virtual void bfmeV62();
	virtual void bfmeV63();
	virtual void bfmeV64();
	virtual void bfmeV65();
	virtual void bfmeV66();
	virtual void bfmeV67();
	virtual void bfmeV68();
	virtual void bfmeV69();
	virtual void bfmeV70();
	virtual void bfmeV71();
	virtual void bfmeV72();
	virtual void bfmeV73();
	virtual void bfmeV74();
	virtual void bfmeV75();
	virtual void bfmeV76();
	virtual void bfmeV77();
	virtual void bfmeV78();
	virtual BfmeResFEF *bfmeVirt79FEF();
};

struct BfmeHoldFEF
{
	unsigned char m_bfmeHead[0x204];
	BfmeSubFEF *m_bfmeT;
};

struct BfmeMidFEF
{
	unsigned char m_bfmeHead[0x10];
	BfmeHoldFEF *m_bfmeS;
};

struct BfmeThingFEF
{
	void bfmeGoFEF(void *unused);
	unsigned char m_bfmeHead[0x1c];
	BfmeMidFEF *m_bfmeP;
};

void BfmeThingFEF::bfmeGoFEF(void *unused)
{
	BfmeSubFEF *s = m_bfmeP->m_bfmeS->m_bfmeT;
	if (s)
	{
		BfmeResFEF *r = s->bfmeVirt79FEF();
		if (r)
			r->bfmeVirt24FEF();
	}
}

class BfmeResFEG
{
public:
	void bfmeUseFEG(void *a);
};

class BfmeGlobFEG
{
public:
	BfmeResFEG *bfmeLookFEG(int k);
};

extern BfmeGlobFEG *g_bfmeObjFEG;

struct BfmeOwnFEG
{
	unsigned char m_bfmeHead[0x74];
	int m_bfmeK;
};

struct BfmeThingFEG
{
	void bfmeGoFEG(void *a);
	unsigned char m_bfmeHead[0x88];
	int m_bfmeK;
};

void BfmeThingFEG::bfmeGoFEG(void *a)
{
	int k = m_bfmeK;
	BfmeOwnFEG *o = *(BfmeOwnFEG **)((char *)this - 4);
	if (k != o->m_bfmeK)
	{
		BfmeResFEG *r = g_bfmeObjFEG->bfmeLookFEG(k);
		if (r)
			r->bfmeUseFEG(a);
	}
}
