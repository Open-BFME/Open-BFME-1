// Open-BFME5 conversions.

extern void *g_bfmeVftATWA[];
extern void *g_bfmeVftBTWA[];
extern void *g_bfmeVftCTWA[];

class Gen_007e86c0
{
public:
	void m();
};

class BfmeStrTWA
{
public:
	char m_bfmePad[0x20];
};

void bfmeFreeTWA(void *p, int n);

class BfmeThingTWA
{
public:
	void *bfmeDelTWA(unsigned char flags);
	void bfmeStepTWA();
	void *m_bfmeVft0;
	void *m_bfmeVft1;
	char m_bfmePad[8];
	BfmeStrTWA m_bfmeStr;
};

void *BfmeThingTWA::bfmeDelTWA(unsigned char flags)
{
	m_bfmeVft0 = g_bfmeVftATWA;
	m_bfmeVft1 = g_bfmeVftBTWA;
	bfmeStepTWA();
	((Gen_007e86c0 *)&m_bfmeStr)->m();
	m_bfmeVft0 = g_bfmeVftCTWA;
	if (flags & 1)
		bfmeFreeTWA(this, 0x30);
	return this;
}

// 0x0112B5C4 is the vftable Rva007F6D60ChildConstructor.cpp emits (ledger
// dir32 row ??_7Rva007F6D60Child@@6B@); g_bfmeVftATWB was a stand-in spelling.
extern "C" void *__identifier("??_7Rva007F6D60Child@@6B@")[];
extern void *g_bfmeVftBTWB[];

class BfmeStrTWB
{
public:
	char m_bfmePad[0x10];
};

class BfmeListTWB
{
public:
	void bfmeDropTWB();
	char m_bfmePad[0x10];
};

void bfmeFreeTWB(void *p);

class BfmeThingTWB
{
public:
	void *bfmeDelTWB(unsigned char flags);
	void *m_bfmeVft;
	char m_bfmePad[4];
	int m_bfme08;
	char m_bfmePad2[0x10];
	BfmeListTWB m_bfmeList;
	BfmeStrTWB m_bfmeB;
	BfmeStrTWB m_bfmeA;
};

void *BfmeThingTWB::bfmeDelTWB(unsigned char flags)
{
	m_bfmeVft = __identifier("??_7Rva007F6D60Child@@6B@");
	m_bfme08 = 0;
	((Gen_007e86c0 *)&m_bfmeA)->m();
	((Gen_007e86c0 *)&m_bfmeB)->m();
	m_bfmeList.bfmeDropTWB();
	m_bfmeVft = g_bfmeVftBTWB;
	if (flags & 1)
		bfmeFreeTWB(this);
	return this;
}

class BfmeSinkTWC
{
public:
	virtual void bfmeV0TWC() = 0;
	virtual void bfmeV1TWC() = 0;
	virtual void bfmeV2TWC() = 0;
	virtual void bfmeDropTWC(void *p, int f) = 0;
};

BfmeSinkTWC *bfmeGetTWC(void);
void bfmeFreeTWC(void *p, int n);

class BfmeHeadTWC
{
public:
	char m_bfmePad[0x10];
};

class BfmeThingTWC
{
public:
	void *bfmeDelTWC(unsigned char flags);
	BfmeHeadTWC m_bfmeHead;
	int m_bfme10;
	void *m_bfmeItem;
};

void *BfmeThingTWC::bfmeDelTWC(unsigned char flags)
{
	if (m_bfmeItem)
		bfmeGetTWC()->bfmeDropTWC(m_bfmeItem, 0);
	m_bfmeItem = 0;
	m_bfme10 = 0;
	((Gen_007e86c0 *)&m_bfmeHead)->m();
	if (flags & 1)
		bfmeFreeTWC(this, 0x20);
	return this;
}
