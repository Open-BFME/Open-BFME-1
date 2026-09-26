extern "C" unsigned char bfmeVftCIA[];

struct BfmeThingCIA
{
	void bfmeBaseCIA();
	BfmeThingCIA *bfmeInitCIA(void *what);
	void *volatile m_bfmeVft;
	unsigned char m_bfmeGap[0x94];
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	void *volatile m_bfmeC;
};

BfmeThingCIA *BfmeThingCIA::bfmeInitCIA(void *what)
{
	bfmeBaseCIA();
	m_bfmeVft = bfmeVftCIA;
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = what;
	return this;
}
