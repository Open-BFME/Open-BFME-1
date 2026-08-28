struct BfmePairCAC
{
	void bfmeSetOneCAC(int x, int y);
	void bfmeSetTwoCAC(int x, int y);
	int m_bfmeX;
	int m_bfmeY;
	unsigned char m_bfmeTail[8];
};

class BfmeThingCAC
{
public:
	void bfmeGoCAC();
	unsigned char m_bfmeHead[0x10];
	BfmePairCAC m_bfmeA;
	BfmePairCAC m_bfmeB;
};

void BfmeThingCAC::bfmeGoCAC()
{
	m_bfmeA.bfmeSetOneCAC(m_bfmeA.m_bfmeX, m_bfmeA.m_bfmeY);
	m_bfmeB.bfmeSetTwoCAC(m_bfmeB.m_bfmeX, m_bfmeB.m_bfmeY);
}
