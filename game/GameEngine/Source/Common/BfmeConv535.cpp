class BfmeThingBUF
{
public:
	void bfmeBaseBUF(void *what);
	BfmeThingBUF *bfmeInitBUF(void *what);
	unsigned char m_bfmeHead[4];
	volatile bool m_bfmeFlag;
	unsigned char m_bfmePad[3];
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	volatile int m_bfmeC;
};

BfmeThingBUF *BfmeThingBUF::bfmeInitBUF(void *what)
{
	bfmeBaseBUF(what);
	m_bfmeFlag = true;
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = 0;
	return this;
}
