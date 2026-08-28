class BfmeResEGE
{
public:
	void bfmeUseEGE(int n);
};

class BfmeObjEGE
{
public:
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
	virtual BfmeResEGE *bfmeGet13EGE(int id);
};

class BfmeObj2EGE
{
public:
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
	virtual void bfmeVirt58EGE();
};

extern BfmeObjEGE *g_bfmeObjEGE;
extern BfmeObj2EGE *g_bfmeObj2EGE;

void bfmeGoEGEa()
{
	BfmeResEGE *r = g_bfmeObjEGE->bfmeGet13EGE(0x3eb);
	r->bfmeUseEGE(1);
	g_bfmeObj2EGE->bfmeVirt58EGE();
}

class BfmeSubEGF
{
public:
	bool bfmeAskEGFa();
	bool bfmeAskEGFb();
};

struct BfmeThingEGF
{
	bool bfmeGoEGFa();
	bool bfmeGoEGFb();
	unsigned char m_bfmeHeadA[0x140];
	BfmeSubEGF *m_bfmeP;
	unsigned char m_bfmeHeadB[0x94];
	int m_bfmeState;
};

bool BfmeThingEGF::bfmeGoEGFa()
{
	switch (m_bfmeState)
	{
	case 1:
	case 4:
		{
			BfmeSubEGF *p = m_bfmeP;
			if (p && p->bfmeAskEGFa())
				return true;
		}
		break;
	}
	return false;
}

bool BfmeThingEGF::bfmeGoEGFb()
{
	switch (m_bfmeState)
	{
	case 1:
	case 4:
		{
			BfmeSubEGF *p = m_bfmeP;
			if (p && p->bfmeAskEGFb())
				return true;
		}
		break;
	}
	return false;
}



void bfmeGoEGEb()
{
	BfmeResEGE *r = g_bfmeObjEGE->bfmeGet13EGE(0x3eb);
	r->bfmeUseEGE(1);
	g_bfmeObj2EGE->bfmeVirt58EGE();
}
