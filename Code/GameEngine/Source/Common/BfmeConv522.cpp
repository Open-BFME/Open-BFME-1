struct BfmePartBSB
{
	unsigned char m_bfmeHead[4];
};

class BfmeThingBSB
{
public:
	void bfmeOneBSB(BfmePartBSB *one, BfmePartBSB *two);
	void bfmeTwoBSB();
	void bfmeGoBSB();
	unsigned char m_bfmeHead[0xe4];
	BfmePartBSB m_bfmeA;
	unsigned char m_bfmeGap[8];
	BfmePartBSB m_bfmeB;
};

void BfmeThingBSB::bfmeGoBSB()
{
	bfmeOneBSB(&m_bfmeA, &m_bfmeB);
	bfmeTwoBSB();
}
