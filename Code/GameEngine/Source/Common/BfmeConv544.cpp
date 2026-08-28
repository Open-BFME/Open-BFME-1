class BfmeThingBWC
{
public:
	void bfmeBaseBWC(void *what);
	BfmeThingBWC *bfmeInitBWC(void *what);
	unsigned char m_bfmeHead[4];
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	int m_bfmeE;
};

BfmeThingBWC *BfmeThingBWC::bfmeInitBWC(void *what)
{
	bfmeBaseBWC(what);
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeE = 0;
	return this;
}
