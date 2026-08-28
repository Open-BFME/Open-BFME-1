class BfmeThingBSC
{
public:
	void bfmeDoBSC(void *what, int flag);
	void bfmeGoBSC();
	unsigned char m_bfmeHead[8];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap[0x18];
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	int m_bfmeE;
	int m_bfmeF;
};

void BfmeThingBSC::bfmeGoBSC()
{
	m_bfmeA = 0;
	m_bfmeC = 0;
	m_bfmeD = 0;
	m_bfmeB = 0;
	m_bfmeE = 0;
	m_bfmeF = 0;
	bfmeDoBSC(m_bfmeWhat, 1);
}
