// Open-BFME5 conversions.

extern void *g_bfmeVftTQA[];

class BfmeSubTQA
{
public:
	void bfmeInitTQA(int a, int b, float f);
	char m_bfmePad[8];
};

class BfmeThingTQA
{
public:
	BfmeThingTQA();
	void *m_bfmeVft;
	int m_bfme04;
	int m_bfme08;
	char m_bfmePad[4];
	BfmeSubTQA m_bfmeSub;
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	char m_bfme24;
	char m_bfmePad2[3];
	int m_bfme28;
};

BfmeThingTQA::BfmeThingTQA()
{
	m_bfmeVft = g_bfmeVftTQA;
	m_bfmeSub.bfmeInitTQA(0, 0, 1.0f);
	m_bfme04 = 0;
	m_bfme08 = 0;
	m_bfme18 = 0;
	m_bfme1c = 0;
	m_bfme20 = 0;
	m_bfme24 = 0;
	m_bfme28 = 0;
}

extern void *g_bfmeVftTQD[];

class BfmeSinkTQD
{
public:
	virtual void bfmeV0TQD() = 0;
	virtual void bfmeV1TQD() = 0;
	virtual void bfmeV2TQD() = 0;
	virtual void bfmeDropTQD(void *p, int f) = 0;
};

BfmeSinkTQD *bfmeGetTQD(void);
void bfmeFreeTQD(void *p, int n);

class BfmeThingTQD
{
public:
	void *bfmeDelTQD(unsigned char flags);
	void *m_bfmeVft;
	char m_bfmePad[8];
	void *m_bfmeItem;
};

void *BfmeThingTQD::bfmeDelTQD(unsigned char flags)
{
	m_bfmeVft = g_bfmeVftTQD;
	bfmeGetTQD()->bfmeDropTQD(m_bfmeItem, 0);
	if (flags & 1)
		bfmeFreeTQD(this, 0x14);
	return this;
}
