class BfmeSubECJ
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
	virtual void bfmeSet112ECJ(int on);
};

struct BfmeThingECJ
{
	void bfmeGoECJ();
	unsigned char m_bfmeHead[8];
	BfmeSubECJ *m_bfmeP;
};

void BfmeThingECJ::bfmeGoECJ()
{
	if (m_bfmeP)
		m_bfmeP->bfmeSet112ECJ(1);
}

struct BfmeHeldECKa
{
	unsigned char m_bfmeHead[0x280];
	void *m_bfmeX;
	void bfmeDoECKa();
};

struct BfmeThingECKa
{
	void *bfmeGoECKa();
	unsigned char m_bfmeHead[4];
	BfmeHeldECKa *m_bfmeP;
};

void *BfmeThingECKa::bfmeGoECKa()
{
	m_bfmeP->bfmeDoECKa();
	return m_bfmeP->m_bfmeX;
}

struct BfmeHeldECKb
{
	unsigned char m_bfmeHead[0x29c];
	void *m_bfmeX;
	void bfmeDoECKb();
};

struct BfmeThingECKb
{
	void *bfmeGoECKb();
	unsigned char m_bfmeHead[4];
	BfmeHeldECKb *m_bfmeP;
};

void *BfmeThingECKb::bfmeGoECKb()
{
	m_bfmeP->bfmeDoECKb();
	return m_bfmeP->m_bfmeX;
}

class BfmeThingECMa
{
public:
	BfmeThingECMa *bfmeCtorECMa();
};

class BfmeThingECMb
{
public:
	BfmeThingECMb *bfmeCtorECMb();
};

void *__cdecl bfmeAllocECMa(unsigned int n);
void *__cdecl bfmeAllocECMb(unsigned int n);

BfmeThingECMa *bfmeGoECMa()
{
	void *p = bfmeAllocECMa(0x48);
	if (p)
		return ((BfmeThingECMa *)p)->bfmeCtorECMa();
	return 0;
}

BfmeThingECMb *bfmeGoECMb()
{
	void *p = bfmeAllocECMb(0x18);
	if (p)
		return ((BfmeThingECMb *)p)->bfmeCtorECMb();
	return 0;
}

