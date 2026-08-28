class BfmeObjECC
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual bool bfmeAsk4ECC();
};

extern BfmeObjECC *g_bfmeObjECD;

bool bfmeGoECD()
{
	BfmeObjECC *o = g_bfmeObjECD;
	if (!o)
		return false;
	return o->bfmeAsk4ECC();
}

class BfmeSubECE
{
public:
	void bfmeCallECE(const char *s);
};

struct BfmeObjECE
{
	unsigned char m_bfmeHead[0x34];
	BfmeSubECE *m_bfmeSub;
};

extern "C" unsigned char bfmeStrECE[];
extern BfmeObjECE *g_bfmeObjECE;

void bfmeGoECE()
{
	BfmeObjECE *o = g_bfmeObjECE;
	if (o)
		o->m_bfmeSub->bfmeCallECE((const char *)bfmeStrECE);
}

struct BfmeObjECF;

struct BfmeVtblECF
{
	void (__stdcall *m_bfmeF0)(BfmeObjECF *o);
	void (__stdcall *m_bfmeF1)(BfmeObjECF *o);
	void (__stdcall *m_bfmeF2)(BfmeObjECF *o);
};

struct BfmeObjECF
{
	BfmeVtblECF *m_bfmeVtbl;
};

extern BfmeObjECF *g_bfmeObjECF;

void bfmeGoECF()
{
	BfmeObjECF *o = g_bfmeObjECF;
	if (o)
		o->m_bfmeVtbl->m_bfmeF2(o);
}

class BfmeSubECG
{
public:
	void bfmeOneECGa();
	void bfmeOneECGb();
	void bfmeTwoECG();
};

struct BfmeThingECGa
{
	void bfmeGoECGa();
	unsigned char m_bfmeHead[0x74];
	BfmeSubECG m_bfmeSub;
};

void BfmeThingECGa::bfmeGoECGa()
{
	m_bfmeSub.bfmeOneECGa();
	m_bfmeSub.bfmeTwoECG();
}

struct BfmeThingECGb
{
	void bfmeGoECGb();
	unsigned char m_bfmeHead[0x70];
	BfmeSubECG m_bfmeSub;
};

void BfmeThingECGb::bfmeGoECGb()
{
	m_bfmeSub.bfmeOneECGb();
	m_bfmeSub.bfmeTwoECG();
}

void __cdecl bfmeFreeECH(void *p);

struct BfmeThingECHa
{
	void bfmeGoECHa();
	void *m_bfmeP;
};

void BfmeThingECHa::bfmeGoECHa()
{
	bfmeFreeECH(m_bfmeP);
	m_bfmeP = 0;
}

struct BfmeThingECHb
{
	void bfmeGoECHb();
	void *m_bfmeP;
};

void BfmeThingECHb::bfmeGoECHb()
{
	bfmeFreeECH(m_bfmeP);
	m_bfmeP = 0;
}

class BfmeObjECI
{
public:
	virtual void bfmeW0();
	virtual void bfmeW1();
	virtual void bfmeW2();
	virtual void bfmeW3();
	virtual void bfmeW4();
	virtual void bfmeW5();
	virtual void bfmeW6();
	virtual void bfmeW7();
	virtual void bfmeW8();
	virtual void bfmeW9();
	virtual void bfmeW10();
	virtual void bfmeW11();
	virtual void bfmeW12();
	virtual void bfmeW13();
	virtual void bfmeW14();
	virtual void bfmeW15();
	virtual void bfmeW16();
	virtual void bfmeW17();
	virtual void bfmeW18();
	virtual void bfmeW19();
	virtual void bfmeW20();
	virtual void bfmeW21();
	virtual void bfmeW22();
	virtual void bfmeW23();
	virtual void bfmeW24();
	virtual void bfmeW25();
	virtual void bfmeW26();
	virtual void bfmeW27();
	virtual void bfmeW28();
	virtual void bfmeW29();
	virtual void bfmeW30();
	virtual void bfmeW31();
	virtual void bfmeW32();
	virtual void bfmeW33();
	virtual void bfmeW34();
	virtual void bfmeW35();
	virtual void bfmeW36();
	virtual void bfmeW37();
	virtual void bfmeW38();
	virtual void bfmeW39();
	virtual void bfmeW40();
	virtual void bfmeW41();
	virtual void bfmeW42();
	virtual void bfmeW43();
	virtual void bfmeW44();
	virtual void bfmeW45();
	virtual bool bfmeAsk46ECI();
};

extern BfmeObjECI *g_bfmeObjECI;

bool bfmeGoECI()
{
	BfmeObjECI *o = g_bfmeObjECI;
	if (!o)
		return false;
	return o->bfmeAsk46ECI();
}
