struct BfmeThingEGA;

struct BfmeSubEGA
{
	BfmeThingEGA *bfmeUpdEGA();
};

struct BfmeThingEGA
{
	unsigned char m_bfmeHeadA[0xc];
	BfmeSubEGA *m_bfmeS;
	unsigned char m_bfmeHeadB[0xbc];
	void *m_bfmeX;
	unsigned char m_bfmeHeadC[4];
	void *m_bfmeY;
};

void *__stdcall bfmeGoEGAa(void *a, BfmeThingEGA *b)
{
	BfmeSubEGA *s = b->m_bfmeS;
	if (s)
	{
		b = s->bfmeUpdEGA();
		return b->m_bfmeX;
	}
	return b->m_bfmeY;
}

struct BfmeThingEGB;

struct BfmeSubEGB
{
	BfmeThingEGB *bfmeUpdEGB();
};

struct BfmeThingEGB
{
	unsigned char m_bfmeHeadA[0xc];
	BfmeSubEGB *m_bfmeS;
	void *m_bfmeX;
	unsigned char m_bfmeHeadC[4];
	void *m_bfmeY;
};

void *__stdcall bfmeGoEGAb(void *a, BfmeThingEGB *b)
{
	BfmeSubEGB *s = b->m_bfmeS;
	if (s)
	{
		b = s->bfmeUpdEGB();
		return b->m_bfmeX;
	}
	return b->m_bfmeY;
}

struct BfmeResEGC
{
	unsigned char m_bfmeHead[8];
	int m_bfmeX;
};

class BfmeSubEGCa
{
public:
	BfmeResEGC *bfmeFindEGCa(void *a);
};

class BfmeSubEGCb
{
public:
	BfmeResEGC *bfmeFindEGCb(void *a);
};

struct BfmeThingEGCa
{
	int bfmeGoEGCa(void *a);
	unsigned char m_bfmeHead[0x24];
	BfmeSubEGCa m_bfmeSub;
};

int BfmeThingEGCa::bfmeGoEGCa(void *a)
{
	BfmeResEGC *r = m_bfmeSub.bfmeFindEGCa(a);
	if (!r)
		return -1;
	return r->m_bfmeX;
}

struct BfmeThingEGCb
{
	int bfmeGoEGCb(void *a);
	unsigned char m_bfmeHead[0x58];
	BfmeSubEGCb m_bfmeSub;
};

int BfmeThingEGCb::bfmeGoEGCb(void *a)
{
	BfmeResEGC *r = m_bfmeSub.bfmeFindEGCb(a);
	if (!r)
		return -1;
	return r->m_bfmeX;
}

class BfmeObjEGD
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
	virtual void bfmeVirt55EGD(void *self, void *a);
};

extern BfmeObjEGD *g_bfmeObjEGD;

struct BfmeThingEGD
{
	void bfmeGoEGD(void *a);
};

void BfmeThingEGD::bfmeGoEGD(void *a)
{
	g_bfmeObjEGD->bfmeVirt55EGD(this, a);
}

