struct BfmeGlobFGA
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
	virtual char bfmeAsk60FGA();
};

extern BfmeGlobFGA *g_bfmeObjFGA;

struct BfmeThingFGA
{
	int bfmeGoFGA();
	unsigned char m_bfmeHead[0xa0];
	char m_bfmeFlag;
};

int BfmeThingFGA::bfmeGoFGA()
{
	if (m_bfmeFlag && g_bfmeObjFGA->bfmeAsk60FGA())
		return 1;
	return 0;
}

struct BfmeGlobFGC
{
	unsigned char m_bfmeHead[0x3c];
	void *m_bfmeV;
};

extern BfmeGlobFGC *g_bfmeObjFGC;

struct BfmeSlotFGC
{
	void *m_bfmeV;
	unsigned char m_bfmePad[0x18];
};

struct BfmeThingFGC
{
	void bfmeGoFGC(int i);
	unsigned char m_bfmeHead[0x1b8];
	BfmeSlotFGC m_bfmeArr[8];
};

void BfmeThingFGC::bfmeGoFGC(int i)
{
	if (i >= 0 && i < 8)
		m_bfmeArr[i].m_bfmeV = g_bfmeObjFGC->m_bfmeV;
}

extern "C" unsigned char bfmeEmptyFGD[];
void __cdecl bfmeCmpFGD(const char *a, const char *b);

struct BfmeStrFGD
{
	unsigned char m_bfmeHead[8];
};

struct BfmeThingFGD
{
	void bfmeGoFGD();
	unsigned char m_bfmeHead[8];
	BfmeStrFGD *m_bfmeA;
	BfmeStrFGD *m_bfmeB;
};

void BfmeThingFGD::bfmeGoFGD()
{
	const char *sa = m_bfmeA ? (const char *)m_bfmeA + 8 : (const char *)bfmeEmptyFGD;
	const char *sb = m_bfmeB ? (const char *)m_bfmeB + 8 : (const char *)bfmeEmptyFGD;
	bfmeCmpFGD(sb, sa);
}

class BfmeResFGE
{
public:
	void bfmeUseFGE(void *b, void *c);
};

class BfmeGlobFGE
{
public:
	BfmeResFGE *bfmeFindFGE(void *a);
};

extern BfmeGlobFGE *g_bfmeObjFGE;

void __stdcall bfmeGoFGE(void *a, void *b, void *c)
{
	BfmeResFGE *r = g_bfmeObjFGE->bfmeFindFGE(a);
	if (r)
		r->bfmeUseFGE(b, c);
}

struct BfmeSinkFGF
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
	virtual void bfmeVirt29FGF(void *p);
	virtual void bfmeW30();
	virtual void bfmeW31();
	virtual void bfmeW32();
	virtual void bfmeW33();
	virtual void bfmeW34();
	virtual void bfmeVirt35FGF(void *p);
};

struct BfmeThingFGF
{
	void bfmeGoFGF(BfmeSinkFGF *s);
	unsigned char m_bfmeHead[4];
	int m_bfmeA;
	int m_bfmeB;
};

void BfmeThingFGF::bfmeGoFGF(BfmeSinkFGF *s)
{
	s->bfmeVirt29FGF(&m_bfmeA);
	s->bfmeVirt35FGF(&m_bfmeB);
}

BfmeSinkFGF *bfmeGoFGG(BfmeSinkFGF *s, char *p)
{
	s->bfmeVirt35FGF(p);
	s->bfmeVirt35FGF(p + 1);
	return s;
}
