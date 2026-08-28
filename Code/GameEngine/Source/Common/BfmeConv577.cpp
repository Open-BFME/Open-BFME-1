extern "C" unsigned char bfmeVftCCF[];

struct BfmeThingCCF
{
	void bfmeBaseCCF();
	BfmeThingCCF *bfmeInitCCF();
	void *volatile m_bfmeVft;
	unsigned char m_bfmeGap[4];
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	volatile int m_bfmeC;
	volatile int m_bfmeD;
	volatile int m_bfmeE;
	volatile int m_bfmeF;
};

BfmeThingCCF *BfmeThingCCF::bfmeInitCCF()
{
	bfmeBaseCCF();
	m_bfmeA = 0;
	m_bfmeVft = bfmeVftCCF;
	m_bfmeB = 0;
	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeE = 0;
	m_bfmeF = 0;
	return this;
}
