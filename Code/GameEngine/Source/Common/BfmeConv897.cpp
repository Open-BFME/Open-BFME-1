struct BfmeArgFHA
{
	unsigned char m_bfmeHeadA[0xa8];
	char m_bfmeFlag;
	unsigned char m_bfmeHeadB[0xb];
	void *m_bfmeP;
};

int __cdecl bfmeCallFHA(void *a, void *b);

bool __stdcall bfmeGoFHA(BfmeArgFHA *a)
{
	if (a->m_bfmeFlag)
	{
		void *p = a->m_bfmeP;
		if (bfmeCallFHA(p, p) != 1)
			return true;
	}
	return false;
}

struct BfmeResFHC
{
	virtual bool bfmeVirt0FHC(void *a, void *b, void *c);
};

struct BfmeSubFHC
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
	virtual BfmeResFHC *bfmeVirt39FHC();
};

struct BfmeHoldFHC
{
	BfmeSubFHC *m_bfmeS;
};

struct BfmeThingFHC
{
	bool bfmeGoFHC(void *a, void *b, void *c);
	unsigned char m_bfmeHead[0x150];
	BfmeHoldFHC *m_bfmeH;
};

bool BfmeThingFHC::bfmeGoFHC(void *a, void *b, void *c)
{
	BfmeHoldFHC *h = m_bfmeH;
	if (h)
	{
		BfmeSubFHC *s = h->m_bfmeS;
		if (s)
		{
			BfmeResFHC *r = s->bfmeVirt39FHC();
			if (r)
				return r->bfmeVirt0FHC(a, b, c);
		}
	}
	return false;
}

struct BfmeItemFHD
{
	virtual void bfmeDelFHD(int f);
};

struct BfmeHoldFHD
{
	unsigned char m_bfmeHeadA[0x2c];
	BfmeItemFHD *m_bfmeIt;
	unsigned char m_bfmeHeadB[0x34];
	int m_bfmeX;
};

struct BfmeThingFHD
{
	void bfmeGoFHD();
	unsigned char m_bfmeHead[0x2e0];
	BfmeHoldFHD *m_bfmeH;
};

void BfmeThingFHD::bfmeGoFHD()
{
	BfmeHoldFHD *h = m_bfmeH;
	if (h)
	{
		BfmeItemFHD *it = h->m_bfmeIt;
		if (it)
		{
			it->bfmeDelFHD(1);
			h->m_bfmeIt = 0;
			h->m_bfmeX = 0;
		}
	}
}

void __stdcall bfmeTailFHG(void *a, void *b, int c, int d);

void __stdcall bfmeGoFHG(void *a, void *b, void *c, void *d)
{
	if (a)
		bfmeTailFHG(a, b, 0, 0);
}

class BfmeResFHH
{
public:
	void bfmeUseFHH(void *a, void *b);
};

struct BfmeSubFHH
{
	unsigned char m_bfmeHead[4];
};

class BfmeGlobFHH
{
public:
	BfmeResFHH *bfmeLookFHH(BfmeSubFHH *s);
};

extern BfmeGlobFHH *g_bfmeObjFHH;

struct BfmeThingFHH
{
	void bfmeGoFHH(void *a, void *b);
	unsigned char m_bfmeHeadA[0xb8];
	char m_bfmeFlag;
	unsigned char m_bfmeHeadB[7];
	BfmeSubFHH m_bfmeSub;
};

void BfmeThingFHH::bfmeGoFHH(void *a, void *b)
{
	if (m_bfmeFlag)
		return;
	BfmeResFHH *r = g_bfmeObjFHH->bfmeLookFHH(&m_bfmeSub);
	if (r)
		r->bfmeUseFHH(a, b);
}

