// Open-BFME5 conversions.

extern void *g_bfmeVftUBA[];

class BfmeThingUBA
{
public:
	BfmeThingUBA();
	void bfmeBaseUBA();
	void *volatile m_bfmeVft;
	char m_bfmePad[0x54];
	volatile int m_bfme58;
	volatile int m_bfme5c;
	volatile int m_bfme60;
};

BfmeThingUBA::BfmeThingUBA()
{
	bfmeBaseUBA();
	m_bfmeVft = g_bfmeVftUBA;
	m_bfme60 = 0;
	m_bfme58 = 0;
	m_bfme5c = 0;
}

class BfmeSubUBB
{
public:
	void bfmeInitUBB(int a);
};

class BfmeThingUBB
{
public:
	BfmeThingUBB();
	volatile short m_bfme00;
	volatile short m_bfme02;
	volatile short m_bfme04;
	volatile short m_bfme06;
	volatile int m_bfme08;
	BfmeSubUBB m_bfmeSub;
};

BfmeThingUBB::BfmeThingUBB()
{
	m_bfme00 = 0;
	m_bfme02 = 0;
	m_bfme04 = 0;
	m_bfme06 = 0;
	m_bfme08 = 0;
	m_bfmeSub.bfmeInitUBB(0);
}
