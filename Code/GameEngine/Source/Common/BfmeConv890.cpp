struct BfmeItemFAA
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
	virtual void bfmeV79();
	virtual void bfmeV80();
	virtual void bfmeV81();
	virtual void bfmeV82();
	virtual void bfmeV83();
	virtual void bfmeV84();
	virtual void bfmeV85();
	virtual void bfmeV86();
	virtual void bfmeV87();
	virtual void bfmeV88();
	virtual void bfmeV89();
	virtual void bfmeV90();
	virtual void bfmeV91();
	virtual void bfmeV92();
	virtual void bfmeV93();
	virtual void bfmeV94();
	virtual void bfmeV95();
	virtual void bfmeV96();
	virtual void bfmeV97();
	virtual void bfmeV98();
	virtual void bfmeV99();
	virtual void bfmeV100();
	virtual void bfmeV101();
	virtual void bfmeV102();
	virtual void bfmeV103();
	virtual void bfmeV104();
	virtual void bfmeV105();
	virtual void bfmeV106();
	virtual void bfmeV107();
	virtual void bfmeV108();
	virtual void bfmeV109();
	virtual void bfmeV110();
	virtual void bfmeV111();
	virtual void bfmeV112();
	virtual void bfmeV113();
	virtual void bfmeV114();
	virtual void bfmeV115();
	virtual void bfmeV116();
	virtual void bfmeV117();
	virtual void bfmeV118();
	virtual void bfmeV119();
	virtual void bfmeV120();
	virtual void bfmeV121();
	virtual void bfmeVirt122FAA();
};

struct BfmeSubFAA
{
	void bfmeRunFAA(int f);
	unsigned char m_bfmeHead[0x204];
	BfmeItemFAA *m_bfmeIt;
};

struct BfmeHoldFAA
{
	unsigned char m_bfmeHead[0x10];
	BfmeSubFAA *m_bfmeS;
};

struct BfmeThingFAA
{
	int bfmeGoFAA();
	unsigned char m_bfmeHead[0x1c];
	BfmeHoldFAA *m_bfmeP;
};

int BfmeThingFAA::bfmeGoFAA()
{
	BfmeSubFAA *s = m_bfmeP->m_bfmeS;
	BfmeItemFAA *it = s->m_bfmeIt;
	if (it)
		it->bfmeVirt122FAA();
	s->bfmeRunFAA(1);
	return 0;
}

struct BfmeBaseFAC
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
	virtual void bfmeVirt14FAC(void *a);
};

struct BfmeThingFAC
{
	void bfmeGoFAC(void *a);
	unsigned char m_bfmeHead[4];
	BfmeBaseFAC *m_bfmeP;
};

void BfmeThingFAC::bfmeGoFAC(void *a)
{
	(*(BfmeBaseFAC **)((char *)this - 8))->bfmeVirt14FAC(a);
	if (m_bfmeP)
		m_bfmeP->bfmeVirt14FAC(a);
}

struct BfmeResFAD
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
	virtual void bfmeV79();
	virtual void bfmeV80();
	virtual void bfmeV81();
	virtual void bfmeV82();
	virtual void bfmeV83();
	virtual void bfmeV84();
	virtual void bfmeV85();
	virtual void bfmeV86();
	virtual void bfmeV87();
	virtual void bfmeV88();
	virtual void bfmeV89();
	virtual void bfmeV90();
	virtual void bfmeV91();
	virtual void bfmeV92();
	virtual void bfmeV93();
	virtual void bfmeV94();
	virtual void bfmeV95();
	virtual void bfmeV96();
	virtual void bfmeV97();
	virtual void bfmeV98();
	virtual void bfmeV99();
	virtual void bfmeV100();
	virtual void bfmeV101();
	virtual void bfmeV102();
	virtual void bfmeV103();
	virtual void bfmeV104();
	virtual void bfmeV105();
	virtual void bfmeV106();
	virtual void bfmeV107();
	virtual void bfmeV108();
	virtual void bfmeV109();
	virtual void bfmeV110();
	virtual void bfmeV111();
	virtual void bfmeV112();
	virtual void bfmeV113();
	virtual void bfmeV114();
	virtual void bfmeV115();
	virtual void bfmeV116();
	virtual void bfmeV117();
	virtual void bfmeV118();
	virtual void bfmeV119();
	virtual void bfmeV120();
	virtual void bfmeVirt121FAD();
};

struct BfmeSubFAD
{
	BfmeResFAD *bfmeGetFAD();
};

struct BfmeHoldFAD
{
	unsigned char m_bfmeHead[0x10];
	BfmeSubFAD *m_bfmeS;
};

struct BfmeThingFAD
{
	void bfmeGoFAD(void *unused);
	unsigned char m_bfmeHead[0x1c];
	BfmeHoldFAD *m_bfmeP;
	unsigned char m_bfmePad[8];
	int m_bfmeK;
};

void BfmeThingFAD::bfmeGoFAD(void *unused)
{
	if (m_bfmeK != 2)
		return;
	BfmeResFAD *r = m_bfmeP->m_bfmeS->bfmeGetFAD();
	if (r)
		r->bfmeVirt121FAD();
}

struct BfmeItemFAE
{
	virtual void bfmeDelFAE(int f);
};

struct BfmeHoldFAE
{
	BfmeItemFAE *m_bfmeP;
};

extern BfmeHoldFAE *g_bfmeAFAE;
extern int g_bfmeBFAE;
extern int g_bfmeCFAE;

void bfmeGoFAE()
{
	BfmeItemFAE *p = g_bfmeAFAE->m_bfmeP;
	g_bfmeAFAE->m_bfmeP = 0;
	g_bfmeBFAE = 1;
	if (p)
		p->bfmeDelFAE(1);
	g_bfmeCFAE |= 1;
}

struct BfmeGlobFAF
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
	virtual void bfmeVirt42FAF(void *x, unsigned int b);
};

extern BfmeGlobFAF *g_bfmeObjFAF;

struct BfmeArgFAF
{
	unsigned char m_bfmeHead[0xc];
	void *m_bfmeX;
};

struct BfmeThingFAF
{
	void bfmeGoFAF(BfmeArgFAF *a, unsigned int b);
	unsigned char m_bfmeB;
};

void BfmeThingFAF::bfmeGoFAF(BfmeArgFAF *a, unsigned int b)
{
	g_bfmeObjFAF->bfmeVirt42FAF(a->m_bfmeX, m_bfmeB);
}

struct BfmeObjFAH
{
	int bfmeKindFAH(void *p);
};

struct BfmeThingFAH
{
	int bfmeGoFAH(BfmeObjFAH *o);
	unsigned char m_bfmeHead[4];
	void *m_bfmeP;
	unsigned char m_bfmePad[8];
	int m_bfmeW;
	int m_bfmeV;
};

int BfmeThingFAH::bfmeGoFAH(BfmeObjFAH *o)
{
	if (o->bfmeKindFAH(m_bfmeP) == 2)
		return 0;
	int v = m_bfmeV;
	if (v == -1)
		v = m_bfmeW;
	return v;
}

