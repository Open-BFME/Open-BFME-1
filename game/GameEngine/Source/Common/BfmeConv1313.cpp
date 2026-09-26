// Open-BFME5 conversions.

extern void *g_bfmeVftTGE[];

__declspec(dllimport) void *__stdcall bfmeMakeTGE(int a);

class BfmeThingTGE
{
public:
	BfmeThingTGE();
	void bfmeBaseTGE();
	void *m_bfmeVft;
	char m_bfmePad[0x58];
	void *m_bfmeHandle;
};

BfmeThingTGE::BfmeThingTGE()
{
	bfmeBaseTGE();
	m_bfmeVft = g_bfmeVftTGE;
	m_bfmeHandle = bfmeMakeTGE(1);
}

class BfmeSubTGB
{
public:
	void bfmeSetTGB(int a);
};

class BfmeThingTGB
{
public:
	void bfmeGoTGB(int a);
	void bfmeUseTGB(int a);
};

void BfmeThingTGB::bfmeGoTGB(int a)
{
	(*(BfmeSubTGB **)((char *)this - 0x18))->bfmeSetTGB(3);
	bfmeUseTGB(a);
}

struct BfmeArgTGC
{
	int m_bfmeHead;
	int m_bfmeTail;
};

class BfmeSourceTGC
{
public:
	virtual void bfmeV0TGC() = 0;
	virtual void bfmeV1TGC() = 0;
	virtual void bfmeV2TGC() = 0;
	virtual void bfmeV3TGC() = 0;
	virtual void bfmeV4TGC() = 0;
	virtual void bfmeV5TGC() = 0;
	virtual void bfmeV6TGC() = 0;
	virtual void bfmeV7TGC() = 0;
	virtual void bfmeV8TGC() = 0;
	virtual void bfmeV9TGC() = 0;
	virtual void bfmeV10TGC() = 0;
	virtual void bfmeV11TGC() = 0;
	virtual void bfmeV12TGC() = 0;
	virtual void bfmeV13TGC() = 0;
	virtual void bfmeV14TGC() = 0;
	virtual void bfmeV15TGC() = 0;
	virtual void bfmeV16TGC() = 0;
	virtual void bfmeV17TGC() = 0;
	virtual void bfmeV18TGC() = 0;
	virtual void bfmeV19TGC() = 0;
	virtual void bfmeV20TGC() = 0;
	virtual void bfmeV21TGC() = 0;
	virtual void bfmeV22TGC() = 0;
	virtual void bfmeV23TGC() = 0;
	virtual void bfmeV24TGC() = 0;
	virtual void bfmeV25TGC() = 0;
	virtual void *bfmeGetTGC(BfmeArgTGC *p) = 0;
};

void bfmeCalcTGC(void *v, int *tail);

void bfmeGoTGC(BfmeSourceTGC *src, BfmeArgTGC *p)
{
	bfmeCalcTGC(src->bfmeGetTGC(p), &p->m_bfmeTail);
}

void bfmePrintTGD(const char *s);
void bfmeRunTGD(int a, int b);

void bfmeGoTGD(int a)
{
	bfmePrintTGD("\nEntering LUA debug mode.  Type ? for help, 'cont' to exit debug mode\n");
	bfmeRunTGD(a, 0);
}
