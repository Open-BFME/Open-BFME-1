extern "C" unsigned char bfmeVftCVE[];

struct BfmeThingCVE
{
	void bfmeBaseCVE();
	BfmeThingCVE *bfmeInitCVE();
	void *volatile m_bfmeVft;
	unsigned char m_bfmeGap[0x40];
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	volatile int m_bfmeC;
	volatile int m_bfmeD;
	volatile int m_bfmeE;
	volatile int m_bfmeF;
	volatile short m_bfmeG;
	unsigned char m_bfmeGap2[2];
	volatile int m_bfmeH;
	volatile int m_bfmeI;
};

BfmeThingCVE *BfmeThingCVE::bfmeInitCVE()
{
	bfmeBaseCVE();
	m_bfmeVft = bfmeVftCVE;
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeE = 0;
	m_bfmeF = 0;
	m_bfmeG = 0;
	m_bfmeH = 0;
	m_bfmeI = 0;
	return this;
}
