extern "C" unsigned char bfmeVftARCa[];
extern "C" unsigned char bfmeVftARCb[];
extern "C" unsigned char bfmeVftARCc[];

class BfmeThingARC
{
public:
	void bfmeBaseARC();
	BfmeThingARC *bfmeInitARC();
	void *volatile m_bfmeVftA;
	unsigned char m_bfmeGap[4];
	void *volatile m_bfmeVftB;
	volatile int m_bfmeOne;
	volatile int m_bfmeTwo;
	volatile int m_bfmeThree;
};

BfmeThingARC *BfmeThingARC::bfmeInitARC()
{
	bfmeBaseARC();
	m_bfmeVftB = bfmeVftARCa;
	m_bfmeVftA = bfmeVftARCb;
	m_bfmeVftB = bfmeVftARCc;
	m_bfmeOne = 0;
	m_bfmeTwo = 0;
	m_bfmeThree = 0;
	return this;
}
