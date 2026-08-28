extern "C" unsigned char bfmeVftTI[];

struct BfmeSubTI
{
	void bfmeStartTI();
	unsigned char m_bfmeHead[0x68];
};

class BfmeThingTI
{
public:
	BfmeThingTI *bfmeInitTI();
	void *volatile m_bfmeVft;
	unsigned char m_bfmeGap[4];
	BfmeSubTI m_bfmeSub;
	volatile int m_bfmeOne;
	volatile int m_bfmeTwo;
	volatile int m_bfmeThree;
};

BfmeThingTI *BfmeThingTI::bfmeInitTI()
{
	m_bfmeSub.bfmeStartTI();
	m_bfmeVft = bfmeVftTI;
	m_bfmeThree = 0;
	m_bfmeOne = 0;
	m_bfmeTwo = 0;
	return this;
}
