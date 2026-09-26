// Open-BFME5 conversions.

extern void *g_bfmeVftATWA[];
extern void *g_bfmeVftBTWA[];
extern void *g_bfmeVftCTWA[];

class BfmeStrTWA
{
public:
	void bfmeDtorTWA();
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
	m_bfmeStr.bfmeDtorTWA();
	m_bfmeVft0 = g_bfmeVftCTWA;
	if (flags & 1)
		bfmeFreeTWA(this, 0x30);
	return this;
}

extern void *g_bfmeVftATWB[];
extern void *g_bfmeVftBTWB[];

class BfmeStrTWB
{
public:
	void bfmeDtorTWB();
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
	m_bfmeVft = g_bfmeVftATWB;
	m_bfme08 = 0;
	m_bfmeA.bfmeDtorTWB();
	m_bfmeB.bfmeDtorTWB();
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
	void bfmeDtorTWC();
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
	m_bfmeHead.bfmeDtorTWC();
	if (flags & 1)
		bfmeFreeTWC(this, 0x20);
	return this;
}
